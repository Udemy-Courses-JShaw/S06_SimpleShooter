// Copyright - Metal Muffin Entertainment ©


#include "G_Launcher.h"
#include "Kismet/GameplayStatics.h"
#include "../Projectile/Grenade_Projectile.h"


void AG_Launcher::PullTrigger()
{
	if (!CanPullTrigger()) { return; }
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("Muzzle"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash_Rear, GunMesh, TEXT("MuzzleRear"));
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
				FireProjectile();
				Ammo--;

				//UAnimInstance
				//TODO: add animations for shooting
			}
		}
	}
}

void AG_Launcher::Alt_PullTrigger(bool bIsPulled)
{
	bAltTriggerIsPulled = bIsPulled;
	{
		//TArray<AGrenade_Projectile> FoundActors;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), FoundActors);
		////AProjectile_Base* (FoundActors); 
		//for (AActor* Referenced_Projectile : FoundActors)
		//{
		//	AProjectile_Base* (Referenced_Projectile);
		//	Referenced_Projectile->ProjectileEnd();
		//}

		//FoundActors->ProjectileEnd();
	}
}

bool AG_Launcher::GetAlt_PullTrigger()
{
	return bAltTriggerIsPulled;
}