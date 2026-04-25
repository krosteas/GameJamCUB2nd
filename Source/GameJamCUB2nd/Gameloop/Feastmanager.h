// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RecipeData.h"
#include "ItemData.h"
#include "Feastmanager.generated.h"

USTRUCT(BlueprintType)
struct FFeastOrder
{
	GENERATED_BODY()

	/** The item the King wants */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Feast")
	TObjectPtr<UItemData> RequestedItem = nullptr;

	/** Minimum quality accepted */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Feast")
	EItemQuality MinimumQuality = EItemQuality::Normal;

	/** Whether the player has fulfilled this order */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Feast")
	bool bFulfilled = false;
};

UCLASS()
class GAMEJAMCUB2ND_API AFeastmanager : public AActor
{
	GENERATED_BODY()

public:
	AFeastmanager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// ── Configuration ─────────────────────────

	/** How many items the King orders per feast */
	UPROPERTY(EditDefaultsOnly, Category = "Feast")
	int32 FeastOrderCount = 3;

	// ── State ─────────────────────────────────

	/** Recipes the player has unlocked so far */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Feast")
	TArray<TObjectPtr<URecipeData>> KnownRecipes;

	/** Orders generated for the current feast */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Feast")
	TArray<FFeastOrder> CurrentOrders;

	/** Whether a feast is currently active */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Feast")
	bool bFeastActive = false;

	// ── Actions ───────────────────────────────

	void BeginFeast();
	void UnlockRecipe(URecipeData* Recipe);
	bool SubmitItem(UItemData* Item, EItemQuality Quality);
	int32 EvaluateFeast();

private:
	void GenerateOrders();
};