// Copyright Vox Dei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KageController.generated.h"

UCLASS()
class KAGERUNNER_API AKageController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlayingState() override;
	virtual void SetupInputComponent() override;

private:
	void HandleCharacterMovement(float DeltaTime);

	//	ACTIONS

	void EvadeUp();
	void EvadeLeft();
	void EvadeRight();
	void EvadeDown();
	void LaunchProjectile();

	class AKageCharacter* KageCharacter;

	float Speed = 100.f;
	float YOffset;
};
