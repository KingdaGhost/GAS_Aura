// Copyright KingdaGhost Studios


#include "Actor/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->SetIsReplicated(true);
}

void AAuraProjectile::OnHit()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	if(LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	bHit = true;
}

void AAuraProjectile::Destroyed()
{
	//This is for clients who did not get a chance to enter OnSphereOverlap() due to destroy function getting called before spawning impacts
	if (!bHit && !HasAuthority()) OnHit();
	if(LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	Super::Destroyed();
}


void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	if(LoopingSoundComponent) LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (DamageEffectParams.SourceAbilitySystemComponent && DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor())
	{
		AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
		if (SourceAvatarActor == OtherActor) return;
		// if the firstactor and second actor has the same tag then friends will be true, and it will return false and thus will be true in the below if check
		if(!UAuraAbilitySystemLibrary::IsNotFriend(OtherActor, SourceAvatarActor)) return;
		if (!bHit) OnHit();
	
		if (HasAuthority())
		{
			if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
			{	// DamageEffectParams is already set in the AuraProjectileSpell when Projectile is Spawn and the remaining will be set here when there is an overlap
				const bool bKnockback = FMath::RandRange(1, 100) < DamageEffectParams.KnockbackChance;
				if (bKnockback)
				{
					// const FVector KnockbackDirection = GetActorForwardVector().RotateAngleAxis(45.f, GetActorRightVector()); // This is the same as the below three lines
					FRotator Rotation = (OtherActor->GetActorLocation() - SourceAvatarActor->GetActorLocation()).Rotation();
					Rotation.Pitch = 45.f;
					const FVector KnockbackDirection = Rotation.Vector();
					const FVector KnockbackForce = KnockbackDirection * DamageEffectParams.KnockbackForceMagnitude;
					DamageEffectParams.KnockbackForce = KnockbackForce;
				}
				const FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
				DamageEffectParams.DeathImpulse = DeathImpulse;
				DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
				UAuraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
			}
		
			Destroy();
		}
		// This else part is for clients only. Getting to this part means that PlaySound and SpawnSystem has been done
		else	bHit = true;
	}
	
}


