// Vox Dei. All rights reserved.

#include "Game/KageController.h"
#include "Characters/KageCharacter.h"
#include "Items/Projectile.h"

void AKageController::BeginPlayingState()
{
	Super::BeginPlayingState();

	KageCharacter = Cast<AKageCharacter>(GetPawn());

	if (KageCharacter) YOffset = KageCharacter->GetActorLocation().Y;
}

void AKageController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleCharacterMovement(DeltaTime);
}

void AKageController::HandleCharacterMovement(float DeltaTime)
{
	if (KageCharacter)
	{
		KageCharacter->AddMovementInput(FVector(Speed * DeltaTime, 0.f, 0.f));	// Add forward movement infinitely

		FVector CurrentPostion = KageCharacter->GetActorLocation();

		if (CurrentPostion.Y != YOffset)
		{
			float YOffsetInterp = FMath::FInterpTo(CurrentPostion.Y, YOffset, DeltaTime, 8.f);
			KageCharacter->SetActorLocation(FVector(CurrentPostion.X, YOffsetInterp, CurrentPostion.Z));	// Move horizontally until reaches the Y position target
		}
	}
}

void AKageController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(FName(TEXT("EvadeUp")), IE_Pressed, this, &AKageController::EvadeUp);
	InputComponent->BindAction(FName(TEXT("EvadeLeft")), IE_Pressed, this, &AKageController::EvadeLeft);
	InputComponent->BindAction(FName(TEXT("EvadeRight")), IE_Pressed, this, &AKageController::EvadeRight);
	InputComponent->BindAction(FName(TEXT("EvadeDown")), IE_Pressed, this, &AKageController::EvadeDown);
	InputComponent->BindAction(FName(TEXT("LaunchProjectile")), IE_Pressed, this, &AKageController::LaunchProjectile);
}

void AKageController::EvadeUp()
{
	if (KageCharacter) KageCharacter->EvadeUp();
}

void AKageController::EvadeLeft()
{
	YOffset -= 200.f;
	if (KageCharacter) KageCharacter->EvadeLeft();
}

void AKageController::EvadeRight()
{
	YOffset += 200.f;
	if (KageCharacter) KageCharacter->EvadeRight();
}

void AKageController::EvadeDown()
{
	if (KageCharacter) KageCharacter->EvadeDown();
}

void AKageController::LaunchProjectile()
{
	UWorld* World = GetWorld();
	if (World && ProjectileClass && KageCharacter)
	{
		FVector LocationToSpawn = KageCharacter->GetActorLocation();
		LocationToSpawn += KageCharacter->GetActorForwardVector() * 100.f;	// Add forward offset

		AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, LocationToSpawn, FRotator(0.f));
		Projectile->SetLifeSpan(3.f);

		KageCharacter->LaunchProjectile();
	}
}
