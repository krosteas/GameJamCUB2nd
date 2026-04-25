// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemData.h"
#include "CustomerOrderComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAMCUB2ND_API UCustomerOrderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCustomerOrderComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	// ── Order ─────────────────────────────────

	/** The item this customer wants */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Order")
	TObjectPtr<UItemData> RequestedItem = nullptr;

	/** Minimum quality the customer will accept */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Order")
	EItemQuality MinimumQuality = EItemQuality::Normal;

	/** Whether this order has been fulfilled */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Order")
	bool bFulfilled = false;

	// ── Rewards & Penalties ───────────────────

	/**
	 * Reputation gained when the order is fulfilled correctly.
	 * Set by CustomerNPC based on archetype.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Order")
	int32 ReputationReward = 5;

	/**
	 * Reputation lost when the wrong item or quality is given.
	 * Stored as a negative value.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Order")
	int32 ReputationPenalty = -10;

	// ── Actions ───────────────────────────────

	/**
	 * Called by CustomerNPC when the player hands over an item.
	 * Returns true if the item and quality meet the order requirements.
	 */
	bool EvaluateOffer(UItemData* Item, EItemQuality Quality);

	/** Returns the reputation reward value */
	int32 GetReputationReward() const { return ReputationReward; }

	/** Returns the reputation penalty value */
	int32 GetReputationPenalty() const { return ReputationPenalty; }

	/**
	 * Sets up the order randomly based on a list of available items
	 * and the customer's archetype minimum quality expectation.
	 */
	void GenerateOrder(const TArray<UItemData*>& AvailableItems, EItemQuality MinQuality);
};