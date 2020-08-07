// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "S06_SimpleShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API AS06_SimpleShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled);
};
