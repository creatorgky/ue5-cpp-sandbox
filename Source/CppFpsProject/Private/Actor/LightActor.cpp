// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/LightActor.h"

#include "Components/PointLightComponent.h"


// Sets default values
ALightActor::ALightActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightComponent"));
	LightComponent->SetupAttachment(GetRootComponent());
	LightComponent->Intensity = 10000.f;
	
}

void ALightActor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Light Interacted"));

	if (LightComponent)
	{
		if (LightComponent->Intensity == 0.f)
		{
			LightComponent->SetIntensity(10000.f);
		}
		else
		{
			LightComponent->SetIntensity(0.f);
		}
	}
	
}

// Called when the game starts or when spawned
void ALightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

