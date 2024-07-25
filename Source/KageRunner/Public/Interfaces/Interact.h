// Copyright Vox Dei. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

UINTERFACE(MinimalAPI)
class UInteract : public UInterface
{
	GENERATED_BODY()
};

class KAGERUNNER_API IInteract
{
	GENERATED_BODY()

public:
	virtual void Interact(class AKageCharacter* KageCharacter) = 0;	// Pure virtual function
};
