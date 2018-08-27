// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"
class UPoolActComp;

USTRUCT()
struct FSpawnPointTransform
{
	GENERATED_USTRUCT_BODY();
	FVector Location;
	float Scale;
	float Rotation;
};

UCLASS()
class GETOUT_API ATileActor : public AActor
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ATileActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = SpawnPoint)
		void SpawnPointGenerator(TSubclassOf<AActor>SpawnProps, int MinSpawn, int MaxSpawn, float Radius, float ScaleMin = 1.f, float ScaleMax = 1.f);
	UFUNCTION(BlueprintCallable, Category = SpawnPoint)
		void SpawnAI(TSubclassOf<APawn> AIPawn, int MinSpawn, int MaxSpawn, float Radius);
	void PlaceActor(TSubclassOf<APawn> &AIPawn, FSpawnPointTransform &SpawnPosition);
	template<class T>
	void RandomlySpawnActors(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);
	bool CastSphere(FVector Location, float Radius);
	bool GetEmptySpace(FVector &SpawnPoint,float Radius);
	void PlaceActor(TSubclassOf<AActor>SpawnProps,FSpawnPointTransform SpawnTransform);
	UPoolActComp* TilePool;
	//TArray<FSpawnPointTransform> RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float ScaleMin, float ScaleMax);
	UFUNCTION(BlueprintCallable, Category = NavMeshPoolSetter)
		void PoolSet(UPoolActComp* Pool);
	void PositionNavMesh();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	AActor* NavMesh;
	void AddScore(int Score);
};

