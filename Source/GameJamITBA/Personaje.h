// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Personaje.generated.h"

UCLASS()
class GAMEJAMITBA_API APersonaje : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonaje();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* cam;


	UPROPERTY(EditAnywhere)
	float movementSpeed;

	UPROPERTY(EditAnywhere)
	float rotationSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Propiedades, meta = (AllowPrivateAccess = "true"))
	bool cambioGravedad;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Propiedades, meta = (AllowPrivateAccess = "true"))
	int playerIndex;


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void VerticalAxis(float value);
	void HorizontalAxis(float value);
	void HorizonalLookAxis(float value);
	void VerticalLookAxis(float value);


	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);



	void StartJump();
	void EndJump();


	void Pausa();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
