// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "RecipeData.h"
#include "CraftingComponent.generated.h"

// ─────────────────────────────────────────────
//  Enums
// ─────────────────────────────────────────────

UENUM(BlueprintType)
enum class ECraftingState : uint8
{
	Idle			UMETA(DisplayName = "Idle"),
	WaitingForBase		UMETA(DisplayName = "Waiting For Base"),
	AddingIngredients	UMETA(DisplayName = "Adding Ingredients"),
	Heating			UMETA(DisplayName = "Heating"),
	Distilling		UMETA(DisplayName = "Distilling"),
	Finished		UMETA(DisplayName = "Finished")
};

// ─────────────────────────────────────────────
//  UCraftingComponent
// ─────────────────────────────────────────────

/**
 * UCraftingComponent
 *
 * Attached to AlchemyStation. Tracks the full state of one crafting session:
 * base liquid, ingredients, heat turns, grinding, and distillation.
 * Calculates final item quality when the craft is finished.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEJAMCUB2ND_API UCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UCraftingComponent();

	// ── State ─────────────────────────────────

	/** Current stage of the crafting process */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting")
	ECraftingState CraftingState = ECraftingState::Idle;

	/** The recipe currently being attempted. Set by AlchemyStation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting")
	TObjectPtr<URecipeData> ActiveRecipe = nullptr;

	// ── Session Tracking ──────────────────────

	/** The base liquid the player placed in the cauldron */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting|Session")
	TObjectPtr<UItemData> PlacedBase = nullptr;

	/** Ingredients the player has added so far, in order */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting|Session")
	TArray<TObjectPtr<UItemData>> AddedIngredients;

	/** Tracks which added ingredients were ground before adding */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting|Session")
	TArray<bool> IngredientWasGround;

	/** How many full hourglass turns of heat have been applied */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting|Session")
	int32 HeatTurnsCompleted = 0;

	/** Whether the player has performed distillation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting|Session")
	bool bDistillationDone = false;

	/** Whether the cauldron is currently on heat */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting|Session")
	bool bIsHeating = false;

	// ── Actions ───────────────────────────────

	/** Start a new crafting session with the given recipe */
	void StartCrafting(URecipeData* Recipe);

	/** Player places the base liquid into the cauldron */
	bool PlaceBase(UItemData* Base);

	/** Player adds an ingredient — bWasGround = true if mortar was used first */
	bool AddIngredient(UItemData* Ingredient, bool bWasGround);

	/** Player toggles the cauldron on/off the heat */
	void ToggleHeat();

	/** Called every 10 seconds while heating — counts one hourglass turn */
	void CompleteHeatTurn();

	/** Player performs distillation to finish the potion */
	bool Distill();

	/** Resets the crafting session back to Idle */
	void ResetCrafting();

	// ── Result ────────────────────────────────

	/**
	 * Calculates the quality of the finished item based on how well
	 * the player followed the recipe. Call after Distill() succeeds.
	 */
	EItemQuality CalculateQuality() const;

protected:

	virtual void BeginPlay() override;

private:

	/** Counts how many steps the player got wrong (wrong order, missing grind, etc.) */
	int32 CountMistakes() const;
};