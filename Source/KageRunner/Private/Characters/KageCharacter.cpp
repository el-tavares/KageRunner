// Vox Dei. All rights reserved.

#include "Characters/KageCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

AKageCharacter::AKageCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ZCapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SpringArmComponent")));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 80.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("CameraComponent")));
	Camera->SetupAttachment(SpringArm);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	BoxCollider->SetupAttachment(GetRootComponent());
	UpdateBoxCollider(ZCapsuleHeight, 0.f);

	// Set mesh to right position and rotation
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -ZCapsuleHeight), FRotator(0.f, -90.f, 0.f));
}

void AKageCharacter::BeginPlay()
{
	Super::BeginPlay();	

	YOffset = GetActorLocation().Y;
}

void AKageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Y != YOffset)
	{
		float YOffsetInterp = FMath::FInterpTo(GetActorLocation().Y, YOffset, DeltaTime, 8.f);
		SetActorLocation(FVector(GetActorLocation().X, YOffsetInterp, GetActorLocation().Z));
	}
}

void AKageCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName(TEXT("EvadeUp")), IE_Pressed, this, &AKageCharacter::EvadeUp);
	PlayerInputComponent->BindAction(FName(TEXT("EvadeLeft")), IE_Pressed, this, &AKageCharacter::EvadeLeft);
	PlayerInputComponent->BindAction(FName(TEXT("EvadeRight")), IE_Pressed, this, &AKageCharacter::EvadeRight);
	PlayerInputComponent->BindAction(FName(TEXT("EvadeDown")), IE_Pressed, this, &AKageCharacter::EvadeDown);
	PlayerInputComponent->BindAction(FName(TEXT("Kunai")), IE_Pressed, this, &AKageCharacter::LaunchKunai);
}

void AKageCharacter::EvadeUp()
{
	UpdateBoxCollider(ZCapsuleHeight / 2.f, ZCapsuleHeight / 2.f);
	OnBoxColliderUpdate();
	Jump();
}

void AKageCharacter::EvadeLeft()
{
	YOffset -= 200.f;
}

void AKageCharacter::EvadeRight()
{
	YOffset += 200.f;
}

void AKageCharacter::EvadeDown()
{
	UpdateBoxCollider(ZCapsuleHeight / 2.f, -(ZCapsuleHeight / 2.f));
	OnBoxColliderUpdate();
}

void AKageCharacter::LaunchKunai()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString(TEXT("Launching kunai")));
}

void AKageCharacter::UpdateBoxCollider(float HalfSize, float ZOffset)
{
	BoxCollider->SetBoxExtent(FVector(24.f, 24.f, HalfSize));
	BoxCollider->SetRelativeLocation(FVector(0.f, 0.f, ZOffset));
}
