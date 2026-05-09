// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

class UMyCustomComponent;
class UBoxComponent;

UCLASS()
class CPPFPSPROJECT_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	//Constructor
	ATestActor();
	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION()
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UStaticMeshComponent* CubeStaticMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshii;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UBoxComponent* BoxCpp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UMyCustomComponent* MyActorComponent;

	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                     const FHitResult& SweepResult);

	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void BoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
