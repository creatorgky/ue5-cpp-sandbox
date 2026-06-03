// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "LightActor.generated.h"

class UPointLightComponent;

UCLASS()
class CPPFPSPROJECT_API ALightActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALightActor();

	virtual void Interact() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UPointLightComponent* LightComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
