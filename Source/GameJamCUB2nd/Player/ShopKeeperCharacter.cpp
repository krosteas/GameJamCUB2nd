// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ShopKeeperCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AShopKeeperCharacter::AShopKeeperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create first person camera attached to the head
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), FName("head"));
	FirstPersonCamera->bUsePawnControlRotation = true;
}

void AShopKeeperCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Register the input mapping context with the Enhanced Input subsystem
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AShopKeeperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShopKeeperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction,     ETriggerEvent::Triggered, this, &AShopKeeperCharacter::Move);
		EIC->BindAction(LookAction,     ETriggerEvent::Triggered, this, &AShopKeeperCharacter::Look);
		EIC->BindAction(InteractAction, ETriggerEvent::Started,   this, &AShopKeeperCharacter::Interact);
	}
}

// ─────────────────────────────────────────────
//  Input Handlers
// ─────────────────────────────────────────────

void AShopKeeperCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(),   MovementVector.X);
	}
}

void AShopKeeperCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void AShopKeeperCharacter::Interact()
{
	// TODO: hook into InteractionComponent here once teammate finishes it
	// e.g. InteractionComponent->TryInteract();
	UE_LOG(LogTemp, Log, TEXT("Interact pressed"));
}

// ─────────────────────────────────────────────
//  Inventory
// ─────────────────────────────────────────────

void AShopKeeperCharacter::AddItem(UItemData* Item, EItemQuality Quality, int32 Quantity)
{
	if (!Item || Quantity <= 0) return;

	// Check if this item+quality combo already exists — if so stack it
	for (FInventorySlot& Slot : Inventory)
	{
		if (Slot.Item == Item && Slot.Quality == Quality)
		{
			Slot.Quantity += Quantity;
			UE_LOG(LogTemp, Log, TEXT("Stacked %s (x%d)"), *Item->ItemName.ToString(), Slot.Quantity);
			return;
		}
	}

	// Otherwise add a new slot
	FInventorySlot NewSlot;
	NewSlot.Item     = Item;
	NewSlot.Quality  = Quality;
	NewSlot.Quantity = Quantity;
	Inventory.Add(NewSlot);

	UE_LOG(LogTemp, Log, TEXT("Added %s to inventory"), *Item->ItemName.ToString());
}

bool AShopKeeperCharacter::RemoveItem(UItemData* Item, EItemQuality Quality, int32 Quantity)
{
	if (!Item || Quantity <= 0) return false;

	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		FInventorySlot& Slot = Inventory[i];
		if (Slot.Item != Item || Slot.Quality != Quality) continue;

		if (Slot.Quantity < Quantity)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not enough %s in inventory"), *Item->ItemName.ToString());
			return false;
		}

		Slot.Quantity -= Quantity;

		// Remove the slot entirely if quantity hits zero
		if (Slot.Quantity == 0)
			Inventory.RemoveAt(i);

		return true;
	}

	return false;
}

bool AShopKeeperCharacter::HasItem(UItemData* Item, EItemQuality Quality) const
{
	return GetItemQuantity(Item, Quality) > 0;
}

int32 AShopKeeperCharacter::GetItemQuantity(UItemData* Item, EItemQuality Quality) const
{
	if (!Item) return 0;

	for (const FInventorySlot& Slot : Inventory)
	{
		if (Slot.Item == Item && Slot.Quality == Quality)
			return Slot.Quantity;
	}

	return 0;
}