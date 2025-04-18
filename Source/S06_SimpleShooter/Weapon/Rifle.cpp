// Copyright - Metal Muffin Entertainment ©


#include "Rifle.h"
#include "Gun_Base.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/ShooterCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Components/SkeletalMeshComponent.h"

void ARifle::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Sets Timer for FullAuto Fire
	FTimerHandle FullAutoTimer;
	if (bAuto)
	{
		if (!FullAutoTimer.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(
				FullAutoTimer,
				this,
				&AGun_Base::PullTrigger,
				CycleTime,
				false,
				-1.0f
			);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FullAutoTimer);
		FullAutoTimer.Invalidate();
	}
}

void ARifle::PullTrigger()
{
	Super::PullTrigger();

}

void ARifle::Alt_PullTrigger(bool bIsPulled)
{
	Super::Alt_PullTrigger(bIsPulled);
	
	bAuto = bIsPulled;

}

