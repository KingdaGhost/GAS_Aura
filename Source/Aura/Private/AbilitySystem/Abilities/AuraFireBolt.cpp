// Copyright KingdaGhost Studios


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

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
			"fire damage with a chance to burn</>"),
			// Values
			Level, ManaCost, Cooldown, ScaledDamage);
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
		"fire damage with a chance to burn</>"),
		// Values
		Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage);
	
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
		"</><Damage>%d </><Default>fire damage with a chance to burn</>"),
		// Values
		Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* TargetActor)
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
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);

	// NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	if (NumProjectiles > 1)
	{
		// if we divide directly by NumProjectiles there will be problems. Eg, if we have 2 projectiles then, the first one will start at LeftOfSpread since the angle starts at 0 but the next one will be at 45 since we divide the spread by 2
		// which we do not want, but instead we want it at the RightOfSpread which is 90 degrees. So we have to divide the spread by Number of Projectiles less by one (1), which will give 90 for the second one.
		const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);
		for (int32 i = 0; i < NumProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			const FVector Start = SocketLocation + FVector(0,0, 5); // Just to raise it above 10 units
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),
				Start,
				 Start + Direction * 100.f,
				5,
				FLinearColor::Red,
				120,
				1);		
		}
	}
	else
	{
		// Single Projectile
		const FVector Start = SocketLocation + FVector(0,0, 5); // Just to raise it above 10 units
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),
				Start,
				 Start + Forward * 100.f,
				5,
				FLinearColor::Red,
				120,
				1);	
	}
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + Forward * 100.f, 5, FLinearColor::White, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + LeftOfSpread * 100.f, 5, FLinearColor::Gray, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + RightOfSpread * 100.f, 5, FLinearColor::Gray, 120, 1);
}
