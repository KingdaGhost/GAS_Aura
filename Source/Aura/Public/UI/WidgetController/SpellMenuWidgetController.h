// Copyright KingdaGhost Studios

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabeld, FString, DescriptionString, FString, NextLevelDescriptionString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature,const FGameplayTag&, AbilityType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpellGlobeReassignedSignature,const FGameplayTag&, AbilityTag);

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;
	void OnSpellPointsChanged(int32 NewSpellPoints);
	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);
	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();
	UFUNCTION(BlueprintCallable)
	void GlobeDeselect();
	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed();
	//SlotTag is the InputTag and AbilityType is either offensive or passive
	UFUNCTION(BlueprintCallable)
	void SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType);
	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& SlotTag, const FGameplayTag& PreviousSlot);
	
	UPROPERTY(BlueprintAssignable, Category="GAS|SpellPoints")
	FOnPlayerStatChangedSignature SpellPointsChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|SpellPoints")
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|Equip")
	FWaitForEquipSelectionSignature WaitForEquipDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Equip")
	FWaitForEquipSelectionSignature StopWaitingForEquipDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|Equip")
	FSpellGlobeReassignedSignature SpellGlobeReassignedDelegate;

private:
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton);

	FSelectedAbility SelectedAbility = { FAuraGameplayTags::Get().Abilities_None, FAuraGameplayTags::Get().Abilities_Status_Locked};
	int32 CurrentSpellPoints = 0;
	bool bWaitingForEquipSelection = false;
	// The SelectedSlot is associated with InputTag since the AbilityIcons in the SpellMenu known for their InputTag
	FGameplayTag SelectedSlot;
};


