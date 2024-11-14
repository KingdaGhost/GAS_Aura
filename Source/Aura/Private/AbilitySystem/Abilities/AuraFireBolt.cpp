// Copyright KingdaGhost Studios


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interaction/CombatInterface.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 ScaledDamage = FMath::RoundToInt(Damage.GetValueAtLevel(Level));
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"
			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			// Description
			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing </><Damage>%d </><Default>"
			"fire damage with a </><Percent>%.0f%%</><Default> chance to burn "
			 "and a </><Percent>%.0f%%</><Default> chance to knockback enemies</>"),
			// Values
			Level, ManaCost, Cooldown, ScaledDamage, DebuffChance, KnockbackChance);
	}
	return FString::Printf(TEXT(
		// Title
		"<Title>FIRE BOLT</>\n\n"
		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		// Description
		"<Default>Launches %d bolts of fire, "
		"exploding on impact and dealing </><Damage>%d </><Default>"
		"fire damage with a </><Percent>%.0f%%</><Default> chance to burn "
		"and a </><Percent>%.0f%%</><Default> chance to knockback enemies</>"),
		// Values
		Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage, DebuffChance, KnockbackChance);
	
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 ScaledDamage = FMath::RoundToInt(Damage.GetValueAtLevel(Level));
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n\n"
		//Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		// Description
		"<Default>Launches %d bolts of fire, exploding on impact and dealing "
		"</><Damage>%d </><Default>fire damage with a </><Percent>%.0f%%</><Default> chance to burn"
		"and a </><Percent>%.0f%%</><Default> chance to knockback enemies</>"),
		// Values
		Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage, DebuffChance, KnockbackChance);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	// We are calling Execute_GetCombatSocketLocation because we declared it as BlueprintNativeEvent
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}

	const FVector Forward = Rotation.Vector();
	const int32 EffectiveNumProjectiles = FMath::Min(NumProjectiles, GetAbilityLevel());
	
	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, EffectiveNumProjectiles);

	for (const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		// SpawnActorDeferred is for spawning an actor in the world when all the things that need to be attached to it has been set.
		// In this case, the gameplay ability spec for damage is set before we spawn the projectile and by calling FinishSpawning on the projectile, we conclude that everything is in order and for it to be spawn to the world
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		if (HomingTarget && HomingTarget->Implements<UCombatInterface>()) // Target only ,i.e, enemies
		{
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		}
		else // Floors and others
		{
			Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
		}
		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
		Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;
		Projectile->FinishSpawning(SpawnTransform);
		
	}
	
}
