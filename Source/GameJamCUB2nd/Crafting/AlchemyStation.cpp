// Fill out your copyright notice in the Description page of Project Settings.

#include "AlchemyStation.h"

// Sets default values
AALchemyStation::AALchemyStation()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the crafting component
	CraftingComponent = CreateDefaultSubobject<UCraftingComponent>(TEXT("CraftingComponent"));
}

void AALchemyStation::BeginPlay()
{
	Super::BeginPlay();
}

// ─────────────────────────────────────────────
//  Tick — hourglass timer
// ─────────────────────────────────────────────

void AALchemyStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bHourglassActive) return;

	CurrentHeatElapsed += DeltaTime;

	if (CurrentHeatElapsed >= HeatTurnDuration)
	{
		CurrentHeatElapsed = 0.0f;
		OnHeatTurnComplete();
	}
}

// ─────────────────────────────────────────────
//  Player Actions
// ─────────────────────────────────────────────

void AALchemyStation::StartCrafting()
{
	if (!ActiveRecipe) return;
	CraftingComponent->StartCrafting(ActiveRecipe);
}

void AALchemyStation::OnPlaceBase(UItemData* Base)
{
	if (!CraftingComponent) return;
	CraftingComponent->PlaceBase(Base);
}

void AALchemyStation::OnAddIngredient(UItemData* Ingredient, bool bWasGround)
{
	if (!CraftingComponent) return;
	CraftingComponent->AddIngredient(Ingredient, bWasGround);
}

void AALchemyStation::OnToggleHeat()
{
	if (!CraftingComponent) return;

	CraftingComponent->ToggleHeat();

	// Start or stop the hourglass based on heating state
	if (CraftingComponent->bIsHeating)
		StartHourglass();
	else
		StopHourglass();
}

void AALchemyStation::OnDistill()
{
	if (!CraftingComponent) return;

	bool bSuccess = CraftingComponent->Distill();
	if (bSuccess)
		OnCraftingFinished();
}

void AALchemyStation::OnReset()
{
	if (!CraftingComponent) return;
	StopHourglass();
	CraftingComponent->ResetCrafting();
}

// ─────────────────────────────────────────────
//  Hourglass
// ─────────────────────────────────────────────

void AALchemyStation::StartHourglass()
{
	CurrentHeatElapsed = 0.0f;
	bHourglassActive = true;
}

void AALchemyStation::StopHourglass()
{
	CurrentHeatElapsed = 0.0f;
	bHourglassActive = false;
}

void AALchemyStation::OnHeatTurnComplete()
{
	if (!CraftingComponent) return;

	CraftingComponent->CompleteHeatTurn();

	// If still heating, hourglass automatically starts next turn
	// If player toggled heat off between turns, stop
	if (!CraftingComponent->bIsHeating)
		StopHourglass();
}

// ─────────────────────────────────────────────
//  Finished
// ─────────────────────────────────────────────

void AALchemyStation::OnCraftingFinished()
{
	if (!CraftingComponent || !CraftingComponent->ActiveRecipe) return;

	EItemQuality FinalQuality = CraftingComponent->CalculateQuality();
	UItemData* ProducedItem = CraftingComponent->ActiveRecipe->ProducedItem;

	if (!ProducedItem) return;

	// TODO: hook into inventory system here
	// e.g. PlayerInventory->AddItem(ProducedItem, FinalQuality);

	UE_LOG(LogTemp, Log, TEXT("Crafting finished: %s at quality %d"),
		*ProducedItem->ItemName.ToString(),
		(int32)FinalQuality);

	StopHourglass();
	CraftingComponent->ResetCrafting();
}