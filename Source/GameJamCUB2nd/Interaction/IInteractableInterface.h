// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * IIInteractableInterface
 *
 * Implement this interface on any actor the player can interact with:
 * AlchemyStation, CustomerNPC, shop counter, doors, etc.
 * ShopkeeperCharacter's InteractionComponent will call these functions
 * when the player presses the interact button.
 */
class GAMEJAMCUB2ND_API IIInteractableInterface
{
	GENERATED_BODY()

public:

	/**
	 * Called when the player starts interacting with this object.
	 * e.g. player walks up and presses interact.
	 */
	virtual void OnInteract(AActor* Interactor) = 0;

	/**
	 * Called when the player stops interacting.
	 * e.g. player walks away or presses interact again to cancel.
	 */
	virtual void OnEndInteract(AActor* Interactor) {}

	/**
	 * Returns the interaction prompt text shown on screen when
	 * the player looks at this object.
	 * e.g. "Press E to brew", "Press E to serve customer"
	 */
	virtual FText GetInteractPrompt() const
	{
		return FText::FromString("Interact");
	}

	/**
	 * Returns true if this object can currently be interacted with.
	 * Use this to disable interaction mid-game
	 * e.g. alchemy station is busy, customer already served, etc.
	 */
	virtual bool CanInteract(AActor* Interactor) const
	{
		return true;
	}
};