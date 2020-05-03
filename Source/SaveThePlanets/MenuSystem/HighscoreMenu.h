// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "HighscoreMenu.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API UHighscoreMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:

	virtual bool Initialize() override;

private:

	UFUNCTION()
	void MainMenu();


	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;
};
