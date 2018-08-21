// Fill out your copyright notice in the Description page of Project Settings.

#include "InfinteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "PoolActComp.h"

AInfinteTerrainGameMode::AInfinteTerrainGameMode()
{
	CommonPool = CreateDefaultSubobject<UPoolActComp>(FName("NavMesh Pool"));
	
}

void AInfinteTerrainGameMode::PopulateBoundsVolume()
{
	TActorIterator <ANavMeshBoundsVolume> NavMeshIterator(GetWorld());
	while (NavMeshIterator)
	{
		UE_LOG(LogTemp, Warning, TEXT("NavMesh Found"))
		AddToPool(*NavMeshIterator);
		++NavMeshIterator;
	}
}

void AInfinteTerrainGameMode::AddToPool(ANavMeshBoundsVolume * NavMesh)
{
	CommonPool->Add(NavMesh);
}
