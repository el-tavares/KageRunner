// Copyright Vox Dei. All Rights Reserved.

#include "Items/Obstacle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName(TEXT("SceneComponent")));
	RootComponent = SceneRoot;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("StaticMeshComponent")));
	ObstacleMesh->SetupAttachment(GetRootComponent());
	ObstacleMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ObstacleMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ObstacleMesh->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	BoxCollider->SetupAttachment(GetRootComponent());
	BoxCollider->SetCollisionObjectType(ECC_WorldStatic);
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnBeginOverlap);	//	Binding OnBeginOverlap delegate
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();	
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObstacle::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("Overlapped with obstacle")));
}
