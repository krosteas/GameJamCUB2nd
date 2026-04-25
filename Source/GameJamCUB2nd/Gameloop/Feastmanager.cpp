// Fill out your copyright notice in the Description page of Project Settings.

#include "Feastmanager.h"

AFeastmanager::AFeastmanager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFeastmanager::BeginPlay()
{
	Super::BeginPlay();
}

void AFeastmanager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ─────────────────────────────────────────────
//  Feast Cycle
// ─────────────────────────────────────────────

void AFeastmanager::BeginFeast()
{
	if (KnownRecipes.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("FeastManager: No known recipes to generate orders from!"));
		return;
	}

	CurrentOrders.Empty();
	GenerateOrders();
	bFeastActive = true;

	UE_LOG(LogTemp, Log, TEXT("King's Feast begun — %d orders generated"), CurrentOrders.Num());
}

void AFeastmanager::GenerateOrders()
{
	TArray<URecipeData*> ShuffledRecipes;
	for (auto& Recipe : KnownRecipes)
		ShuffledRecipes.Add(Recipe);

	// Fisher-Yates shuffle
	for (int32 i = ShuffledRecipes.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::RandRange(0, i);
		ShuffledRecipes.Swap(i, j);
	}

	int32 OrdersToGenerate = FMath::Min(FeastOrderCount, ShuffledRecipes.Num());
	for (int32 i = 0; i < OrdersToGenerate; i++)
	{
		FFeastOrder Order;
		Order.RequestedItem = ShuffledRecipes[i]->ProducedItem;
		Order.MinimumQuality = EItemQuality::Normal;
		Order.bFulfilled = false;
		CurrentOrders.Add(Order);
	}
}

// ─────────────────────────────────────────────
//  Player Actions
// ─────────────────────────────────────────────

void AFeastmanager::UnlockRecipe(URecipeData* Recipe)
{
	if (!Recipe) return;
	if (KnownRecipes.Contains(Recipe)) return;

	KnownRecipes.Add(Recipe);
	UE_LOG(LogTemp, Log, TEXT("Recipe unlocked: %s"),
		*Recipe->ProducedItem->ItemName.ToString());
}

bool AFeastmanager::SubmitItem(UItemData* Item, EItemQuality Quality)
{
	if (!Item || !bFeastActive) return false;

	for (FFeastOrder& Order : CurrentOrders)
	{
		if (Order.bFulfilled) continue;
		if (Order.RequestedItem != Item) continue;
		if (Quality < Order.MinimumQuality)
		{
			UE_LOG(LogTemp, Log, TEXT("Item %s submitted but quality too low"),
				*Item->ItemName.ToString());
			return false;
		}

		Order.bFulfilled = true;
		UE_LOG(LogTemp, Log, TEXT("Order fulfilled: %s"), *Item->ItemName.ToString());
		return true;
	}

	UE_LOG(LogTemp, Log, TEXT("Item %s not needed for the feast"),
		*Item->ItemName.ToString());
	return false;
}

// ─────────────────────────────────────────────
//  Evaluation
// ─────────────────────────────────────────────

int32 AFeastmanager::EvaluateFeast()
{
	int32 Failures = 0;

	for (const FFeastOrder& Order : CurrentOrders)
	{
		if (!Order.bFulfilled)
		{
			Failures++;
			UE_LOG(LogTemp, Log, TEXT("Unfulfilled feast order: %s"),
				*Order.RequestedItem->ItemName.ToString());
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Feast evaluated — %d failures"), Failures);
	bFeastActive = false;
	return Failures;
}