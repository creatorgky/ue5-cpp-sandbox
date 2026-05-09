// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Components/MyCustomComponent.h"


// Sets default values for this component's properties
UMyCustomComponent::UMyCustomComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyCustomComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyCustomComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	UE_LOG(LogTemp, Error, TEXT("UMyCustomComponent"));
	UE_LOG(LogTemp, Warning, TEXT("DeltaTime=%f %s"),DeltaTime ,*FString(__FUNCTION__));
}

