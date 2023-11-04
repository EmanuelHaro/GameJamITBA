// Fill out your copyright notice in the Description page of Project Settings.


#include "Personaje.h"

// Sets default values
APersonaje::APersonaje()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	movementSpeed = 100;
	rotationSpeed = 100;


	cam = CreateDefaultSubobject<UCameraComponent>("Camera");
	cam->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APersonaje::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APersonaje::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APersonaje::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APersonaje::MoveForward); //W S Up Down
	PlayerInputComponent->BindAxis("MoveRight", this, &APersonaje::MoveRight); // A D Left Right

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APersonaje::HorizonalLookAxis); //Mouse X
	//PlayerInputComponent->BindAxis("TurnRate", this, &APersonaje::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APersonaje::VerticalLookAxis); //Mouse Y
	//PlayerInputComponent->BindAxis("LookUpRate", this, &APersonaje::LookUpAtRate);

}


void APersonaje::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		if (cambioGravedad) // Si la variable "gravedad" es verdadera
		{
			// Limita el valor de entrada a -1 para aplicar la gravedad invertida
			Value = FMath::Clamp(Value, -1.f, 1.f);
		}
		AddMovementInput(Direction, Value);
	}
}

void APersonaje::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction

		if (cambioGravedad) // Si la variable "gravedad" es verdadera
		{
			// Limita el valor de entrada a -1 para aplicar la gravedad invertida
			Value = FMath::Clamp(Value, 1.f, -1.f);
		}
		AddMovementInput(Direction, Value);
	}
}



void APersonaje::VerticalAxis(float value) {
	float deltaS = GetWorld()->GetDeltaSeconds();
	if (cambioGravedad) // Si la variable "gravedad" es verdadera
	{
		// Limita el valor de entrada a -1 para aplicar la gravedad invertida
		value = FMath::Clamp(value, -1.f, 1.f);
	}

	FVector movement = GetActorForwardVector() * movementSpeed * deltaS * value;
	AddMovementInput(movement);
}

void APersonaje::HorizontalAxis(float value) {
	float deltaS = GetWorld()->GetDeltaSeconds();

	if (cambioGravedad) // Si la variable "gravedad" es verdadera
	{
		// Limita el valor de entrada a -1 para aplicar la gravedad invertida
		value = FMath::Clamp(value, -1.f, 1.f);
	}

	FVector movement = GetActorRightVector() * movementSpeed * deltaS * value;
	AddMovementInput(movement);

}

void APersonaje::HorizonalLookAxis(float value) {

	float deltaS = GetWorld()->GetDeltaSeconds();
	if (cambioGravedad) // Si la variable "gravedad" es verdadera
	{
		// Limita el valor de entrada a -1 para aplicar la gravedad invertida
		value = FMath::Clamp(value, -1.f, 1.f);
	}
	AddControllerYawInput(rotationSpeed * value * deltaS);
}


void APersonaje::VerticalLookAxis(float value) {
	float deltaS = GetWorld()->GetDeltaSeconds();
	if (cambioGravedad) // Si la variable "gravedad" es verdadera
	{
		// Limita el valor de entrada a -1 para aplicar la gravedad invertida
		value = FMath::Clamp(value, -1.f, 1.f);
	}
	AddControllerPitchInput(value * deltaS * rotationSpeed);
}
