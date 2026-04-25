// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CraftingComponent.h"
#include "RecipeData.h"
#include "ItemData.h"
#include "AlchemyStation.generated.h"

UCLASS()
class GAMEJAMCUB2ND_API AALchemyStation : public AActor
{
	GENERATED_BODY()

public:
	AALchemyStation();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// ── Components ────────────────────────────

	/** Handles all crafting logic for this station */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crafting")
	TObjectPtr<UCraftingComponent> CraftingComponent;

	// ── Configuration ─────────────────────────

	/**
	 * The recipe this station is currently set to craft.
	 * Set by the player or by the game before interacting.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crafting")
	TObjectPtr<URecipeData> ActiveRecipe;

	// ── Hourglass Timer ───────────────────────

	/** Duration of one hourglass turn in seconds */
	UPROPERTY(EditDefaultsOnly, Category = "Crafting")
	float HeatTurnDuration = 10.0f;

	/** How much time has passed in the current heat turn */
	UPROPERTY(VisibleAnywhere, Category = "Crafting")
	float CurrentHeatElapsed = 0.0f;

	/** Whether the hourglass is currently counting */
	UPROPERTY(VisibleAnywhere, Category = "Crafting")
	bool bHourglassActive = false;

	// ── Player Actions ────────────────────────

	/** Called by player to start a crafting session */
	void StartCrafting();

	/** Called by player when placing the base liquid */
	void OnPlaceBase(UItemData* Base);

	/** Called by player when adding an ingredient */
	void OnAddIngredient(UItemData* Ingredient, bool bWasGround);

	/** Called by player when toggling the cauldron on/off heat */
	void OnToggleHeat();

	/** Called by player when performing distillation */
	void OnDistill();

	/** Called by player to reset and start over */
	void OnReset();

private:

	/** Starts the hourglass countdown */
	void StartHourglass();

	/** Stops the hourglass countdown */
	void StopHourglass();

	/**
	 * Called when one full heat turn completes.
	 * Notifies CraftingComponent and resets the hourglass for the next turn.
	 */
	void OnHeatTurnComplete();

	/**
	 * Called when crafting finishes successfully.
	 * Calculates quality and sends item to inventory.
	 */
	void OnCraftingFinished();
};