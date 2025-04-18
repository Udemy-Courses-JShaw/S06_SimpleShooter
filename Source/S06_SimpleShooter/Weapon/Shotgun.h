// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/Gun_Base.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API AShotgun : public AGun_Base
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetShotgunNumRoundsFired();

private:
	virtual void PullTrigger() override;

	void Alt_PullTrigger(bool bIsPulled);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Blast();

	UPROPERTY(EditAnywhere, Category = "Firing")
	uint8 ShotgunNumRoundsFired = 5;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float BurstCycleTime = 0.015f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float AutoCycleTime = 0.1f;

	bool bAltFire = false;
};
