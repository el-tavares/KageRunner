// Vox Dei. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KageController.generated.h"

/**
 * 
 */
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

	UPROPERTY(EditDefaultsOnly, Category = "Kage Controller")
	TSubclassOf<class AProjectile> ProjectileClass;

	float Speed = 100.f;
	float YOffset;
};
