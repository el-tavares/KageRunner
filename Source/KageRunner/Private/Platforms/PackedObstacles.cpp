// Copyright Vox Dei. All Rights Reserved.

#include "Platforms/PackedObstacles.h"
#include "Components/BoxComponent.h"

APackedObstacles::APackedObstacles()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName(TEXT("SceneComponent")));
	RootComponent = SceneRoot;

	FloorCollider = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	FloorCollider->SetupAttachment(GetRootComponent());
	FloorCollider->SetBoxExtent(FVector(1500.f, 960.f, 30.f));
	FloorCollider->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	FloorCollider->SetGenerateOverlapEvents(false);
	FloorCollider->SetCollisionObjectType(ECC_WorldStatic);
	FloorCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FloorCollider->SetCollisionResponseToAllChannels(ECR_Block);
}

void APackedObstacles::BeginPlay()
{
	Super::BeginPlay();	
}

void APackedObstacles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
