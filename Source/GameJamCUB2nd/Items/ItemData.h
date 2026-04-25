// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Potion      UMETA(DisplayName = "Potion"),
	Food        UMETA(DisplayName = "Food"),
	Drink       UMETA(DisplayName = "Drink"),
	Ingredient  UMETA(DisplayName = "Ingredient"),
	Misc        UMETA(DisplayName = "Misc")
};

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	Poor        UMETA(DisplayName = "Poor"),
	Normal      UMETA(DisplayName = "Normal"),
	Fine        UMETA(DisplayName = "Fine"),
	Perfect     UMETA(DisplayName = "Perfect")
};

/**
 * UItemData
 *
 * A DataAsset that defines a single item type in the game.
 * Create one asset per item (e.g. DA_HealingPotion, DA_StrangeBrew).
 * Referenced by RecipeData, CustomerOrderComponent, and CraftingComponent.
 */
UCLASS()
class GAMEJAMCUB2ND_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:

	// ── Identity ──────────────────────────────

	/** Display name shown to the player and in UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
	FText ItemName;

	/** Flavour text / tooltip shown in the shop UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
	FText Description;

	/** Icon shown in inventory and customer request UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
	TObjectPtr<UTexture2D> Icon;

	// ── Classification ────────────────────────

	/** Broad category — drives what customers can request and what recipes produce */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classification")
	EItemType ItemType = EItemType::Misc;

	/** Base quality — the intended quality when the recipe succeeds perfectly */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classification")
	EItemQuality BaseQuality = EItemQuality::Normal;

	// ── Economy ───────────────────────────────

	/** Base gold value at Normal quality. Scaled at runtime by quality modifier. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Economy", meta = (ClampMin = "0"))
	int32 BaseGoldValue = 10;

	// ── Tags ──────────────────────────────────

	/** Gameplay tags (e.g. "healing", "poisonous", "exotic", "cursed") */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags")
	TArray<FName> ItemTags;

	// ── Helpers ───────────────────────────────

	/** Returns the gold value adjusted for a given quality level */
	UFUNCTION(BlueprintPure, Category = "Economy")
	int32 GetValueForQuality(EItemQuality Quality) const;

	/** Returns true if this item has a specific tag */
	UFUNCTION(BlueprintPure, Category = "Tags")
	bool HasTag(FName Tag) const;
};