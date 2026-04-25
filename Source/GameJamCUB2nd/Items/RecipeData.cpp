// Fill out your copyright notice in the Description page of Project Settings.

#include "RecipeData.h"

bool URecipeData::IsValidCraft(const TArray<UItemData*>& IngredientsInOrder) const
{
	if (IngredientsInOrder.Num() != Steps.Num())
		return false;

	// Sort steps by OrderIndex so the designer doesn't have
	// to enter them in order in the editor
	TArray<FRecipeStep> SortedSteps = Steps;
	SortedSteps.Sort([](const FRecipeStep& A, const FRecipeStep& B)
	{
		return A.OrderIndex < B.OrderIndex;
	});

	for (int32 i = 0; i < SortedSteps.Num(); i++)
	{
		if (SortedSteps[i].Ingredient != IngredientsInOrder[i])
			return false;
	}

	return true;
}`