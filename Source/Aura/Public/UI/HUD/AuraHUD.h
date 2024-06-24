// Copyright KingdaGhost Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraWidgetController;
class UAttributeMenuWidgetController;
class UAuraUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	template <typename T>
	T* GetOrCreateWidgetController(const FWidgetControllerParams& WCParams, TObjectPtr<T>& WidgetController, TSubclassOf<T> WidgetControllerClass);
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:

	/** This is the view */
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	/** This is the Controller known as WidgetController in the MVC model we are using for this project */
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;


	UPROPERTY(EditAnywhere, Category="WidgetController")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere, Category="WidgetController")
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
};


