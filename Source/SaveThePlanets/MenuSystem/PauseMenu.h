// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API UPauseMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonRestart;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonResume;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonQuit;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonMainMenu;

	UFUNCTION()
	void Quit();
	UFUNCTION()
	void Start();
	UFUNCTION()
	void Resume();
	UFUNCTION()
	void TravelMainMenu();

};
