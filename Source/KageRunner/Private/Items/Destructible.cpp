// Copyright Vox Dei. All Rights Reserved.

#include "Items/Destructible.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

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
}

void ADestructible::BeginPlay()
{
	Super::BeginPlay();
}

void ADestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
