// Copyright KingdaGhost Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"
class UAuraAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, int32 /*Ability level*/)
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*Status*/, const FGameplayTag& /*SlotTag*/, const FGameplayTag& /*PreviousSlot*/)
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void ForEachAbility(const FForEachAbility& Delegate);
	void UpgradeAttribute(const FGameplayTag& AttributeTag);
	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);
	void UpdateAbilityStatuses(int32 Level);
	UFUNCTION(Server, Reliable)
	void ServerSpendSpellPoint(const FGameplayTag& AbilityTag);
	UFUNCTION(Server, Reliable)
	void ServerEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& SlotTag);
	UFUNCTION(Client, Reliable)
	void ClientEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& SlotTag, const FGameplayTag& PreviousSlot);
	//Marking them static means making them as utility function
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& AbilityTag);
	FGameplayTag GetInputTagFromAbilityTag(const FGameplayTag& AbilityTag);

	bool GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLevelDescription);
	void ClearSlot(FGameplayAbilitySpec* Spec);
	void ClearAbilitiesOfSlot(const FGameplayTag& SlotTag);
	static bool AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& SlotTag);
	
	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	FAbilityStatusChanged AbilityStatusChanged;
	FAbilityEquipped AbilityEquipped;
	bool bStartupAbilitiesGiven = false;
protected:
	//This is called when our ActivatableAbilities variable is replicated. This is done when we GiveAbility();
	virtual void OnRep_ActivateAbilities() override;
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	UFUNCTION(Client, Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);
};
