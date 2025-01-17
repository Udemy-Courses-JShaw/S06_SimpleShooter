// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "S06_SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API AKillEmAllGameMode : public AS06_SimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	UFUNCTION(BlueprintPure)
	int32 GetNumEnemiesRemaining() const;

private:
	void EndGame(bool bIsPlayerWinner);

};
