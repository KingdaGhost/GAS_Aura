// Copyright KingdaGhost Studios


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"
#include "NativeGameplayTags.h"

// This is how we initialize a static variable
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

//The below works in conjunction with the UE_DECLARE_GAMEPLAY_TAG_EXTERN(TagName);
/*UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_ARMOR, "Attributes.Secondary.Armor", "Reducing damage taken, improves Block Chance");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_ARMORPENETRATION, "Attributes.Secondary.ArmorPenetration", "Bypass Enemy armor");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_BLOCKCHANCE, "Attributes.Secondary.BlockChance", "The chances to block enemy attack damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_CRITICALHITCHANCE, "Attributes.Secondary.CriticalHitChance", "The chances to critically damage enemy");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_CRITICALHITDAMAGE, "Attributes.Secondary.CriticalHitDamage", "The amount of damage to critically damage enemy");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_CRITICALHITRESISTANCE, "Attributes.Secondary.CriticalHitResistance", "The amount of resistance to avoid getting critically damaged by enemy");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_HEALTHREGENERATION, "Attributes.Secondary.HealthRegeneration", "The amount of health generated per second");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_MANAREGENERATION, "Attributes.Secondary.ManaRegeneration", "The amount of mana generated per second");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_MAXHEALTH, "Attributes.Secondary.MaxHealth", "The total amount of Health a character has");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_MAXMANA, "Attributes.Secondary.MaxMana", "The total amount of Mana a character has");*/

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	// Primary Attributes
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Increases Physical damage"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases magical damage"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Increases Armor and Armor Penetration"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Increases Health"));

	// Secondary Attributes
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reducing damage taken, improves Block Chance"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Bypass Enemy armor"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("The chances to block enemy attack damage"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("The chances to critically damage enemy"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("The amount of damage to critically damage enemy"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces critical hit chance of attacking enemies"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("The amount of health generated per second"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("The amount of mana generated per second"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("The total amount of Health a character can obtain"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("The total amount of Mana a character  can obtain"));

	// Input Tags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Input Tag for 1 Key"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Input Tag for 2 Key"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Input Tag for 3 Key"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Input Tag for 4 Key"));
	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.1"), FString("Input Tag for Passive Ability 1"));
	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.2"), FString("Input Tag for Passive Ability 2"));

	/* Damage Types */
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"), FString("Fire Damage type"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"), FString("Arcane Damage type"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"), FString("Lightning Damage type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), FString("Physical Damage type"));

	/* Resistances */
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"), FString("Resistance to Arcane Damage type"));
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Resistance to Fire Damage type"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"), FString("Resistance to Lightning Damage type"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("Resistance to Physical Damage type"));

	/** Debuffs */
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Burn"), FString("Burn Debuff type"));
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"), FString("Stun Debuff type"));
	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Physical"), FString("Physical Debuff type"));
	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Arcane"), FString("Arcane Debuff type"));
	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"), FString("Chance Debuff type"));
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"), FString("Damage Debuff type"));
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"), FString("Duration Debuff type"));
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"), FString("Frequency Debuff type"));
	/* Meta Attributes */
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"), FString("Incoming XP Meta Attribute"));

	/* Map of Damage types to Resistance */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	/* Map of Damage types to Debuffs*/
	GameplayTags.DamageTypeToDebuffs.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypeToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypeToDebuffs.Add(GameplayTags.Damage_Lightning, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypeToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);
	
	/*Effects*/
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Hit Reaction when hit by something"));

	/*Offensive Abilities*/
	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.None"), FString("No Ability - like the nullptr for Ability Tags"));
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"), FString("Attack Ability Tag"));
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"), FString("Summon Ability Tag"));
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), FString("FireBolt Ability Tag"));
	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"), FString("Electrocute Ability Tag"));
	GameplayTags.Abilities_Arcane_ArcaneShards = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Arcane.ArcaneShards"), FString("ArcaneShards Ability Tag"));

	/* Passive Abilities */
	GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.HaloOfProtection"), FString("Halo of protection passive Ability Tag"));
	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.LifeSiphon"), FString("Life Siphon passive Ability Tag"));
	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.ManaSiphon"), FString("Mana Siphon passive Ability Tag"));

	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.HitReact"), FString("Hit React Ability Tag"));
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Locked"), FString("Locked status Ability Tag"));
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Eligible"), FString("Eligible status Ability Tag"));
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Unlocked"), FString("Unlocked Status Ability Tag"));
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Equipped"), FString("Equipped Status Ability Tag"));
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"), FString("None Type of Ability Tag"));
	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Offensive"), FString("Offensive Type of Ability Tag"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"), FString("Passive Type of Ability Tag"));

	/*Cooldown*/
	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("FireBolt Cooldown Tag"));
	
	/*Combat Tags*/
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"), FString("Weapon"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"), FString("Right Hand"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"), FString("Left Hand"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"), FString("Tail"));

	/*Montage Tags*/
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"), FString("Attack 1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"), FString("Attack 2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"), FString("Attack 3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"), FString("Attack 4"));

	/* Player Tags */
	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.CursorTrace"), FString("Block tracing under the Cursor"));
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputHeld"), FString("Block Input Held callback for Input"));
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputPressed"), FString("Block Input Pressed callback for Input"));
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputReleased"), FString("Block Input Released callback for Input"));
}