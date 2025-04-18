// Copyright - Metal Muffin Entertainment ©


#include "Shotgun.h"
#include "Gun_Base.h"
#include "../Projectile/Projectile_Base.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void AShotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Sets Timer for FullAuto Fire
	FTimerHandle ShotgunAutoTimer;
	if (bAltFire)
	{
		if (!ShotgunAutoTimer.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(
				ShotgunAutoTimer,
				this,
				&AShotgun::PullTrigger,
				AutoCycleTime,
				false,
				-1.0f
			);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ShotgunAutoTimer);
		ShotgunAutoTimer.Invalidate();
	}

}

void AShotgun::PullTrigger()
{
	//Super::PullTrigger();		//Shotguns are weird...

	if (!CanPullTrigger()) { return; }
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("Muzzle"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("Muzzle"));
	FTimerHandle CycleTimer;

	if (FiringStatus == EFiringStatus::Ready)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			MuzzleFlash,
			GunMesh->GetSocketLocation(TEXT("Muzzle")),
			GunMesh->GetSocketRotation(TEXT("Muzzle"))
		);
		if (!CycleTimer.IsValid())
		{
			//Sets cycle Timer
			FiringStatus = EFiringStatus::Cycling;
			GetWorld()->GetTimerManager().SetTimer(
				CycleTimer,
				this,
				&AGun_Base::MakeReady,
				CycleTime,
				false,
				-1.0f
			);

			//Launch Projectile
			if (Ammo > 0)
			{
				//FireProjectile();		//Blast() fires a bunch at a time
				Blast();
				Ammo--;

				//UAnimInstance
				//TODO: add animations for shooting
			}
		}
	}

	
}

void AShotgun::Alt_PullTrigger(bool bIsPulled)
{
	Super::Alt_PullTrigger(bIsPulled);

	if (FiringStatus != EFiringStatus::Ready)
	{
		return;
	}
	bAltFire = bIsPulled;
}

void AShotgun::Blast()
{
	for (size_t i = 0; i < ShotgunNumRoundsFired; i++)
	{
		Super::FireProjectile();
	}
}

int AShotgun::GetShotgunNumRoundsFired()
{
	return ShotgunNumRoundsFired;
}
