// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/WPGGameplayAbility.h"
#include "Abilities/PlayerAbilityInputID.h"

EPlayerAbilityInputID UWPGGameplayAbility::GetPlayerAbilityInputID()
{
	return PlayerAbilityInputID;
}

int32 UWPGGameplayAbility::GetAbilityLevel()
{
	return AbilityLevel;
}
