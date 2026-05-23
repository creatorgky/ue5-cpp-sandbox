// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Characters/InputCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TestWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"


// Sets default values
AInputCharacter::AInputCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TestWidgetComponent"));
	TestWidgetComponent->SetupAttachment(GetRootComponent());
	TestWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}


// Called when the game starts or when spawned
void AInputCharacter::BeginPlay()
{
	Super::BeginPlay();

	BindInputContext();

	//Create WBP_TestWidget
	UUserWidget* CreatedUserWidget = CreateWidget<UUserWidget>(GetWorld(), TestWidgetClass);
	if (CreatedUserWidget)
	{
		CreatedTestWidget = Cast<UTestWidget>(CreatedUserWidget);
		if (CreatedTestWidget)
		{
			CreatedTestWidget->AddToViewport();
			CreatedTestWidget->SetHealthPercent(0.2f);
			CreatedTestWidget->SetManaPercent(0.5f);
			CreatedTestWidget->SetGold(0.5f);
			CreatedTestWidget->SetScore(0.5f);
		}
	}
	if (TestWidgetComponent)
	{
		if (UUserWidget* UserWidgetObject = TestWidgetComponent->GetUserWidgetObject())
		{
		CreatedTestWidgetComp = Cast<UTestWidget>(UserWidgetObject);
		}
	}
}



void AInputCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimePassed += DeltaTime;

	GoldManagement();

	ProgressBarManagement();
}

void AInputCharacter::GoldManagement()
{
	int Speed = static_cast<int>(GetVelocity().Size());
	Gold += Speed;
	if (CreatedTestWidget) CreatedTestWidget->SetGold(Gold);
	if (CreatedTestWidgetComp)
	{
		CreatedTestWidgetComp->SetGold(Gold/10);
	}
}

void AInputCharacter::ProgressBarManagement()
{
	if (CreatedTestWidget)
	{
		CreatedTestWidget->SetHealthPercent(TimePassed / 10.f);
		CreatedTestWidget->SetManaPercent(TimePassed / 20.f);
	}
	if (CreatedTestWidgetComp)
	{
		CreatedTestWidgetComp->SetHealthPercent(TimePassed / 30.f);
		CreatedTestWidgetComp->SetManaPercent(TimePassed / 40.f);
	}
	
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
	Score++;
	if (CreatedTestWidget)
	{
		CreatedTestWidget->SetScore(Score);
	}
	if (CreatedTestWidgetComp)
	{
		CreatedTestWidgetComp->SetScore(Score*50);
	}
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

