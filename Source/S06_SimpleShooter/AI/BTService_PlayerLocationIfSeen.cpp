// Copyright - Metal Muffin Entertainment ©


#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Character/ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!ensure(OwnerComp.GetAIOwner())) return;
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) return;


	if (AIController->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}