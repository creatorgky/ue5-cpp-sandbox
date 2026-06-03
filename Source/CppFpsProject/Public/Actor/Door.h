// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "Door.generated.h"

UCLASS()
class CPPFPSPROJECT_API ADoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

	virtual void Interact() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneRootComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
