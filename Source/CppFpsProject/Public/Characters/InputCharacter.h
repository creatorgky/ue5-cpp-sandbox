// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputCharacter.generated.h"

class UWidgetComponent;
class UTestWidget;
class UEnhancedInputLocalPlayerSubsystem;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class CPPFPSPROJECT_API AInputCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AInputCharacter();
protected:
	virtual void BeginPlay() override;
	void GoldManagement();
	void ProgressBarManagement();
	void BindInputContext();

public:
	virtual void Tick(float DeltaTime) override;
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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TestWidgetClass;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* TestWidgetComponent;
	
	UFUNCTION()
	void CustomJump();

	UFUNCTION()
	void CustomMove(const FInputActionValue& InputValue);

	UFUNCTION()
	void CustomMouseLook(const FInputActionValue& InputValue);

	UPROPERTY()
	UTestWidget* CreatedTestWidget;

	UPROPERTY()
	UTestWidget* CreatedTestWidgetComp;
	
	float TimePassed = 0.f;

	int32 Gold = 0;

	int32 Score = 0;
};
