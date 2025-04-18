// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/Gun_Base.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API APistol : public AGun_Base
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bAltFire = false;
	int BurstFireNumRounds = 5;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float BurstCycleTime = 0.2f;

	void Alt_PullTrigger(bool bIsPulled);

protected:

};
