// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "../Projectile/Projectile_Base.h"
#include "Grenade_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API AGrenade_Projectile : public AProjectile_Base
{
	GENERATED_BODY()

	AGrenade_Projectile();

protected:
	virtual void BeginPlay() override;
	
private:
	//virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void OnTimerExpire();

	float DestroyDelay = 2.5f;
};
