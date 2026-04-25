// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Items/ItemData.h"
#include "ShopKeeperCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;

// ─────────────────────────────────────────────
//  Inventory
// ─────────────────────────────────────────────

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	/** The item in this slot */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UItemData> Item = nullptr;

	/** Quality of this item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	EItemQuality Quality = EItemQuality::Normal;

	/** How many of this item+quality combo the player holds */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 Quantity = 1;
};

// ─────────────────────────────────────────────
//  AShopKeeperCharacter
// ─────────────────────────────────────────────

UCLASS()
class GAMEJAMCUB2ND_API AShopKeeperCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShopKeeperCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ── Camera ────────────────────────────────

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	// ── Input ─────────────────────────────────

	/** Input mapping context — assign IMC_Shopkeeper in the editor */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Move action — assign IA_Move in the editor */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	/** Look action — assign IA_Look in the editor */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	/** Interact action — assign IA_Interact in the editor */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	// ── Inventory ─────────────────────────────

	/** The player's current inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventorySlot> Inventory;

	/** Adds an item to inventory — stacks if same item+quality already exists */
	void AddItem(UItemData* Item, EItemQuality Quality, int32 Quantity = 1);

	/** Removes one of a specific item+quality. Returns true if successful. */
	bool RemoveItem(UItemData* Item, EItemQuality Quality, int32 Quantity = 1);

	/** Returns true if the player has at least one of this item+quality */
	bool HasItem(UItemData* Item, EItemQuality Quality) const;

	/** Returns the quantity of a specific item+quality in inventory */
	int32 GetItemQuantity(UItemData* Item, EItemQuality Quality) const;

private:

	// ── Input Handlers ────────────────────────

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
};