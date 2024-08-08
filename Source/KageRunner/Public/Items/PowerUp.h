// Copyright Vox Dei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interact.h"
#include "PowerUp.generated.h"

UCLASS()
class KAGERUNNER_API APowerUp : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	APowerUp();

	virtual void Tick(float DeltaTime) override;
	virtual void Interact(class AKageCharacter* KageCharacter) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* InteractSound;

	float RunningTime, RotationSpeed = 100.f, HoveringAmplitude = .5f, HoveringFrequency = 5.f;
};
