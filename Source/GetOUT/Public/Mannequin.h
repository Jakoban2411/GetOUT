// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

class UCameraComponent;
class AGun;
UCLASS()
class GETOUT_API AMannequin : public ACharacter	
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;
	//Gun
	UPROPERTY(EditAnywhere, Category = Mesh)
		TSubclassOf<AGun> SpawnGun;
	AGun* Gun;
	UFUNCTION(BlueprintCallable, Category = Fire)
		void Fire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void UnPossessed() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void FireDelegate();
	FTimerHandle BurstHandle;
	int32 BulletsFired = 0;
	bool bHasFired=false;
};
