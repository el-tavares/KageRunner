// Copyright Vox Dei. All Rights Reserved.

#include "Characters/KageCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Interfaces/Interact.h"
#include "KageRunner/ModuleEditor.h"
#include "Items/Projectile.h"

AKageCharacter::AKageCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	ZCapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AKageCharacter::OnBeginOverlap);	// Binding OnBeginOverlap delegate

	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	BoxCollider->SetupAttachment(GetRootComponent());
	BoxCollider->SetCollisionObjectType(ECC_Vehicle);
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	UpdateBoxCollider(ZCapsuleHeight, 0.f);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -ZCapsuleHeight), FRotator(0.f, -90.f, 0.f));	// Set mesh to correct position and rotation

	Tags.Add(FName(TEXT("Player")));

	ADD_PROPERTY_SECTION("Kage Character");
}

void AKageCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void AKageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKageCharacter::EvadeUp()
{
	UpdateBoxCollider(ZCapsuleHeight / 2.f, (ZCapsuleHeight / 2.f) + 20.f);
	PlayMontage(EvadeMontage, FName(TEXT("EvadeUp")));
}

void AKageCharacter::EvadeLeft()
{	
	PlayMontage(EvadeMontage, FName(TEXT("EvadeLeft")));
}

void AKageCharacter::EvadeRight()
{	
	PlayMontage(EvadeMontage, FName(TEXT("EvadeRight")));
}

void AKageCharacter::EvadeDown()
{
	UpdateBoxCollider(ZCapsuleHeight / 2.f, -(ZCapsuleHeight / 2.f));
	PlayMontage(EvadeMontage, FName(TEXT("EvadeDown")));
}

void AKageCharacter::PlayMontage(UAnimMontage* Montage, FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName);

		FOnMontageEnded EndMontage;	// Create end montage delegate struct
		EndMontage.BindUObject(this, &AKageCharacter::OnEvadeEnd);	// Bind the event
		AnimInstance->Montage_SetEndDelegate(EndMontage, Montage);	// Set delegate
	}
}

void AKageCharacter::OnEvadeEnd(UAnimMontage* AnimMontage, bool Interrupted)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("Montage ended")));

	if (!Interrupted) UpdateBoxCollider(ZCapsuleHeight, 0.f);
}

void AKageCharacter::UpdateBoxCollider(float HalfSize, float ZOffset)
{
	BoxCollider->SetBoxExtent(FVector(24.f, 24.f, HalfSize));
	BoxCollider->SetRelativeLocation(FVector(0.f, 0.f, ZOffset));
}

void AKageCharacter::LaunchProjectile()
{
	PlayMontage(ThrowKunaiMontage, FName(TEXT("Default")));

	UWorld* World = GetWorld();
	if (World && ProjectileClass)
	{
		FVector LocationToSpawn = GetActorLocation();
		LocationToSpawn += GetActorForwardVector() * 100.f;	// Add forward offset

		AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, LocationToSpawn, FRotator(0.f));
		Projectile->SetLifeSpan(5.f);
	}
}

void AKageCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteract* InteractInterface = Cast<IInteract>(OtherActor);
	if (InteractInterface) InteractInterface->Interact(this);
}

void AKageCharacter::InteractExample()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString(TEXT("Interact example")));
}
