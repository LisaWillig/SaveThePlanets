// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"



void UMenuWidget::SetMenuInterface(IMenuInterface* Interface) {
	this->MenuInterface = Interface;
}

void UMenuWidget::Setup() {
	AddToViewport();
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(this->TakeWidget());

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;

}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) {
	RemoveFromViewport();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}