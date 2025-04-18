// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/Gun_Base.h"
#include "Sniper.generated.h"

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API ASniper : public AGun_Base
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool GetAlt_PullTrigger();

	virtual void Alt_PullTrigger(bool bIsPulled) override;

private:

	UPROPERTY(EditAnywhere, Category = "Firing")
	bool bAltTriggerIsPulled;
};
