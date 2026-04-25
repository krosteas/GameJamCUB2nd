// Fill out your copyright notice in the Description page of Project Settings.

#include "CraftingComponent.h"

UCraftingComponent::UCraftingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCraftingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// ─────────────────────────────────────────────
//  Actions
// ─────────────────────────────────────────────

void UCraftingComponent::StartCrafting(URecipeData* Recipe)
{
	if (!Recipe) return;

	ResetCrafting();
	ActiveRecipe = Recipe;
	CraftingState = ECraftingState::WaitingForBase;
}

bool UCraftingComponent::PlaceBase(UItemData* Base)
{
	if (!Base || !ActiveRecipe) return false;
	if (CraftingState != ECraftingState::WaitingForBase) return false;

	// Check this is the correct base for the recipe
	if (ActiveRecipe->RequiredBase != Base) return false;

	PlacedBase = Base;
	CraftingState = ECraftingState::AddingIngredients;
	return true;
}

bool UCraftingComponent::AddIngredient(UItemData* Ingredient, bool bWasGround)
{
	if (!Ingredient || !ActiveRecipe) return false;
	if (CraftingState != ECraftingState::AddingIngredients) return false;

	// Don't accept more ingredients than the recipe needs
	if (AddedIngredients.Num() >= ActiveRecipe->GetStepCount()) return false;

	AddedIngredients.Add(Ingredient);
	IngredientWasGround.Add(bWasGround);
	return true;
}

void UCraftingComponent::ToggleHeat()
{
	if (CraftingState != ECraftingState::AddingIngredients &&
		CraftingState != ECraftingState::Heating) return;

	bIsHeating = !bIsHeating;
	CraftingState = bIsHeating ? ECraftingState::Heating
				   : ECraftingState::AddingIngredients;
}

void UCraftingComponent::CompleteHeatTurn()
{
	if (CraftingState != ECraftingState::Heating) return;
	if (!bIsHeating) return;

	HeatTurnsCompleted++;
}

bool UCraftingComponent::Distill()
{
    if (!ActiveRecipe) return false;
    if (AddedIngredients.Num() != ActiveRecipe->GetStepCount()) return false;

    bDistillationDone = true;
    CraftingState = ECraftingState::Finished;
    return true;
}

void UCraftingComponent::ResetCrafting()
{
	ActiveRecipe = nullptr;
	PlacedBase = nullptr;
	AddedIngredients.Empty();
	IngredientWasGround.Empty();
	HeatTurnsCompleted = 0;
	bDistillationDone = false;
	bIsHeating = false;
	CraftingState = ECraftingState::Idle;
}

// ─────────────────────────────────────────────
//  Quality Calculation
// ─────────────────────────────────────────────

EItemQuality UCraftingComponent::CalculateQuality() const
{
	if (!ActiveRecipe || CraftingState != ECraftingState::Finished)
		return EItemQuality::Poor;

	int32 Mistakes = CountMistakes();

	if (Mistakes == 0) return EItemQuality::Perfect;
	if (Mistakes == 1) return EItemQuality::Fine;
	if (Mistakes == 2) return EItemQuality::Normal;
	return EItemQuality::Poor;
}

int32 UCraftingComponent::CountMistakes() const
{
	int32 Mistakes = 0;

	if (!ActiveRecipe) return Mistakes;

	// Sort recipe steps by order
	TArray<FRecipeStep> SortedSteps = ActiveRecipe->Steps;
	SortedSteps.Sort([](const FRecipeStep& A, const FRecipeStep& B)
	{
		return A.OrderIndex < B.OrderIndex;
	});

	// Check each ingredient — wrong item or missing grind counts as a mistake
	for (int32 i = 0; i < SortedSteps.Num(); i++)
	{
		if (i >= AddedIngredients.Num()) { Mistakes++; continue; }

		if (SortedSteps[i].Ingredient != AddedIngredients[i])
			Mistakes++;

		if (SortedSteps[i].bRequiresGrinding && !IngredientWasGround[i])
			Mistakes++;
	}

	// Too many or too few heat turns = one mistake
	if (HeatTurnsCompleted != ActiveRecipe->RequiredHeatTurns)
		Mistakes++;

	return Mistakes;
}