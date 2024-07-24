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

	// ACTIONS

	void EvadeUp();
	void EvadeLeft();
	void EvadeRight();
	void EvadeDown();
	void LaunchProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)	// Temp
	void OnBoxColliderUpdate();				// Temp

private:
	UFUNCTION(BlueprintCallable)
	void UpdateBoxCollider(float HalfSize, float ZOffset);

	// COMPONENTS

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollider;

	// OTHERS

	UPROPERTY(EditDefaultsOnly, Category = "Kage Character")
	class UAnimMontage* EvadeMontage;

	float ZCapsuleHeight;
};
