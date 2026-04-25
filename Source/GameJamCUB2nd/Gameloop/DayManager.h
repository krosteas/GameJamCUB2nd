// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RecipeData.h"
#include "DayManager.generated.h"

class AFeastmanager;

UENUM(BlueprintType)
enum class EDayPhase : uint8
{
	NotStarted  UMETA(DisplayName = "Not Started"),
	WorkDay     UMETA(DisplayName = "Work Day"),
	FeastDay    UMETA(DisplayName = "Feast Day"),
	EndOfDay    UMETA(DisplayName = "End Of Day"),
	GameOver    UMETA(DisplayName = "Game Over")
};

UCLASS()
class GAMEJAMCUB2ND_API ADayManager : public AActor
{
	GENERATED_BODY()

public:
	ADayManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// ── Configuration ─────────────────────────

	/** Total real-time duration of one work day in seconds */
	UPROPERTY(EditDefaultsOnly, Category = "Day")
	float DayDuration = 600.0f;

	/** Minimum customers guaranteed per day */
	UPROPERTY(EditDefaultsOnly, Category = "Customers")
	int32 MinCustomersPerDay = 3;

	/** How much time must remain (seconds) to spawn an extra customer */
	UPROPERTY(EditDefaultsOnly, Category = "Customers")
	float ExtraCustomerTimeThreshold = 120.0f;

	/** Reputation lost per failed feast item */
	UPROPERTY(EditDefaultsOnly, Category = "Reputation")
	int32 ReputationPenaltyPerFailure = 10;

	/** Reputation at which the player is exiled */
	UPROPERTY(EditDefaultsOnly, Category = "Reputation")
	int32 ExileReputationThreshold = 0;

	// ── State ─────────────────────────────────

	/** Current day number (starts at 1) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Day")
	int32 CurrentDay = 1;

	/** How much real time has passed today in seconds */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Day")
	float DayElapsed = 0.0f;

	/** Current phase of the day */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Day")
	EDayPhase DayPhase = EDayPhase::NotStarted;

	/** Player's current gold */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Economy")
	int32 Gold = 0;

	/** Player's current reputation (0 = exiled) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reputation")
	int32 Reputation = 100;

	/** How many customers have spawned today */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Customers")
	int32 CustomersSpawnedToday = 0;

	// ── References ────────────────────────────

	/** Reference to the FeastManager in the level */