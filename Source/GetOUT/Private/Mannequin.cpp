// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include"Components/SkeletalMeshComponent.h"
#include"Camera/CameraComponent.h"
#include"Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include"Gun.h"
#include"Public/TimerManager.h"
#include"Engine/World.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	


}

void AMannequin::Fire()
{
	if (bHasFired == false)
	{
		bHasFired = true;
		GetWorldTimerManager().SetTimer(BurstHandle, this, &AMannequin::FireDelegate, .1f, true, 0.f);
		//if (GetWorldTimerManager().GetTimerElapsed(BurstHandle) <= Gun->BurstTime)	
		//	GetWorldTimerManager().ClearTimer(BurstHandle);
	}
	else
		UE_LOG(LogTemp,Warning,TEXT("%s is HasFired"),(bHasFired?TEXT("True"):TEXT("False")))
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActorDeferred<AGun>(SpawnGun, GetTransform());
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	if (IsPlayerControlled())
	{
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	UGameplayStatics::FinishSpawningActor(Gun, GetTransform());
	Gun->SetOwner(this);
	Gun->AnimInstance1P = Mesh1P->GetAnimInstance();
	Gun->AnimInstance3P = GetMesh()->GetAnimInstance();
	if (InputComponent != nullptr)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::Fire);
	}
}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();
	if(Gun!=nullptr)
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AMannequin::FireDelegate()
{
	if (BulletsFired <= Gun->Rounds)
	{
		Gun->OnFire();
		BulletsFired += 1;
		//UE_LOG(LogTemp,Warning,TEXT("%f:Time Elapsed"), GetWorldTimerManager().GetTimerElapsed(BurstHandle))

	}
	else
	{
		GetWorldTimerManager().ClearTimer(BurstHandle);
		bHasFired = false;
		BulletsFired = 0;
	}
}

