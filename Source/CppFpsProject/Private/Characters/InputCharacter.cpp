// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Characters/InputCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AInputCharacter::AInputCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AInputCharacter::BeginPlay()
{
	Super::BeginPlay();

	BindInputContext();
}

// Called every frame
void AInputCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInputCharacter::BindInputContext()
{
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (PlayerController->IsLocalPlayerController())
			{
				InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
				if (InputSubsystem)
				{
					InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
					InputSubsystem->AddMappingContext(LookMappingContext, 0);
				}
			}                             
		}
}

// Called to bind functionality to input
void AInputCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AInputCharacter::CustomJump);

		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInputCharacter::CustomMove);

		EnhancedInput->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AInputCharacter::CustomMouseLook);
	}
}

void AInputCharacter::CustomJump()
{
	UE_LOG(LogTemp, Warning, TEXT("JUMP!"));
	Jump();
	
}

void AInputCharacter::CustomMove(const FInputActionValue& InputValue)
{
	UE_LOG(LogTemp, Warning, TEXT("MOVE!"));

	FVector2D Input =  InputValue.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(),Input.X);
	AddMovementInput(GetActorRightVector(),Input.Y);
}

void AInputCharacter::CustomMouseLook(const FInputActionValue& InputValue)
{
	UE_LOG(LogTemp, Warning, TEXT("LOOK! %s"), *InputValue.ToString());

	FVector2D Input = InputValue.Get<FVector2D>();

	AddControllerYawInput(Input.X);
	AddControllerPitchInput(Input.Y);
}

