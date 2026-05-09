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

void AInputCharacter::BindInputContext()
{
	//if (AController* Controller = GetController())
	//{
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (PlayerController->IsLocalPlayerController())
				if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
				{
					Subsystem->AddMappingContext(DefaultMappingContext, 0);
				}
			
		}
	//}
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

// Called to bind functionality to input
void AInputCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AInputCharacter::CustomJump);
	}
}

void AInputCharacter::CustomJump()
{
	UE_LOG(LogTemp, Warning, TEXT("JUMP!"));
}

