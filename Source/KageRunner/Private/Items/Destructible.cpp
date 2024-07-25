// Copyright Vox Dei. All Rights Reserved.

#include "Items/Destructible.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Items/PowerUp.h"

ADestructible::ADestructible()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName(TEXT("SceneComponent")));
	RootComponent = SceneRoot;

	DestructibleGeo = CreateDefaultSubobject<UGeometryCollectionComponent>(FName(TEXT("GeometryCollection")));
	DestructibleGeo->SetupAttachment(GetRootComponent());
	DestructibleGeo->SetGenerateOverlapEvents(true);
	DestructibleGeo->SetCollisionResponseToAllChannels(ECR_Ignore);
	DestructibleGeo->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	DestructibleGeo->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	DestructibleGeo->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);
	DestructibleGeo->bNotifyBreaks = true;
	DestructibleGeo->OnChaosBreakEvent.AddDynamic(this, &ADestructible::OnBreak);
}

void ADestructible::BeginPlay()
{
	Super::BeginPlay();
}

void ADestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestructible::OnBreak(const FChaosBreakEvent& BreakEvent)
{
	if (bBroken) return;

	UWorld* World = GetWorld();
	if (World && !PowerUpClasses.IsEmpty())
	{
		FVector LocationToSpawn = GetActorLocation() + FVector(0.f, 0.f, 100.f);

		const int Selection = FMath::RandRange(0, PowerUpClasses.Num() - 1);

		if (PowerUpClasses[Selection]) World->SpawnActor<APowerUp>(PowerUpClasses[Selection], LocationToSpawn, GetActorRotation());
	}

	bBroken = true;
}
