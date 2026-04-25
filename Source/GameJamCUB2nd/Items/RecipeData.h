// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.h"
#include "RecipeData.generated.h"

// ─────────────────────────────────────────────
//  Structs
// ─────────────────────────────────────────────

/**
 * One step in a recipe — an ingredient plus the order it must be added.
 * Order is 1-based (first ingredient = 1, second = 2, etc.)
 */
USTRUCT(BlueprintType)
struct FRecipeStep
{
	GENERATED_BODY()

	/** The ingredient required at this step */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe")
	TObjectPtr<UItemData> Ingredient = nullptr;

	/** Position in the crafting sequence (1 = first added) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe", meta = (ClampMin = "1"))
	int32 OrderIndex = 1;

	/** Whether this ingredient must be ground in the mortar before adding */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe")
	bool bRequiresGrinding = false;
};

// ─────────────────────────────────────────────
//  URecipeData
// ─────────────────────────────────────────────

/**
 * URecipeData
 *
 * A DataAsset that defines one craftable recipe.
 * Create one asset per recipe (e.g. DA_Recipe_HealingPotion).
 * Used by CraftingComponent to validate what the player is making.
 */
UCLASS()
class GAMEJAMCUB2ND_API URecipeData : public UDataAsset
{
	GENERATED_BODY()

public:

	// ── Output ────────────────────────────────

	/** The item this recipe produces on a perfect craft */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Output")
	TObjectPtr<UItemData> ProducedItem = nullptr;

	// ── Ingredients ───────────────────────────

	/** Ordered list of ingredients and their required sequence */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ingredients")
	TArray<FRecipeStep> Steps;

	// ── Crafting Parameters ───────────────────

	/** How long a perfect craft takes in seconds */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crafting", meta = (ClampMin = "1.0"))
	float BaseCraftTime = 5.0f;

	/**
	 * Required heat level (0 = cold, 100 = max heat).
	 * CraftingComponent checks the player's current heat against this.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crafting", meta = (ClampMin = "0", ClampMax = "100"))
	int32 RequiredHeatLevel = 50;

	/**
	 * Difficulty rating (1-5).
	 * Higher = tighter timing windows in the alchemy minigame.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crafting", meta = (ClampMin = "1", ClampMax = "5"))
	int32 Difficulty = 1;

	// ── Helpers ───────────────────────────────

	/** Returns true if the given ingredients match this recipe's steps in the correct order */
	UFUNCTION(BlueprintPure, Category = "Crafting")
	bool IsValidCraft(const TArray<UItemData*>& IngredientsInOrder) const;

	/** Returns the number of steps in this recipe */
	UFUNCTION(BlueprintPure, Category = "Crafting")
	int32 GetStepCount() const { return Steps.Num(); }

	/** How many hourglass turns (10s each) the recipe needs on heat */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crafting", meta = (ClampMin = "1"))
	int32 RequiredHeatTurns = 1;

	/** The base liquid this recipe requires (Water, Wine, Beer, Spirits) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crafting")
	TObjectPtr<UItemData> RequiredBase = nullptr;

};