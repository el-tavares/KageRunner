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

	ADD_PROPERTY_SECTION("Platform");
}

void AKagePlatform::BeginPlay()
{
	Super::BeginPlay();

	if (bIsFirstPlatform) for (int i = 1; i < PlatformCount; i++) SpawnPlatform(PlatformSize * i);	// Generate count platforms minus one (first platform already exist)
}

void AKagePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().X < DestroyXLocation) Destroy();

	GetRootComponent()->AddLocalOffset(FVector(-300.f * DeltaTime, 0.f, 0.f));
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
