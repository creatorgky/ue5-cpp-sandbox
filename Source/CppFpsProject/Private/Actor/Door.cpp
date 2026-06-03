// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Door.h"


// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRootComponent;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(GetRootComponent());
}

void ADoor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Door Interacted"));

	if (DoorMesh)
	{
		if (FMath::IsNearlyEqual(DoorMesh->GetRelativeRotation().Yaw ,90.f))
		DoorMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		else
 		DoorMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

