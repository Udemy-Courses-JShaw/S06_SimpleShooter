// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

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

	//InputBindings
	PlayerInputComponent->BindAxis(FName("LookUp"),		this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("LookRight"),	this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(FName("MoveForward"),this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"),	this, &AShooterCharacter::MoveRight); 
	
	PlayerInputComponent->BindAxis(FName("LookUpController"), this, &AShooterCharacter::LookUpController);
	PlayerInputComponent->BindAxis(FName("LookRightController"), this, &AShooterCharacter::LookRightController);


	PlayerInputComponent->BindAction(FName("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

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

void AShooterCharacter::LookUpController(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightController(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}
