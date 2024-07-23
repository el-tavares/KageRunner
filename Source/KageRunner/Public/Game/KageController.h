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

private:
	APawn* ControlledPawn;

	UPROPERTY(VisibleDefaultsOnly, Category = "KageController")
	float Speed = 100.f;
};
