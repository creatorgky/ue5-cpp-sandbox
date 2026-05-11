// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TestActors/TestActor.h"

#include "Components/BoxComponent.h"
#include "Public/Components/MyCustomComponent.h"


ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("ATestActor constructor called"));

	SkeletalMeshii = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshiz"));
	RootComponent = SkeletalMeshii;

	CubeStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	CubeStaticMesh->SetupAttachment(RootComponent);
	CubeStaticMesh->SetAngularDamping(50.0f);

	BoxCpp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCpp->SetupAttachment(RootComponent);
	BoxCpp->SetLineThickness(5.0f);
	BoxCpp->SetHiddenInGame(false);

	MyActorComponent = CreateDefaultSubobject<UMyCustomComponent>(TEXT("CustomCppComponent"));
	MyActorComponent->SetupAttachment(BoxCpp);

}
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ATestActor::BeginPlay() called"));

	if (BoxCpp)
	{
		BoxCpp->OnComponentBeginOverlap.AddDynamic(this, &ATestActor::BoxBeginOverlap);

		BoxCpp->OnComponentEndOverlap.AddDynamic(this, &ATestActor::BoxEndOverlap);

		BoxCpp->OnComponentHit.AddDynamic(this, &ATestActor::BoxHit);
	}
	
}

void ATestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("EndPlay() called"));
}

void ATestActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("ATestActor::Tick() called with DeltaSeconds: %f"), DeltaSeconds);

	//if (MyActorComponent) UE_LOG(LogTemp, Warning, TEXT("MyCustomComponentHealth=%f"), MyActorComponent->health);
}

void ATestActor::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BoxCpp Begin Overlap"));
}

void ATestActor::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("BoxCpp End Overlap"));
}

void ATestActor::BoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("BoxCpp Hit"));
}



