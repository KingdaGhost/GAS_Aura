// Copyright KingdaGhost Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
/**
 *  AuraGameplayTags
 *
 *  Singleton containing native Gameplay Tags
 */

/*UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_ARMOR);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_ARMORPENETRATION);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_BLOCKCHANCE);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_CRITICALHITCHANCE);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_CRITICALHITDAMAGE);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_CRITICALHITRESISTANCE);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_HEALTHREGENERATION);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_MANAREGENERATION);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_MAXHEALTH);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ATTRIBUTES_SECONDARY_MAXMANA);*/

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth; 
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag Damage;

private:
	static FAuraGameplayTags GameplayTags;
};
