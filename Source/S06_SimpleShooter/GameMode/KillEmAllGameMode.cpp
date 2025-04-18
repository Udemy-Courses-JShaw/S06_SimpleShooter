// Copyright - Metal Muffin Entertainment ©


#include "KillEmAllGameMode.h"
#include "../AI/EnemyAIController.h"
#include "GameFramework/Controller.h"
#include "EngineUtils.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	//Player Loses
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for (AEnemyAIController* EnemyAI : TActorRange<AEnemyAIController>(GetWorld()))
	{
		if (!EnemyAI->IsDead())
		{
			return;
		}
	}
	
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

int32 AKillEmAllGameMode::GetNumEnemiesRemaining() const
{
	int32 NumEnemies = 0;
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		NumEnemies++;
	}
	return NumEnemies;
}