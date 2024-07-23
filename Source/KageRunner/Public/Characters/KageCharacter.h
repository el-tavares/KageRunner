// Vox Dei. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KageCharacter.generated.h"

UCLASS()
class KAGERUNNER_API AKageCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AKageCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
};
