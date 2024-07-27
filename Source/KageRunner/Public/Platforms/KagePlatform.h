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

	UFUNCTION()	// Using delegate OnComponentEndOverlap from UPrimitiveComponent
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void SpawnPlatform();

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, Category = "Platform")	// Platform classes to spawn next
	TArray<TSubclassOf<AKagePlatform>> PlatformClasses;

	UPROPERTY(EditInstanceOnly, Category = "Platform")	// Is the first platform in the world
	bool bIsFirstPlatform = false;

	UPROPERTY(EditInstanceOnly, Category = "Platform")	// Number of platforms in the world
	int32 PlatformCount = 3;

	bool bPlayerInside = false;
	float RunningTime = 0.f;
	const float PlatformDistance = 3000.f;
};
