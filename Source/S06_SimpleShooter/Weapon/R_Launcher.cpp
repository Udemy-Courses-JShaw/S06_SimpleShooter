// Copyright - Metal Muffin Entertainment ©


#include "R_Launcher.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AR_Launcher::AR_Launcher()
{
 	// Set this actor to call Tick() everyframe.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	

}

void AR_Launcher::PullTrigger()
{
	Super::PullTrigger();
}

// Called when the game starts or when spawned
void AR_Launcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AR_Launcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AR_Launcher::GetAlt_PullTrigger()
{
	return bAltTriggerIsPulled;
}

void AR_Launcher::Alt_PullTrigger(bool bIsPulled)
{
	bAltTriggerIsPulled = bIsPulled;
}