// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Characters/InputCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TestWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Interface/InteractInterface.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInputCharacter::AInputCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TestWidgetComponent"));
	TestWidgetComponent->SetupAttachment(GetRootComponent());
	TestWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(GetRootComponent());
	SphereCollision->SetSphereRadius(1000.f);
	SphereCollision->SetHiddenInGame(false);
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

	if (SphereCollision)
	{
		SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AInputCharacter::OnSphereBeginOverlap);
	}

	FTimerHandle CustomTimerHandle;
	FTimerDelegate CustomTimerDelegate = FTimerDelegate::CreateUObject(this, &AInputCharacter::Trace, 10000.f);
	GetWorldTimerManager().SetTimer(CustomTimerHandle,CustomTimerDelegate, 0.1f, true);
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

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this,AActor::StaticClass(),FoundActors);
	UE_LOG(LogTemp, Warning, TEXT("Found Actors: %d"), FoundActors.Num());
	for (AActor* Actor : FoundActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetName());
	}
}

void AInputCharacter::Trace(float length)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 10000.f;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FColor::Emerald, 5.f, 3);
	if (HitResult.bBlockingHit)
	{
		if (HitResult.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
			HitResult.GetActor()->Destroy();
		}
	}
}

void AInputCharacter::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP! %s"), *OtherActor->GetName());

		IInteractInterface* InterfaceActor = Cast<IInteractInterface>(OtherActor);
		if (InterfaceActor)
		{
			InterfaceActor->Interact();
		}
	}
}

void AInputCharacter::CustomMove(const FInputActionValue& InputValue)
{
	FVector2D Input =  InputValue.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(),Input.X);
	AddMovementInput(GetActorRightVector(),Input.Y);
}

void AInputCharacter::CustomMouseLook(const FInputActionValue& InputValue)
{
	FVector2D Input = InputValue.Get<FVector2D>();

	AddControllerYawInput(Input.X);
	AddControllerPitchInput(Input.Y);
}

