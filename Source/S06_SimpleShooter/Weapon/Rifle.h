// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "../Character/ShooterCharacter.h"
#include "../Weapon/Gun_Base.h"
#include "Rifle.generated.h"

class AShooterCharacter;

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API ARifle : public AGun_Base
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Tick(float DeltaTime) override;

public:
	virtual void PullTrigger() override;

	virtual void Alt_PullTrigger(bool bIsPulled) override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bAuto = false;

	
};
