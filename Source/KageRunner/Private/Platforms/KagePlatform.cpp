// Copyright Vox Dei. All Rights Reserved.

#include "Platforms/KagePlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "KageRunner/ModuleEditor.h"
#include "Items/Obstacle.h"
#include "Items/Destructible.h"
#include "PackedLevelActor/PackedLevelActor.h"
#include "Platforms/PackedObstacles.h"

AKagePlatform::AKagePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName(TEXT("SceneComponent")));
	RootComponent = SceneRoot;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("StaticMeshComponent")));
	FloorMesh->SetupAttachment(GetRootComponent());
	FloorMesh->SetGenerateOverlapEvents(false);
	FloorMesh->SetCollisionObjectType(ECC_WorldStatic);
	/*FloorMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	FloorMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	FloorMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	FloorMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	FloorMesh->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);*/


	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	BoxTrigger->SetupAttachment(GetRootComponent());
	BoxTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AKagePlatform::OnBeginOverlap);

	ADD_PROPERTY_SECTION("Platform");
}

void AKagePlatform::BeginPlay()
{
	Super::BeginPlay();

	ActorsToDestroy.Add(this);

	if (bIsFirstPlatform) for (int i = 1; i < PlatformCount; i++) SpawnPlatform(PlatformSize * i);	// Generate count platforms minus one (first platform already exist)

	SpawnOutsideActors();
}

void AKagePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().X < DestroyXLocation) for (auto& Actor : ActorsToDestroy) Actor->Destroy();

	GetRootComponent()->AddLocalOffset(FVector(-500.f * DeltaTime, 0.f, 0.f));	// Add backward movement infinitely
}

void AKagePlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bPlayerOverlapped || !OtherActor->ActorHasTag(FName(TEXT("Player")))) return;	// Return if already overlapped or is not player

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("Begin overlap")));

	bPlayerOverlapped = true;

	SpawnPlatform(PlatformCount * PlatformSize);
}

void AKagePlatform::SpawnPlatform(float XOffset)
{
	UWorld* World = GetWorld();

	if (World && !PlatformClasses.IsEmpty())	// Check if platform classes is not empty
	{
		const FVector LocationToSpawn = GetActorLocation() + FVector(XOffset, 0.f, 0.f);

		const int Selection = FMath::RandRange(0, PlatformClasses.Num() - 1);	// Select platform class

		if (PlatformClasses[Selection]) World->SpawnActor<AKagePlatform>(PlatformClasses[Selection], LocationToSpawn, GetActorRotation());	// Spawn selected platform
	}
}

void AKagePlatform::SpawnOutsideActors()
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (!OutsideActors.IsEmpty() && !OutsideActorsLocation.IsEmpty())	// Check if packed actor classes and locations are not empty
	{
		for (auto& LocationToSpawn : OutsideActorsLocation)
		{
			const int Selection = FMath::RandRange(0, OutsideActors.Num() - 1);	// Select packed actor class

			if (OutsideActors[Selection])
			{
				const bool Select = FMath::RandRange(0, 1) == 1;
				FRotator SpawnRotation = Select ? GetActorRotation() : GetActorRotation() + FRotator(0.f, 180.f, 0.f);	// Select rotation

				APackedLevelActor* PackedActor = World->SpawnActor<APackedLevelActor>(OutsideActors[Selection], LocationToSpawn, SpawnRotation);	// Spawn selected packed actor
				if (PackedActor)
				{
					PackedActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
					ActorsToDestroy.Add(PackedActor);
				}
			}
		}			
	}

	if (OutsideScene)	// Check if scenario class is valid
	{
		APackedLevelActor* PackedActor = World->SpawnActor<APackedLevelActor>(OutsideScene, GetActorLocation(), GetActorRotation());	// Spawn outside scene packed actor
		if (PackedActor)
		{
			PackedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			ActorsToDestroy.Add(PackedActor);
		}
	}

	if (!InsideObstacles.IsEmpty())	// Check if obstacle classes are not a empty array
	{
		const int Selection = FMath::RandRange(0, InsideObstacles.Num() - 1);	// Select packed obstacle class

		if (InsideObstacles[Selection])
		{
			const bool Select = FMath::RandRange(0, 1) == 1;
			FRotator SpawnRotation = Select ? GetActorRotation() : GetActorRotation() + FRotator(0.f, 180.f, 0.f);	// Select rotation

			PackedObstaclesSpawn += GetActorLocation();	// Update offset from this actor location

			APackedObstacles* PackedObstacle = World->SpawnActor<APackedObstacles>(InsideObstacles[Selection], PackedObstaclesSpawn, SpawnRotation);
			if (PackedObstacle)
			{
				PackedObstacle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				ActorsToDestroy.Add(PackedObstacle);
			}
		}
	}
}
