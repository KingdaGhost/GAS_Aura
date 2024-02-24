// Copyright KingdaGhost Studios


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	if(UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass))
	{
		Widget->AddToViewport();
	}
}
