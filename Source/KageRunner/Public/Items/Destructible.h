// Copyright Vox Dei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Destructible.generated.h"

UCLASS()
class KAGERUNNER_API ADestructible : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestructible();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class UGeometryCollectionComponent* DestructibleGeo;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollider;

	UFUNCTION()	// Using delegate OnChaosBreakEvent from UGeometryCollectionComponent
	void OnBreak(const FChaosBreakEvent& BreakEvent);

	UPROPERTY(EditDefaultsOnly, Category = "Destructible")
	TArray<TSubclassOf<class APowerUp>> PowerUpClasses;

	bool bBroken;
};
