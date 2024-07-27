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
	BoxTrigger->SetBoxExtent(FVector(1500.f, 300.f, 300.f));
	BoxTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AKagePlatform::OnBeginOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AKagePlatform::OnEndOverlap);

	ADD_PROPERTY_SECTION("Platform");
}

void AKagePlatform::BeginPlay()
{
	Super::BeginPlay();

	if (bIsFirstPlatform)
	{
		bPlayerInside = true;
		SpawnPlatform();
	}
}

void AKagePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlayerInside) RunningTime += DeltaTime;	// Start counting time when play is inside
}

void AKagePlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("Begin overlap")));

	bPlayerInside = true;
	SpawnPlatform();
}

void AKagePlatform::SpawnPlatform()
{
	UWorld* World = GetWorld();

	if (World && !PlatformClasses.IsEmpty())	// Check if world is valid and platform classes is not empty
	{
		FVector LocationToSpawn = GetActorLocation() + FVector(PlatformDistance * PlatformCount, 0.f, 0.f);	// Set spawn location with offset

		const int Selection = FMath::RandRange(0, PlatformClasses.Num() - 1);	// Select platform class

		if (PlatformClasses[Selection]) World->SpawnActor<AKagePlatform>(PlatformClasses[Selection], LocationToSpawn, GetActorRotation());	// Spawn selected platform
	}
}

void AKagePlatform::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("End overlap")));

	bPlayerInside = false;
	SetLifeSpan(RunningTime);	// Destroy by the time player spent inside
}
