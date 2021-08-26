// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "RollABall/Items/RollABallItemBase.h"
#include "RollABallWidget.h"

void ARollABallGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollABallItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if (GameWidgetClass) 
	{
		GameWidget = Cast<URollABallWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget) 
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollABallGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ARollABallGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
