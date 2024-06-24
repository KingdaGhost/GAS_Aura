// Copyright KingdaGhost Studios


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

template <typename T>
T* AAuraHUD::GetOrCreateWidgetController(const FWidgetControllerParams& WCParams,
	TObjectPtr<T>& WidgetController, TSubclassOf<T> WidgetControllerClass)
{
	if (WidgetController == nullptr)
	{
		// NewObject<>() is used to create a UObject
		WidgetController = NewObject<T>(this, WidgetControllerClass);
		WidgetController->SetWidgetControllerParams(WCParams);
		WidgetController->BindCallbacksToDependencies();
	}
	return WidgetController;
}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	return GetOrCreateWidgetController<UOverlayWidgetController>(WCParams, OverlayWidgetController, OverlayWidgetControllerClass);
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	return GetOrCreateWidgetController<UAttributeMenuWidgetController>(WCParams, AttributeMenuWidgetController, AttributeMenuWidgetControllerClass);
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS); // This constructs the constructor of the struct FWidgetControllerParams in the AuraWidgetController class by initializing all the member variables of its struct
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController); // Setting the Widget Controller in the AuraUserWidget class

	WidgetController->BroadcastInitialValue();
	
	/*UAttributeMenuWidgetController* AttributeMenuWC = GetAttributeMenuWidgetController(WidgetControllerParams);
	AttributeMenuWC->BroadcastInitialValue();*/
		
	Widget->AddToViewport();
	
}
