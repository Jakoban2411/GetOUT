// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GetOUTGameMode.h"
#include "InfinteTerrainGameMode.generated.h"
class ANavMeshBoundsVolume;
class UPoolActComp;
/**
 * 
 */
UCLASS()
class GETOUT_API AInfinteTerrainGameMode : public AGetOUTGameMode
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable)
		void PopulateBoundsVolume();
	AInfinteTerrainGameMode();
	void AddToPool(ANavMeshBoundsVolume* NavMesh);
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UPoolActComp* CommonPool;
	int32 Score = 0;
	UFUNCTION(BlueprintCallable,Category= Scoring)
	void AddScore(int32 AddToScore);
	UFUNCTION(BlueprintCallable, Category = Scoring)
	int32 GetScore();
};
