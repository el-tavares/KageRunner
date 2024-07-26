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
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TArray<TSubclassOf<AKagePlatform>> PlatformClasses;

	UPROPERTY(EditAnywhere, Category = "Platform")	// Default is 10m (1000cm)
	float PlatformDistance = 1000.f;	

	UPROPERTY(VisibleAnywhere, Category = "Platform")	// Default is 3 platforms in world
	int32 PlatformCount = 3;	

	UPROPERTY(EditAnywhere, Category = "Platform", meta = (MakeEditWidget))	// Positions that walls will be spawned
	TArray<FVector> WallObstaclePositions;

	UPROPERTY(EditAnywhere, Category = "Platform", meta = (MakeEditWidget))	// Positions that lower obstacles will be spawned
	TArray<FVector> LowerObstaclePositions;

	UPROPERTY(EditAnywhere, Category = "Platform", meta = (MakeEditWidget))	// Positions that upper obstacles will be spawned
	TArray<FVector> UpperObstaclePositions;

	UPROPERTY(EditAnywhere, Category = "Platform", meta = (MakeEditWidget))	// Positions that destructibles will be spawned
	TArray<FVector> DestructiblePositions;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TSubclassOf<class AObstacle> WallObstacleClass;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TSubclassOf<class AObstacle> LowerObstacleClass;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TSubclassOf<class AObstacle> UpperObstacleClass;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TSubclassOf<class ADestructible> DestructibleClass;

	void SetObstacles();

	bool bPlayerInside = false;
	float RunningTime = 0.f;
};
