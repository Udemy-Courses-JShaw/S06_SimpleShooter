// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class S06_SIMPLESHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AcceptanceRadius = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* AIBehavior;

};
