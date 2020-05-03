// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* MainStartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainHighscoreButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainQuitButton;

	UFUNCTION()
	void Quit();
	UFUNCTION()
	void Start();
	UFUNCTION()
	void Highscore();
};
