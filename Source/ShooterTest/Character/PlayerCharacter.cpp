// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ShooterTest/Weapons/WeaponBase.h"

APlayerCharacter::APlayerCharacter()
{
	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FP_Gun = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
	
	Mesh1P->SetHiddenInGame(false, true);
	
	if(!FP_Gun) return;
	FP_Gun->SetUser(this);
	
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
							  TEXT("GripPoint"));
}

void APlayerCharacter::Attack_Implementation()
{
	Super::Attack_Implementation();
	if(OnFire.IsBound())
	{
		OnFire.Broadcast();
	}
}

void APlayerCharacter::AltAttack_Implementation()
{
	Super::AltAttack_Implementation();
	if(OnAltFire.IsBound())
	{
		OnAltFire.Broadcast();
	}
}

void APlayerCharacter::Die_Implementation()
{
	Super::Die_Implementation();
}
