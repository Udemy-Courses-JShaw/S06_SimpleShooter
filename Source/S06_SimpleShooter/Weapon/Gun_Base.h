// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Projectile/Projectile_Base.h"
#include "../Character/ShooterCharacter.h"
#include "Gun_Base.generated.h"

class UParticleSystem;
class AProjectile_Base;

UENUM(BlueprintType)
enum class EFiringStatus : uint8
{
	OutOfAmmo,
	Reloading,
	Cycling,
	Ready,
};

UCLASS()
class S06_SIMPLESHOOTER_API AGun_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun_Base();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void PullTrigger();

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Alt_PullTrigger(bool bIsPulled);

	bool CanPullTrigger();
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	void Reload();

	void MakeReady();

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void FireProjectile();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	EFiringStatus GetFiringStatus() const;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadDelay = 1.25f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float CycleTime = .5f;

	UFUNCTION(BlueprintCallable, Category = "Action")
	AController* GetOwnerController() const;

	Weapon GetCurrentWeapon() const;

	UFUNCTION(BlueprintPure, Category = "Firing")
	uint8 GetCurrentAmmo() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringStatus FiringStatus = EFiringStatus::Ready;

	void ReloadFinished();

	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);

	bool bCanPullTrigger;

	UPROPERTY(EditAnywhere, Category = "Firing")
	uint8 AmmoCapacity;
	
	UPROPERTY(EditAnywhere, Category = "Firing")
	uint8 Ammo;
	
	UPROPERTY(VisibleAnywhere, Category = "Firing")
	USceneComponent* RootGunComponent;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Firing")
	UParticleSystem* MuzzleFlash;
	
	UPROPERTY(EditAnywhere, Category = "Firing")
	UParticleSystem* MuzzleFlash_Rear;

	UPROPERTY(EditAnywhere, Category = "Firing")
	USoundBase* MuzzleSound;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 32000.f;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ConeHalfAngleOffset = .2f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile_Base> ProjectileBluePrint;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float MaxWeaponRange = 10000;

	FTimerHandle ReloadTimer;
	

};
