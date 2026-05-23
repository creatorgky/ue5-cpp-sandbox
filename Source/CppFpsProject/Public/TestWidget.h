// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestWidget.generated.h"

class UButton;
class UTextBlock;
class UProgressBar;

UCLASS()
class CPPFPSPROJECT_API UTestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	void SetHealthPercent(float NewPercent);

	void SetManaPercent(float NewPercent);

	void SetGold(int32 NewGold);

	void SetScore(int32 NewScore);
	
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ManaBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UButton* TestButton;

	UFUNCTION()
	void OnTestButtonPressed();
};
