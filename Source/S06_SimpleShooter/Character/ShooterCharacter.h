// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun_Base;

UENUM()
enum class Weapon : uint8
{
	Rifle,
	Launcher,
	Shotgun,
};

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

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	Weapon CurrentWeapon;

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	AGun_Base* GetCurrentWeapon();

	void SetCurrentWeapon(Weapon NewValue);

	void Fire();

	void Weapon1();

	void Weapon2();

	void NextWeapon();

	void PreviousWeapon();

private:
	void MoveForward(float AxisValue);
	
	void LookUp(float AxisValue);
	
	void LookRight(float AxisValue);
	
	void MoveRight(float AxisValue);

	UPROPERTY(EditAnywhere, Category = "Character")
	float RotationRate = 120.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 200.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float Health = MaxHealth;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void LookUpController(float AxisValue);
	
	void LookRightController(float AxisValue);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> RifleClass;
	UPROPERTY()
	AGun_Base* Rifle;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> LauncherClass;
	UPROPERTY()
	AGun_Base* Launcher;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> ShotgunClass;
	UPROPERTY()
	AGun_Base* Shotgun;

};
