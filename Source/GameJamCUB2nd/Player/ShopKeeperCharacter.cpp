// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopKeeperCharacter.h"

// Sets default values
AShopKeeperCharacter::AShopKeeperCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShopKeeperCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShopKeeperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShopKeeperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

