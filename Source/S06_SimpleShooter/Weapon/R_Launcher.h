// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Weapon/Gun_Base.h"
#include "R_Launcher.generated.h"

UCLASS()
class S06_SIMPLESHOOTER_API AR_Launcher : public AGun_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AR_Launcher();

	virtual void PullTrigger() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool GetAlt_PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bAltTriggerIsPulled;
	virtual void Alt_PullTrigger(bool bIsPulled) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//UPROPERTY(EditAnywhere)
	//UParticleSystem* MuzzleFlash_Rear;


};
