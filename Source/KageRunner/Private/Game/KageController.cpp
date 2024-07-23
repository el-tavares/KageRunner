// Vox Dei. All rights reserved.

#include "Game/KageController.h"

void AKageController::BeginPlayingState()
{
	Super::BeginPlayingState();

	ControlledPawn = GetPawn();
}

void AKageController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ControlledPawn->AddMovementInput(FVector(Speed * DeltaTime, 0.f, 0.f));
}
