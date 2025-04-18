// Copyright - Metal Muffin Entertainment ©


#include "Grenade_Projectile.h"
#include "Kismet/GameplayStatics.h"

AGrenade_Projectile::AGrenade_Projectile()
{
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = .75f;
}

void AGrenade_Projectile::BeginPlay()
{
	//Super::BeginPlay(); 

	//Set LifeSpan Timer
	FTimerHandle ProjectileLifetime;
	GetWorld()->GetTimerManager().SetTimer(
		ProjectileLifetime,
		this,
		&AGrenade_Projectile::OnTimerExpire,
		DestroyDelay,
		false,
		-1.0f
	);
	CollisionMesh->IgnoreActorWhenMoving(GetInstigator(), true);
	//CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile_Base::OnHit);

}

void AGrenade_Projectile::OnTimerExpire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Should go Boom"))
	//ProjectileEnd();
	Destroy();
}

//void AGrenade_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//	AActor* ActorHit = Hit.GetActor();
//
//	if (ActorHit->GetInstigator() != this->GetInstigator())
//	{
//		if (ActorHit != nullptr)
//		{
//			AController* OwnerController = GetWorld()->GetFirstPlayerController();
//			if (!ensure(OwnerController)) { return; }
//			FVector ViewportLocation;
//			FRotator ViewportRotation;
//			OwnerController->GetPlayerViewPoint(ViewportLocation, ViewportRotation);
//			FVector ShotDirection = -ViewportRotation.Vector();
//
//			//Do Damage
//			FPointDamageEvent DamageEvent(ProjectileDamage, Hit, ShotDirection, nullptr);
//			ActorHit->TakeDamage(ProjectileDamage, DamageEvent, OwnerController, this);
//			UGameplayStatics::SpawnSoundAtLocation(
//				GetWorld(),
//				ImpactSound_Body,
//				ActorHit->GetActorLocation(),
//				ActorHit->GetActorRotation()
//			);
//			UGameplayStatics::ApplyRadialDamage(
//				this,
//				ProjectileDamage,
//				GetActorLocation(),
//				ExplosionForce->Radius,
//				UDamageType::StaticClass(),
//				TArray<AActor*>() //Damages all actors
//			);
//		}
//		else
//		{
//			UGameplayStatics::SpawnSoundAtLocation(
//				GetWorld(),
//				ImpactSound_World,
//				ActorHit->GetActorLocation(),
//				ActorHit->GetActorRotation()
//			);
//		}
//		//UE_LOG(LogTemp, Warning, TEXT("ActorHit: %s"), *ActorHit->GetName())
//
//	}
//
//	ProjectileEnd();
//}
