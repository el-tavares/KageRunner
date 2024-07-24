// Vox Dei. All rights reserved.

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

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class UGeometryCollectionComponent* DestructibleGeo;
};
