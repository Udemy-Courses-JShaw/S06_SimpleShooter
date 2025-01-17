// Copyright - Metal Muffin Entertainment ©


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDScreen = CreateWidget(this, HUDScreenClass);
	if (HUDScreen != nullptr)
	{
		HUDScreen->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	HUDScreen->RemoveFromViewport();
	if (bIsWinner)
	{
		UUserWidget* WinScreen  = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else if(!bIsWinner)
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}
	
}

float AShooterPlayerController::GetRestartDelay()
{
	return RestartDelay;
}

