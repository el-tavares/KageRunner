// Vox Dei. All rights reserved.

#include "Characters/KageCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AKageCharacter::AKageCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SpringArmComponent")));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 80.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("CameraComponent")));
	Camera->SetupAttachment(SpringArm);

	const float ZOffset = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -ZOffset), FRotator(0.f, -90.f, 0.f));
}

void AKageCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void AKageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
