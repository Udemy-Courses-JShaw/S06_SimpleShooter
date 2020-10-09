// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun_Base;

UENUM()
enum class Weapon : uint8
{
	Pistol,
	Rifle,
	G_Launcher,
	R_Launcher,
	Shotgun,
	Sniper,
};

UCLASS()
class S06_SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	Weapon CurrentWeapon;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AGun_Base* GetCurrentWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	Weapon GetCurrentWeaponEnum() const;

	void SetCurrentWeapon(Weapon NewValue);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Alt_Fire_Pressed();
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	void Alt_Fire_Released();

	void ReloadWeapon();
	void Weapon1();
	void Weapon2();
	void Weapon3();
	void Weapon4(); 
	void Weapon5();
	void Weapon6();
	void NextWeapon();
	void PreviousWeapon();

private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpController(float AxisValue);
	void LookRightController(float AxisValue);

	UPROPERTY(EditAnywhere, Category = "Character")
	float RotationRate = 120.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 200.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float Health = MaxHealth;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> PistolClass;

	UPROPERTY()
	AGun_Base* Pistol;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> RifleClass;

	UPROPERTY()
	AGun_Base* Rifle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> G_LauncherClass;

	UPROPERTY()
	AGun_Base* G_Launcher;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> R_LauncherClass;

	UPROPERTY()
	AGun_Base* R_Launcher;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> ShotgunClass;

	UPROPERTY()
	AGun_Base* Shotgun;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun_Base> SniperClass;

	UPROPERTY()
	AGun_Base* Sniper;

};
