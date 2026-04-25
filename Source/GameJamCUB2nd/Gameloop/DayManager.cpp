// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLoop/DayManager.h"
#include "GameLoop/Feastmanager.h"

ADayManager::ADayManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADayManager::BeginPlay()
{
	Super::BeginPlay();
	StartDay();
}

void ADayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DayPhase != EDayPhase::WorkDay && DayPhase != EDayPhase::FeastDay)
		return;

	DayElapsed += DeltaTime;
	TrySpawnCustomer();

	if (DayElapsed >= DayDuration)
		EndDay();
}

// ─────────────────────────────────────────────
//  Day Cycle
// ─────────────────────────────────────────────

void ADayManager::StartDay()
{
	DayElapsed = 0.0f;
	CustomersSpawnedToday = 0;
	DayPhase = IsFeastDay() ? EDayPhase::FeastDay : EDayPhase::WorkDay;

	UE_LOG(LogTemp, Log, TEXT("Day %d started. Feast day: %s"),
		CurrentDay, IsFeastDay() ? TEXT("Yes") : TEXT("No"));

	for (int32 i = 0; i < MinCustomersPerDay; i++)
		TrySpawnC