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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// TEMP

	UFUNCTION(BlueprintImplementableEvent)
	void OnBoxColliderUpdate();

private:
	// ACTIONS

	void EvadeUp();
	void EvadeLeft();
	void EvadeRight();
	void EvadeDown();
	void LaunchKunai();

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

	UPROPERTY(VisibleInstanceOnly, Category = "Kage Character")
	float YOffset;

	float ZCapsuleHeight;

};
