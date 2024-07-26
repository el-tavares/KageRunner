// Copyright Vox Dei. All Rights Reserved.

#include "Platforms/KagePlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "KageRunner/ModuleEditor.h"
#include "Items/Obstacle.h"
#include "Items/Destructible.h"

AKagePlatform::AKagePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName(TEXT("SceneComponent")));
	RootComponent = SceneRoot;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("StaticMeshComponent")));
	FloorMesh->SetupAttachment(GetRootComponent());
	FloorMesh->SetCollisionObjectType(ECC_WorldStatic);
	FloorMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	FloorMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	FloorMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	FloorMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	FloorMesh->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	BoxTrigger->SetupAttachment(GetRootComponent());
	BoxTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AKagePlatform::OnBeginOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AKagePlatform::OnEndOverlap);

	ADD_PROPERTY_SECTION("Platform");
}

void AKagePlatform::BeginPlay()
{
	Super::BeginPlay();

	PlatformActors.Add(this);
	SetObstacles();
}

void AKagePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlayerInside) RunningTime += DeltaTime;
}

void AKagePlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("Begin overlap")));

	bPlayerInside = true;

	UWorld* World = GetWorld();
	if (World && !PlatformClasses.IsEmpty())
	{
		FVector LocationToSpawn = GetActorLocation() + FVector(PlatformDistance * PlatformCount, 0.f, 0.f);

		const int Selection = FMath::RandRange(0, PlatformClasses.Num() - 1);

		if (PlatformClasses[Selection]) World->SpawnActor<AKagePlatform>(PlatformClasses[Selection], LocationToSpawn, GetActorRotation());
	}
}

void AKagePlatform::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("End overlap")));

	bPlayerInside = false;

	for (AActor* Actor : PlatformActors) Actor->SetLifeSpan(RunningTime);
}

void AKagePlatform::SetObstacles()
{
	UWorld* World = GetWorld();

	if (WallObstacleClass && !WallObstaclePositions.IsEmpty())
	{
		for (FVector WallPosition : WallObstaclePositions)
		{
			if (World) PlatformActors.Add(World->SpawnActor<AObstacle>(WallObstacleClass, GetActorLocation() + WallPosition, FRotator::ZeroRotator));
		}
	}

	if (LowerObstacleClass && !LowerObstaclePositions.IsEmpty())
	{
		for (FVector LowerPosition : LowerObstaclePositions)
		{
			if (World) PlatformActors.Add(World->SpawnActor<AObstacle>(LowerObstacleClass, GetActorLocation() + LowerPosition, FRotator::ZeroRotator));
		}
	}

	if (UpperObstacleClass && !UpperObstaclePositions.IsEmpty())
	{
		for (FVector UpperPosition : UpperObstaclePositions)
		{
			if (World) PlatformActors.Add(World->SpawnActor<AObstacle>(UpperObstacleClass, GetActorLocation() + UpperPosition, FRotator::ZeroRotator));
		}
	}

	if (DestructibleClass && !DestructiblePositions.IsEmpty())
	{
		for (FVector  DestructiblePosition : DestructiblePositions)
		{
			if (World) PlatformActors.Add(World->SpawnActor<ADestructible>(DestructibleClass, GetActorLocation() + DestructiblePosition, FRotator::ZeroRotator));
		}
	}
}
