// Copyright KingdaGhost Studios

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class AAuraPlayerController;
class AAuraPlayerState;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	void InitAbilityActorInfo();

	UPROPERTY()
	TObjectPtr<AAuraPlayerState> AuraPlayerState;
	UPROPERTY()
	TObjectPtr<AAuraPlayerController> AuraPlayerController;
	
};
