// Copyright - Metal Muffin Entertainment ©


#include "Sniper.h"

// Called every frame
void ASniper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ASniper::GetAlt_PullTrigger()
{
	return bAltTriggerIsPulled;
}

void ASniper::Alt_PullTrigger(bool bIsPulled)
{
	bAltTriggerIsPulled = bIsPulled;
}
