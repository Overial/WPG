// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WPGGameplayAbility.generated.h"

enum class EPlayerAbilityInputID : uint8;

UCLASS()
class WPG_API UWPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	EPlayerAbilityInputID PlayerAbilityInputID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int32 AbilityLevel;

public:
	EPlayerAbilityInputID GetPlayerAbilityInputID();

	int32 GetAbilityLevel();
};
