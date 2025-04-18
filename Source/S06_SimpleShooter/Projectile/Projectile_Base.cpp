// Copyright - Metal Muffin Entertainment ©


#include "Projectile_Base.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

// Sets default values
AProjectile_Base::AProjectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	Tracer = CreateDefaultSubobject<UParticleSystemComponent>(FName("Tracer"));
	Tracer->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Tracer->bAutoActivate = false;
	Tracer->SetVisibility(true);

	ImpactEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactEffect"));
	ImpactEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactEffect->bAutoActivate = false;
	ImpactEffect->SetVisibility(true);

	// Use this component to drive this projectile's movement.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->SetUpdatedComponent(GetRootComponent());
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = ProjectileGravityScale;
	//ProjectileMovement->bShouldBounce = false;
	//ProjectileMovement->Bounciness = 0.3f;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called every frame
void AProjectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile_Base::LaunchProjectile(const FVector& ShotDirection)
{
	ProjectileMovement->Velocity = ShotDirection * ProjectileInitialSpeed;
	ProjectileMovement->Activate();

	Tracer->Activate();
}

// Called when the game starts or when spawned
void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();

	//Set LifeSpan Timer
	FTimerHandle ProjectileLifetime;
	GetWorld()->GetTimerManager().SetTimer(
		ProjectileLifetime,
		this,
		&AProjectile_Base::OnTimerExpire,
		DestroyDelay,
		false,
		-1.0f
	);
	CollisionMesh->IgnoreActorWhenMoving(GetInstigator(), true);
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile_Base::OnHit);

}

void AProjectile_Base::ProjectileEnd()
{
	ImpactEffect->ActivateSystem();
	SetRootComponent(ImpactEffect);
	ExplosionForce->FireImpulse();
	CollisionMesh->DestroyComponent();
	Tracer->SetVisibility(false);
	Tracer->Deactivate();
}

void AProjectile_Base::OnTimerExpire()
{
	//ProjectileEnd();
	Destroy();
}

void AProjectile_Base::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit->GetInstigator() != this->GetInstigator())
	{
		if (ActorHit != nullptr)
		{
			AController* OwnerController = GetWorld()->GetFirstPlayerController();
			if (!ensure(OwnerController)) { return; }
			FVector ViewportLocation;
			FRotator ViewportRotation;
			OwnerController->GetPlayerViewPoint(ViewportLocation, ViewportRotation);
			FVector ShotDirection = -ViewportRotation.Vector();

			//Do Damage
			FPointDamageEvent DamageEvent(ProjectileDamage, Hit, ShotDirection, nullptr);
			ActorHit->TakeDamage(ProjectileDamage, DamageEvent, OwnerController, this);
			UGameplayStatics::SpawnSoundAtLocation(
				GetWorld(),
				ImpactSound_Body,
				ActorHit->GetActorLocation(),
				ActorHit->GetActorRotation()
			);
			UGameplayStatics::ApplyRadialDamage(
				this,
				ProjectileDamage,
				GetActorLocation(),
				ExplosionForce->Radius,
				UDamageType::StaticClass(),
				TArray<AActor*>() //Damages all actors
			);
		}
		else
		{
			UGameplayStatics::SpawnSoundAtLocation(
				GetWorld(),
				ImpactSound_World,
				ActorHit->GetActorLocation(),
				ActorHit->GetActorRotation()
			);
		}
		//UE_LOG(LogTemp, Warning, TEXT("ActorHit: %s"), *ActorHit->GetName())
		
	}
	
	ProjectileEnd();
	//DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 15, FColor::Green, true);

}


