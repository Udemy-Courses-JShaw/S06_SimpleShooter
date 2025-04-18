// Copyright - Metal Muffin Entertainment ©


#include "Gun_Base.h"
#include "../Projectile/Projectile_Base.h"
#include "../Character/ShooterCharacter.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Math/RandomStream.h"
#include "Engine/World.h"



// Sets default values
AGun_Base::AGun_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootGunComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));
	SetRootComponent(RootGunComponent);
	
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	GunMesh->SetupAttachment(RootGunComponent);

	Ammo = AmmoCapacity;
}

void AGun_Base::PullTrigger()
{
	if (!CanPullTrigger()) { return; }
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("Muzzle"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash_Rear, GunMesh, TEXT("MuzzleRear"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("Muzzle"));
	FTimerHandle CycleTimer;

	if (FiringStatus == EFiringStatus::Ready)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			MuzzleFlash,
			GunMesh->GetSocketLocation(TEXT("Muzzle")),
			GunMesh->GetSocketRotation(TEXT("Muzzle"))
		);
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			MuzzleFlash_Rear,
			GunMesh->GetSocketLocation(TEXT("MuzzleRear")),
			GunMesh->GetSocketRotation(TEXT("MuzzleRear"))
		);
		if (!CycleTimer.IsValid())
		{
			//Sets cycle Timer
			FiringStatus = EFiringStatus::Cycling;
			GetWorld()->GetTimerManager().SetTimer(
				CycleTimer,
				this,
				&AGun_Base::MakeReady,
				CycleTime,
				false,
				-1.0f
			);
			
			//Launch Projectile
			if (Ammo > 0)
			{
				FireProjectile();
				Ammo--;
		
				//UAnimInstance
				//TODO: add animations for shooting
			}
		}
	}
}

void AGun_Base::Alt_PullTrigger(bool bIsPulled)
{
	//Override specific to weapons
}

bool AGun_Base::CanPullTrigger()
{
	bCanPullTrigger = false; //safe value
	if (GetFiringStatus() == EFiringStatus::Ready )
	{
		bCanPullTrigger = true;
	}
	return bCanPullTrigger;
}

void AGun_Base::MakeReady()
{
	FiringStatus = EFiringStatus::Ready;
	//UE_LOG(LogTemp, Warning, TEXT("Ready."))
}

void AGun_Base::FireProjectile()
{
	if (ProjectileBluePrint == nullptr) { return; }
	if (Ammo > 0)
	{
		FHitResult LineTraceResult;
		FVector LineTraceVector;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = GetOwnerController()->GetPawn();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GunTrace(LineTraceResult, LineTraceVector);

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GunMesh->GetSocketLocation(FName("Muzzle")), LineTraceResult.ImpactPoint);
		FVector Cone = FMath::VRandCone(LookAtRotation.Vector(), ConeHalfAngleOffset, ConeHalfAngleOffset);

		AProjectile_Base* Projectile = GetWorld()->SpawnActor<AProjectile_Base>(
			ProjectileBluePrint,
			GunMesh->GetSocketLocation(FName("Muzzle")),
			LookAtRotation,
			SpawnParameters
		);
		
		Projectile->LaunchProjectile(Cone);
	}
}

EFiringStatus AGun_Base::GetFiringStatus() const
{
	return FiringStatus;
}

// Called when the game starts or when spawned
void AGun_Base::BeginPlay()
{
	Super::BeginPlay();
	
	if (RootGunComponent == nullptr || GunMesh == nullptr) { return; }
	
	Ammo = AmmoCapacity;
	MakeReady();
}

void AGun_Base::Reload()
{
	FiringStatus = EFiringStatus::Reloading;
	//UE_LOG(LogTemp, Warning, TEXT("Reload Called from Gun_Base"))
	
	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimer,
		this,
		&AGun_Base::ReloadFinished,
		ReloadDelay,
		false,
		-1.0f
	);
}

void AGun_Base::ReloadFinished()
{
	Ammo = AmmoCapacity;
	MakeReady();
}

bool AGun_Base::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!ensure(OwnerController)) return false;

	FVector ViewportLocation;
	FRotator ViewportRotation;
	OwnerController->GetPlayerViewPoint(ViewportLocation, ViewportRotation); //OUT parameters
	ShotDirection = -ViewportRotation.Vector();
	FVector End = ViewportLocation + ViewportRotation.Vector() * MaxWeaponRange;

	//LineTrace Ignores
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool Trace = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		ViewportLocation,
		End,
		ECollisionChannel::ECC_GameTraceChannel2, //BulletTrace, not Projectile
		Params
	);
	/*
	DrawDebugPoint(
		GetWorld(),
		HitResult.ImpactPoint,
		20,
		FColor::Blue,
		true
	);
	*/
	return Trace;
}

AController* AGun_Base::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!ensure(OwnerPawn)) return nullptr;
	
	return OwnerPawn->GetController();
}

Weapon AGun_Base::GetCurrentWeapon() const
{
	AShooterCharacter* Character = Cast<AShooterCharacter>(GetOwnerController()->GetPawn());
	return Character->GetCurrentWeaponEnum();
}

uint8 AGun_Base::GetCurrentAmmo() const
{
	return Ammo;
}

// Called every frame
void AGun_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetWorld()->GetTimerManager().IsTimerActive(ReloadTimer))
	{
		FiringStatus = EFiringStatus::Reloading;
		bCanPullTrigger = false;
	}
	else if (Ammo <= 0 && FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::OutOfAmmo)
	{
		Reload();
		FiringStatus = EFiringStatus::OutOfAmmo; 
		bCanPullTrigger = false;
		UE_LOG(LogTemp, Warning, TEXT("EFiringStatus::OutOfAmmo"))
	}
	else if (Ammo <= 0 && FiringStatus == EFiringStatus::Reloading)
	{
		FiringStatus = EFiringStatus::Reloading;
		bCanPullTrigger = false;
	}
	else if (GetFiringStatus() == EFiringStatus::Reloading || GetFiringStatus() == EFiringStatus::Cycling)
	{
		bCanPullTrigger = false;
	}
	
	if (GetFiringStatus() == EFiringStatus::Ready)
	{
		bCanPullTrigger = true;
	}
	if (GetFiringStatus() != EFiringStatus::Ready)
	{
		bCanPullTrigger = false;
	}

}


