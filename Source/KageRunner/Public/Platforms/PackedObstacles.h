// Copyright Vox Dei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PackedObstacles.generated.h"

UCLASS()
class KAGERUNNER_API APackedObstacles : public AActor
{
	GENERATED_BODY()
	
public:	
	APackedObstacles();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* FloorCollider;
};
