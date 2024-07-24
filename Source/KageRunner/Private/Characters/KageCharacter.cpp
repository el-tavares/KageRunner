// Vox Dei. All rights reserved.

#include "Characters/KageCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

AKageCharacter::AKageCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	ZCapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SpringArmComponent")));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 520.f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 180.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("CameraComponent")));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(15.f, 0.f, 0.f));

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	BoxCollider->SetupAttachment(GetRootComponent());
	UpdateBoxCollider(ZCapsuleHeight, 0.f);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -ZCapsuleHeight), FRotator(0.f, -90.f, 0.f));	// Set mesh to correct position and rotation
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
	UpdateBoxCollider(ZCapsuleHeight / 2.f, ZCapsuleHeight / 2.f);
	OnBoxColliderUpdate();	// Temp
}

void AKageCharacter::EvadeLeft()
{	
}

void AKageCharacter::EvadeRight()
{	
}

void AKageCharacter::EvadeDown()
{
	UpdateBoxCollider(ZCapsuleHeight / 2.f, -(ZCapsuleHeight / 2.f));
	OnBoxColliderUpdate();	// Temp
}

void AKageCharacter::LaunchProjectile()
{
}

void AKageCharacter::UpdateBoxCollider(float HalfSize, float ZOffset)
{
	BoxCollider->SetBoxExtent(FVector(24.f, 24.f, HalfSize));
	BoxCollider->SetRelativeLocation(FVector(0.f, 0.f, ZOffset));
}
