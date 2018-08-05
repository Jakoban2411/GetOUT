// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"

UCLASS()
class GETOUT_API ATileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileActor();
	UFUNCTION(BlueprintCallable, Category = SpawnPoint)
		void SpawnPointGenerator(TSubclassOf<AActor>SpawnProps,int MinSpawn,int MaxSpawn, float Radius);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool CastSphere(FVector Location, float Radius);
	bool GetEmptySpace(FVector SpawnPoint,float Radius);
	void SpawnProp(TSubclassOf<AActor>SpawnProps, FVector SpawnLocation);
	
};
