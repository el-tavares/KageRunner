// Copyright Vox Dei. All Rights Reserved.

#include "Items/Destructible.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/BoxComponent.h"
#include "Items/PowerUp.h"
#include "KageRunner/ModuleEditor.h"

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

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	BoxCollider->SetupAttachment(GetRootComponent());
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	ADD_PROPERTY_SECTION("Destructible");
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

	BoxCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	UWorld* World = GetWorld();
	if (World && !PowerUpClasses.IsEmpty())
	{
		FVector LocationToSpawn = GetActorLocation() + FVector(0.f, 0.f, 100.f);

		const int Selection = FMath::RandRange(0, PowerUpClasses.Num() - 1);

		if (PowerUpClasses[Selection]) (World->SpawnActor<APowerUp>(PowerUpClasses[Selection], LocationToSpawn, GetActorRotation()))->SetLifeSpan(3.f);
	}

	bBroken = true;
}
