// Copyright Vox Dei. All Rights Reserved.

#include "Items/PowerUp.h"
#include "Characters/KageCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

APowerUp::APowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	RootComponent = BoxCollider;
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("StaticMeshComponent")));
	ItemMesh->SetupAttachment(GetRootComponent());
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void APowerUp::BeginPlay()
{
	Super::BeginPlay();	
}

void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	AddActorLocalOffset(FVector(0.f, 0.f, HoveringAmplitude * FMath::Sin(RunningTime * HoveringFrequency)));
	AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}

void APowerUp::Interact(AKageCharacter* KageCharacter)
{
	if (InteractSound) UGameplayStatics::PlaySoundAtLocation(this, InteractSound, GetActorLocation());

	//if (KageCharacter) KageCharacter->InteractExample();

	Destroy();
}
