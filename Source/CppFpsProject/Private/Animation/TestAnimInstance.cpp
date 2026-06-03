// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TestAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTestAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PawnOwner = TryGetPawnOwner();
	if (PawnOwner)
	{
		if (ACharacter* CharacterOwner = Cast<ACharacter>(PawnOwner)) CharacterMovement = CharacterOwner->GetCharacterMovement();
	}
}

void UTestAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{                                 
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PawnOwner)
	{
		Speed = PawnOwner->GetVelocity().Size();
		Direction =	UKismetAnimationLibrary::CalculateDirection(PawnOwner->GetVelocity(), PawnOwner->GetActorRotation());
		if (CharacterMovement)
		{
			bIsFalling = CharacterMovement->IsFalling();
			CharacterMovement->GetCurrentAcceleration() != FVector::ZeroVector && Speed>0.f ? bShouldMove = true : bShouldMove = false;
		}	
	}
}
