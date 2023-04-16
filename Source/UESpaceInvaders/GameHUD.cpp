// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Engine.h"
#include "UESpaceInvadersGameMode.h"
#include <Internationalization/Text.h>

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	if (UWorld* World = GetWorld())
	{
		AUESpaceInvadersGameMode* Mode = Cast<AUESpaceInvadersGameMode>(World->GetAuthGameMode());
		FText ScoreText = FText::Format(FText::FromString(TEXT("Score: {0}")), FText::AsNumber(Mode->GetScore()));

		FCanvasTextItem ScoreItem(FVector2D(0, 0), ScoreText, GEngine->GetMediumFont(), FLinearColor::White);
		ScoreItem.Position = FVector2D(0, 0);
		Canvas->DrawItem(ScoreItem);

		FText LivesText = FText::Format(FText::FromString(TEXT("Lives: {0}")), FText::AsNumber(Mode->GetPlayerLives()));
		FCanvasTextItem LivesItem(FVector2D(0, 0), LivesText, GEngine->GetMediumFont(), FLinearColor::White);
		LivesItem.Position = FVector2D(0, ScoreItem.DrawnSize.Y);
		Canvas->DrawItem(LivesItem);
	}
}
