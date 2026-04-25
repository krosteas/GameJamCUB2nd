// Fill out your copyright notice in the Description page of Project Settings.

#include "Customers/CustomerOrderComponent.h"

UCustomerOrderComponent::UCustomerOrderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCustomerOrderComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCustomerOrderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// ─────────────────────────────────────────────
//  Actions
// ─────────────────────────────────────────────

bool UCustomerOrderComponent::EvaluateOffer(UItemData* Item, EItemQuality Quality)
{
	if (!Item || !RequestedItem) return false;
	if (bFulfilled) return false;

	// Wrong item
	if (Item != RequestedItem)
	{
		UE_LOG(LogTemp, Log, TEXT("Order rejected — wrong item"));
		return false;
	}

	// Quality too low
	if (Quality < MinimumQuality)
	{
		UE_LOG(LogTemp, Log, TEXT("Order rejected — quality too low"));
		return false;
	}

	bFulfilled = true;
	UE_LOG(LogTemp, Log, TEXT("Order fulfilled: %s"), *Item->ItemName.ToString());
	return true;
}

void UCustomerOrderComponent::GenerateOrder(const TArray<UItemData*>& AvailableItems,
	EItemQuality MinQuality)
{
	if (AvailableItems.Num() == 0) return;

	// Pick a random item from the available pool
	int32 RandomIndex = FMath::RandRange(0, AvailableItems.Num() - 1);
	RequestedItem = AvailableItems[RandomIndex];
	MinimumQuality = MinQuality;
	bFulfilled = false;

	UE_LOG(LogTemp, Log, TEXT("Order generated: %s (min quality: %d)"),
		*RequestedItem->ItemName.ToString(), (int32)MinimumQuality);
}