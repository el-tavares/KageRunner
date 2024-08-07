// Copyright Vox Dei. All Rights Reserved.

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

	UFUNCTION()	// Using delegate FOnMontageEnded from UAnimInstance
	void OnEvadeEnd(class UAnimMontage* AnimMontage, bool Interrupted);

	void EvadeUp();
	void EvadeLeft();
	void EvadeRight();
	void EvadeDown();
	void LaunchProjectile();

	void InteractExample();	// Temp function

protected:
	virtual void BeginPlay() override;

	UFUNCTION()	// Using delegate OnComponentBeginOverlap from UPrimitiveComponent
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UFUNCTION(BlueprintCallable)	// Temp callable
	void UpdateBoxCollider(float HalfSize, float ZOffset);

	void PlayMontage(class UAnimMontage* Montage, FName SectionName);

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Kage Character")
	class UAnimMontage* EvadeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Kage Character")
	class UAnimMontage* ThrowKunaiMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Kage Character")
	TSubclassOf<class AProjectile> ProjectileClass;

	float ZCapsuleHeight;
};
