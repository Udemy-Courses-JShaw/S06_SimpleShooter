// Copyright - Metal Muffin Entertainment ©


#include "ShooterCharacter.h"
#include "../Weapon/Gun_Base.h"
#include "Components/CapsuleComponent.h"
#include "../GameMode/S06_SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	Rifle = GetWorld()->SpawnActor<AGun_Base>(RifleClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	Rifle->SetOwner(this);
	Rifle->SetActorHiddenInGame(true);

	Launcher = GetWorld()->SpawnActor<AGun_Base>(LauncherClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Launcher->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	Launcher->SetOwner(this);
	Launcher->SetActorHiddenInGame(true);

	Shotgun = GetWorld()->SpawnActor<AGun_Base>(ShotgunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Shotgun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	Shotgun->SetOwner(this);
	Shotgun->SetActorHiddenInGame(true);
	//Default Weapon
	SetCurrentWeapon(Weapon::Rifle);
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("LookUp"),		this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),	this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),	this, &AShooterCharacter::MoveRight);
	//Controller Specific
	PlayerInputComponent->BindAxis(TEXT("LookUpController"),	 this, &AShooterCharacter::LookUpController);
	PlayerInputComponent->BindAxis(TEXT("LookRightController"),  this, &AShooterCharacter::LookRightController);
	
	//Actions
	PlayerInputComponent->BindAction(TEXT("Jump"),  EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Fire);
	//PlayerInputComponent->BindAction(TEXT("Crouch"),EInputEvent::IE_Pressed, this, &ACharacter::Crouch);
	
	//Weapon Specific
	PlayerInputComponent->BindAction(TEXT("Weapon1"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Weapon1);
	PlayerInputComponent->BindAction(TEXT("Weapon2"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Weapon2);
	PlayerInputComponent->BindAction(TEXT("NextWeapon"),     EInputEvent::IE_Pressed, this, &AShooterCharacter::NextWeapon);
	PlayerInputComponent->BindAction(TEXT("PreviousWeapon"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PreviousWeapon);
	
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	if (Health >= 0)
	{
		Health -= DamageToApply;
		UE_LOG(LogTemp, Warning, TEXT("Remaining Health: %f"), Health)
	}

	if (IsDead())
	{
		AS06_SimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AS06_SimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();
	}

	return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AShooterCharacter::LookUpController(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightController(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

AGun_Base* AShooterCharacter::GetCurrentWeapon()
{
	if (CurrentWeapon == Weapon::Rifle)
	{
		if (Rifle != nullptr) { return Rifle; }
	}
	else if (CurrentWeapon == Weapon::Launcher)
	{
		if (Launcher != nullptr) { return Launcher; }
	}
	else
	{
		if (Shotgun != nullptr) { return Shotgun; }
	}

	//safe value
	return Rifle;
}

void AShooterCharacter::SetCurrentWeapon(Weapon NewValue)
{
	GetCurrentWeapon()->SetActorHiddenInGame(true);
	CurrentWeapon = NewValue;
	GetCurrentWeapon()->SetActorHiddenInGame(false);
}

void AShooterCharacter::Fire()
{
	GetCurrentWeapon()->PullTrigger();
}

void AShooterCharacter::Weapon1()
{
	SetCurrentWeapon(Weapon::Rifle);
}

void AShooterCharacter::Weapon2()
{
	SetCurrentWeapon(Weapon::Launcher);
}

void AShooterCharacter::NextWeapon()
{
	if (CurrentWeapon == Weapon::Rifle)
	{
		SetCurrentWeapon(Weapon::Launcher);
	}
	else if (CurrentWeapon == Weapon::Launcher)
	{
		SetCurrentWeapon(Weapon::Rifle);
	}
	//TODO: add Shotgun when inplemented
}

void AShooterCharacter::PreviousWeapon()
{
	if (CurrentWeapon == Weapon::Launcher)
	{
		SetCurrentWeapon(Weapon::Rifle);
	}
	else if (CurrentWeapon == Weapon::Rifle)
	{
		SetCurrentWeapon(Weapon::Launcher);
	}
	//TODO: add Shotgun when inplemented
}
