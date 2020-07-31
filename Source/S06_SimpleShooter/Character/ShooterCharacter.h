// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class S06_SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Fire();
private:
	void MoveForward(float AxisValue);
	
	void LookUp(float AxisValue);
	
	void LookRight(float AxisValue);
	
	void MoveRight(float AxisValue);

	UPROPERTY(EditAnywhere)
	float RotationRate = 120.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 200.f;

	UPROPERTY(VisibleAnywhere)
	float Health = 200.f;

	void LookUpController(float AxisValue);
	
	void LookRightController(float AxisValue);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};
