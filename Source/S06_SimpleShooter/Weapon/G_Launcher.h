// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/Gun_Base.h"
#include "G_Launcher.generated.h"

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API AG_Launcher : public AGun_Base
{
	GENERATED_BODY()
public:
	virtual void PullTrigger() override;

	virtual void Alt_PullTrigger(bool bIsPulled) override;
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool GetAlt_PullTrigger();

private:
	bool bAltTriggerIsPulled;
};
