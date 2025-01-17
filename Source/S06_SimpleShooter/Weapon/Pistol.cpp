// Copyright - Metal Muffin Entertainment ©


#include "Pistol.h"

void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int BurstRounds = BurstFireNumRounds;

	//Sets Timer for FullAuto Fire
	FTimerHandle BurstTimer;
	if (bAltFire)
	{
		if (!BurstTimer.IsValid() && BurstRounds > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(
				BurstTimer,
				this,
				&APistol::PullTrigger,
				CycleTime,
				false,
				-1.0f
			);
			BurstRounds--;
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimer);
		BurstTimer.Invalidate();
		BurstRounds = BurstFireNumRounds;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Alt_Trigger Released - Pistol"))
}

void APistol::Alt_PullTrigger(bool bIsPulled)
{
	Super::Alt_PullTrigger(bIsPulled);

	bAltFire = bIsPulled;

}