// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    void Setup();
    virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
};