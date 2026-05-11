// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputCharacter.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class CPPFPSPROJECT_API AInputCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInputCharacter();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void BindInputContext();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem;
	
	UPROPERTY(EditAnywhere)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* LookMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* MouseLookAction;

	UFUNCTION()
	void CustomJump();

	UFUNCTION()
	void CustomMove(const FInputActionValue& InputValue);

	UFUNCTION()
	void CustomMouseLook(const FInputActionValue& InputValue);
};
