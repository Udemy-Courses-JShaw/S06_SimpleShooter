// Copyright - Metal Muffin Entertainment ©

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Controller.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile_Base.generated.h"

class AProjectile;
class UParticleSystem;
class AController;

UCLASS()
class S06_SIMPLESHOOTER_API AProjectile_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile_Base();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void LaunchProjectile(const FVector& ShotDirection);

	UFUNCTION(BlueprintCallable, Category = "On Hit")
	void ProjectileEnd();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	float ProjectileGravityScale = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactEffect = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* Tracer = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound_Body;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound_World;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 15.f;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileInitialSpeed = 3000.f;

	void OnTimerExpire();

	UFUNCTION(BlueprintCallable, Category = "On Hit")
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
