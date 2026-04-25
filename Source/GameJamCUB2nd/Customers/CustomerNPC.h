// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/ItemData.h"
#include "CustomerNPC.generated.h"

class UCustomerOrderComponent;
class ADayManager;

// ─────────────────────────────────────────────
//  Enums
// ─────────────────────────────────────────────
UENUM(BlueprintType)
enum class ECustomerArchetype : uint8
{
	Peasant		UMETA(DisplayName = "Peasant"),
	Noble		UMETA(DisplayName = "Noble"),
	Witch		UMETA(DisplayName = "Witch"),
	Knight		UMETA(DisplayName = "Knight"),
	Merchant	UMETA(DisplayName = "Merchant"),
	King		UMETA(DisplayName = "King")
};


UENUM(BlueprintType)
enum class ECustomerState : uint8
{
	Entering	UMETA(DisplayName = "Entering"),
	Waiting		UMETA(DisplayName = "Waiting"),
	BeingServed	UMETA(DisplayName = "Being Served"),
	Leaving		UMETA(DisplayName = "Leaving")
};

// ─────────────────────────────────────────────
//  ACustomerNPC
// ─────────────────────────────────────────────

UCLASS()
class GAMEJAMCUB2ND_API ACustomerNPC : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomerNPC();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ── Components ────────────────────────────

	/** Holds what this customer wants */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Customer")
	TObjectPtr<UCustomerOrderComponent> OrderComponent;

	// ── Configuration ─────────────────────────

	/** What kind of customer this is */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customer")
	ECustomerArchetype Archetype = ECustomerArchetype::Peasant;

	/**
	 * How long the customer will wait before leaving (seconds).
	 * Varies by archetype — nobles are impatient, peasants are patient.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customer")
	float Patience = 60.0f;

	// ── State ─────────────────────────────────

	/** Current behaviour state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Customer")
	ECustomerState CustomerState = ECustomerState::Entering;

	/** How long the customer has been waiting */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Customer")
	float WaitElapsed = 0.0f;

	/** Reference to DayManager to report transaction results */
	UPROPERTY(EditAnywhere, Category = "Customer")
	TObjectPtr<ADayManager> DayManager;

	// ── Actions ───────────────────────────────

	/** Called when the customer arrives and starts waiting */
	void StartWaiting();

	/**
	 * Called by the player when serving this customer.
	 * Item and quality are what the player hands over.
	 * Returns true if the customer accepts it.
	 */
	bool Serve(UItemData* Item, EItemQuality Quality);

	/** Called when the customer leaves — either served or ran out of patience */
	void Leave(bool bWasServed);

	/** Returns patience remaining as 0-1 fraction */
	float GetPatienceFraction() const;

private:

	/** Sets default patience based on archetype */
	void ApplyArchetypeSettings();
};