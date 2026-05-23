// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"

#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UTestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("CPP %s"), *FString(__FUNCTION__));

	if (TestButton)
	{
		TestButton->OnPressed.AddDynamic(this, &UTestWidget::OnTestButtonPressed);
	}
}

void UTestWidget::OnTestButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("CPP %s"), *FString(__FUNCTION__));
}

void UTestWidget::SetHealthPercent(float NewPercent)
{
	if (HealthBar) HealthBar->SetPercent(NewPercent);

	if (HealthText)
	{
		int NewIntPercent = FMath::RoundToInt(NewPercent * 100);
		if (NewIntPercent <=100 && NewIntPercent >=0)
		{
			HealthText->SetText(FText::FromString(FString::Printf(TEXT("Health: %i%%"), NewIntPercent)));
		}
	}
	
}

void UTestWidget::SetManaPercent(float NewPercent)
{
	if (ManaBar) ManaBar->SetPercent(NewPercent);
}

void UTestWidget::SetGold(int32 NewGold)
{
	if (GoldText) GoldText->SetText(FText::FromString(FString::Printf(TEXT("Gold: %i"), NewGold)));
}

void UTestWidget::SetScore(int32 NewScore)
{
	if (ScoreText) ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %i"), NewScore)));
}
