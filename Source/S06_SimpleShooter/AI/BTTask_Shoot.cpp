// Copyright - Metal Muffin Entertainment ©


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "../Character/ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!ensure(OwnerComp.GetAIOwner())) return EBTNodeResult::Failed;

	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ensure(Character)) return EBTNodeResult::Failed;

	Character->Fire();

	return EBTNodeResult::Succeeded;
}