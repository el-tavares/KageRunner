// Copyright Vox Dei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KagePlatform.generated.h"

UCLASS()
class KAGERUNNER_API AKagePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AKagePlatform();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()	// Using delegate OnComponentBeginOverlap from UPrimitiveComponent
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void SpawnPlatform(float XOffset);
	void SpawnOutsideActors();

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TArray<TSubclassOf<AKagePlatform>> PlatformClasses;

	UPROPERTY(EditInstanceOnly, Category = "Platform")
	bool bIsFirstPlatform = false;

	float PlatformSize = 3000.f;

	int32 PlatformCount = 4;

	float DestroyXLocation = -5000.f;

	bool bPlayerOverlapped = false;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TArray<TSubclassOf<class APackedLevelActor>> OutsideActors;

	UPROPERTY(EditAnywhere, Category = "Platform", meta = (MakeEditWidget))
	TArray<FVector> OutsideActorsLocation;

	TArray<AActor*> ActorsToDestroy;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TSubclassOf<class APackedLevelActor> OutsideScene;
};
