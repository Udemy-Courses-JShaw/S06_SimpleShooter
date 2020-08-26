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

	//hides default weapon attached to base mesh
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Pistol = Cast<AGun_Base>(GetWorld()->SpawnActor<AGun_Base>(PistolClass));
	Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	Pistol->SetOwner(this);
	Pistol->SetActorHiddenInGame(true);

	Rifle = Cast<AGun_Base>(GetWorld()->SpawnActor<AGun_Base>(RifleClass));
	Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	Rifle->SetOwner(this);
	Rifle->SetActorHiddenInGame(true);

	G_Launcher = Cast<AGun_Base>(GetWorld()->SpawnActor<AGun_Base>(G_LauncherClass));
	G_Launcher->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	G_Launcher->SetOwner(this);
	G_Launcher->SetActorHiddenInGame(true);

	R_Launcher = Cast<AGun_Base>(GetWorld()->SpawnActor<AGun_Base>(R_LauncherClass));
	R_Launcher->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	R_Launcher->SetOwner(this);
	R_Launcher->SetActorHiddenInGame(true);

	Shotgun = Cast<AGun_Base>(GetWorld()->SpawnActor<AGun_Base>(ShotgunClass));
	Shotgun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	Shotgun->SetOwner(this);
	Shotgun->SetActorHiddenInGame(true);

	Sniper = Cast<AGun_Base>(GetWorld()->SpawnActor<AGun_Base>(SniperClass));
	Sniper->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_R"));
	Sniper->SetOwner(this);
	Sniper->SetActorHiddenInGame(true);
	
	//Set Defaults
	Health = MaxHealth;
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
	PlayerInputComponent->BindAction(TEXT("Jump"),    EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"),    EInputEvent::IE_Pressed, this, &AShooterCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("Alt_Fire"),EInputEvent::IE_Pressed, this, &AShooterCharacter::Alt_Fire);
	PlayerInputComponent->BindAction(TEXT("Reload"),  EInputEvent::IE_Pressed, this, &AShooterCharacter::ReloadWeapon);
	
	//Weapon Specific
	PlayerInputComponent->BindAction(TEXT("Weapon1"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Weapon1);
	PlayerInputComponent->BindAction(TEXT("Weapon2"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Weapon2);
	PlayerInputComponent->BindAction(TEXT("Weapon3"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Weapon3);
	PlayerInputComponent->BindAction(TEXT("Weapon4"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Weapon4);
	PlayerInputComponent->BindAction(TEXT("Weapon5"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Weapon5);
	PlayerInputComponent->BindAction(TEXT("Weapon6"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Weapon6);
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

AGun_Base* AShooterCharacter::GetCurrentWeapon() const
{
	if (CurrentWeapon == Weapon::Pistol)
	{
		if (Pistol != nullptr) { return Pistol; }
	}
	else if (CurrentWeapon == Weapon::Rifle)
	{
		if (Rifle != nullptr) { return Rifle; }
	}
	else if (CurrentWeapon == Weapon::G_Launcher)
	{
		if (G_Launcher != nullptr) { return G_Launcher; }
	}
	else if (CurrentWeapon == Weapon::R_Launcher)
	{
		if (R_Launcher != nullptr) { return R_Launcher; }
	}
	else if (CurrentWeapon == Weapon::Shotgun)
	{
		if (Shotgun != nullptr) { return Shotgun; }
	}
	else
	{
		if (Sniper != nullptr) { return Sniper; }
	}

	//safe value
	return Rifle;
}

Weapon AShooterCharacter::GetCurrentWeaponEnum() const
{
	return CurrentWeapon;
}

void AShooterCharacter::SetCurrentWeapon(Weapon NewValue)
{
	GetCurrentWeapon()->SetActorHiddenInGame(true);
	CurrentWeapon = NewValue;
	UE_LOG(LogTemp, Warning, TEXT("Weapon: %s"), *GetCurrentWeapon()->GetFName().ToString())
	GetCurrentWeapon()->SetActorHiddenInGame(false);
}

void AShooterCharacter::Fire()
{
	GetCurrentWeapon()->PullTrigger();
}

void AShooterCharacter::Alt_Fire()
{
	GetCurrentWeapon()->Alt_PullTrigger();
}

void AShooterCharacter::ReloadWeapon()
{
	GetCurrentWeapon()->Reload();
}

void AShooterCharacter::Weapon1()
{
	SetCurrentWeapon(Weapon::Pistol);
}

void AShooterCharacter::Weapon2()
{
	SetCurrentWeapon(Weapon::Rifle);
}

void AShooterCharacter::Weapon3()
{
	SetCurrentWeapon(Weapon::G_Launcher);
}

void AShooterCharacter::Weapon4()
{
	SetCurrentWeapon(Weapon::R_Launcher);
}

void AShooterCharacter::Weapon5()
{
	SetCurrentWeapon(Weapon::Shotgun);
}

void AShooterCharacter::Weapon6()
{
	SetCurrentWeapon(Weapon::Sniper);
}

void AShooterCharacter::NextWeapon()
{
	if (CurrentWeapon == Weapon::Sniper)
	{
		SetCurrentWeapon(Weapon::Pistol);
	}
	else if (CurrentWeapon == Weapon::Pistol)
	{
		SetCurrentWeapon(Weapon::Rifle);
	}
	else if (CurrentWeapon == Weapon::Rifle)
	{
		SetCurrentWeapon(Weapon::G_Launcher);
	}
	else if (CurrentWeapon == Weapon::G_Launcher)
	{
		SetCurrentWeapon(Weapon::R_Launcher);
	}
	else if (CurrentWeapon == Weapon::R_Launcher)
	{
		SetCurrentWeapon(Weapon::Shotgun);
	}
	else if (CurrentWeapon == Weapon::Shotgun)
	{
		SetCurrentWeapon(Weapon::Sniper);
	}
}

void AShooterCharacter::PreviousWeapon()
{
	if (CurrentWeapon == Weapon::Sniper)
	{
		SetCurrentWeapon(Weapon::Shotgun);
	}
	else if (CurrentWeapon == Weapon::Shotgun)
	{
		SetCurrentWeapon(Weapon::R_Launcher);
	}
	else if (CurrentWeapon == Weapon::R_Launcher)
	{
		SetCurrentWeapon(Weapon::G_Launcher);
	}
	else if (CurrentWeapon == Weapon::G_Launcher)
	{
		SetCurrentWeapon(Weapon::Rifle);
	}
	else if (CurrentWeapon == Weapon::Rifle)
	{
		SetCurrentWeapon(Weapon::Pistol);
	}
	else if (CurrentWeapon == Weapon::Pistol)
	{
		SetCurrentWeapon(Weapon::Sniper);
	}
}
