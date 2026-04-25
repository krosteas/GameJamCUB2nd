// Fill out your copyright notice in the Description page of Project Settings.

#include "Customers/CustomerNPC.h"
#include "Customers/CustomerOrderComponent.h"
#include "GameLoop/DayManager.h"

ACustomerNPC::ACustomerNPC()
{
	PrimaryActorTick.bCanEverTick = true;

	OrderComponent = CreateDefaultSubobject<UCustomerOrderComponent>(TEXT("OrderComponent"));
}

void ACustomerNPC::BeginPlay()
{
	Super::BeginPlay();
	ApplyArchetypeSettings();
	StartWaiting();
}

void ACustomerNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CustomerState != ECustomerState::Waiting) return;

	WaitElapsed += DeltaTime;

	if (WaitElapsed >= Patience)
	{
		UE_LOG(LogTemp, Log, TEXT("Customer ran out of patience and left"));
		Leave(false);
	}
}

void ACustomerNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// ─────────────────────────────────────────────
//  Actions
// ─────────────────────────────────────────────

void ACustomerNPC::StartWaiting()
{
	WaitElapsed = 0.0f;
	CustomerState = ECustomerState::Waiting;
	UE_LOG(LogTemp, Log, TEXT("Customer is waiting — patience: %.0fs"), Patience);
}

bool ACustomerNPC::Serve(UItemData* Item, EItemQuality Quality)
{
	if (!Item || !OrderComponent) return false;
	if (CustomerState != ECustomerState::Waiting) return false;

	CustomerState = ECustomerState::BeingServed;

	bool bAccepted = OrderComponent->EvaluateOffer(Item, Quality);

	if (bAccepted)
	{
		UE_LOG(LogTemp, Log, TEXT("Customer accepted the item"));

		// Report gold and reputation gain to DayManager
		if (DayManager)
		{
			int32 GoldEarned = Item->GetValueForQuality(Quality);
			int32 ReputationGain = OrderComponent->GetReputationReward();
			DayManager->OnCustomerServed(GoldEarned, ReputationGain);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Customer rejected the item"));

		// Reputation penalty for wrong item
		if (DayManager)
			DayManager->OnCustomerServed(0, OrderComponent->GetReputationPenalty());
	}

	Leave(bAccepted);
	return bAccepted;
}

void ACustomerNPC::Leave(bool bWasServed)
{
	CustomerState = ECustomerState::Leaving;
	UE_LOG(LogTemp, Log, TEXT("Customer leaving. Served: %s"),
		bWasServed ? TEXT("Yes") : TEXT("No"));

	// TODO: play leave animation, then destroy actor
	// For now just destroy immediately
	Destroy();
}

float ACustomerNPC::GetPatienceFraction() const
{
	if (Patience <= 0.0f) return 0.0f;
	return FMath::Clamp(1.0f - (WaitElapsed / Patience), 0.0f, 1.0f);
}

// ─────────────────────────────────────────────
//  Archetype Settings
// ─────────────────────────────────────────────

void ACustomerNPC::ApplyArchetypeSettings()
{
	switch (Archetype)
	{
		case ECustomerArchetype::Peasant:
			Patience = 90.0f;	// very patient
			break;
		case ECustomerArchetype::Noble:
			Patience = 30.0f;	// impatient
			break;
		case ECustomerArchetype::Witch:
			Patience = 60.0f;	// average
			break;
		case ECustomerArchetype::Knight:
			Patience = 45.0f;	// somewhat impatient
			break;
		case ECustomerArchetype::Merchant:
			Patience = 75.0f;	// fairly patient
			break;
		case ECustomerArchetype::King:
    		Patience = 20.0f;	// very impatient, he's the king
    		break;
		default:
			Patience = 60.0f;
			break;
	}
}