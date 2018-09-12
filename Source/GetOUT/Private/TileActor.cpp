// Fill out your copyright notice in the Description page of Project Settings.

#include "TileActor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PoolActComp.h"
#include "Mannequin.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/AI/Navigation/NavigationSystem.h"

// Sets default values
ATileActor::ATileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATileActor::SpawnPointGenerator(TSubclassOf<AActor>SpawnProps,int MinSpawn,int MaxSpawn,float Radius,float ScaleMin,float ScaleMax)
{
	RandomlySpawnActors(SpawnProps, MinSpawn, MaxSpawn, Radius, ScaleMin, ScaleMax);
}

void ATileActor::SpawnAI(TSubclassOf<APawn> AIPawn,int MinSpawn, int MaxSpawn, float Radius)
{
	RandomlySpawnActors(AIPawn, MinSpawn, MaxSpawn, Radius, 1.f, 1.f);
}
template<class T>
void ATileActor::RandomlySpawnActors(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPointTransform SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool found = GetEmptySpace(SpawnPosition.Location, Radius * SpawnPosition.Scale);
		if (found)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPosition);
		}
	}
}

/*TArray<FSpawnPointTransform> ATileActor::RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPointTransform> SpawnPointTransformArray;
	FSpawnPointTransform SpawnTransform;
	FVector SpawnPoint;
	int NumbertoSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i <= NumbertoSpawn; i++)
	{
		SpawnTransform.Scale = FMath::RandRange(MinScale, MaxScale);
		if (GetEmptySpace(SpawnTransform.Location, Radius*SpawnTransform.Scale))
		{

			SpawnTransform.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnPointTransformArray.Add(SpawnTransform);
		}

	}
	return SpawnPointTransformArray;
}*/

bool ATileActor::GetEmptySpace(FVector &SpawnPoint, float Radius)
{
	FVector Min(100, -2000, -190);
	FVector Max(4000, 2000, -184);
	FBox Bounds = FBox(Min, Max);
	int MaxAttempts = 100;
	FVector CandidateKey;
	for (int i = 0; i < MaxAttempts; i++)
	{
		CandidateKey = FMath::RandPointInBox(Bounds);
		if (CastSphere(CandidateKey, Radius))
		{
			SpawnPoint = CandidateKey;
			return true;
		}
	}
	return false;
}

bool ATileActor::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	if (HasHit)
	{
		auto HitActor = HitResult.Actor;
		UE_LOG(LogTemp, Warning, TEXT("%s is colliding"), *HitActor->GetName())
	}
	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	return !HasHit;
}

void ATileActor::PlaceActor(TSubclassOf<APawn> &AIPawn, FSpawnPointTransform &SpawnPosition)
{
	APawn* SpawnedAI = GetWorld()->SpawnActor<APawn>(AIPawn);
	if (SpawnedAI)
	{
		SpawnedAI->SetActorRelativeLocation(SpawnPosition.Location);
		SpawnedAI->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SpawnedAI->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
		SpawnedAI->SpawnDefaultController();
		SpawnedAI->Tags.Add(FName("Enemies"));
	}
}

void ATileActor::PlaceActor(TSubclassOf<AActor>SpawnProps, FSpawnPointTransform SpawnPoint)
{
	AActor* SpawnedProp = GetWorld()->SpawnActor<AActor>(SpawnProps);
	if (SpawnedProp)
	{
		SpawnedProp->SetActorRelativeLocation(SpawnPoint.Location);
		SpawnedProp->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SpawnedProp->SetActorRotation(FRotator(0, SpawnPoint.Rotation, 0));
		SpawnedProp->SetActorScale3D(FVector(SpawnPoint.Scale));
	}
}


void ATileActor::PoolSet(UPoolActComp * Pool)
{
		TilePool = Pool;
		PositionNavMesh();
}

void ATileActor::PositionNavMesh()
{
	NavMesh = TilePool->CheckOut();
	if (NavMesh != nullptr)
	{
		NavMesh->SetActorLocation(FVector(GetActorLocation().X + 2000.f, GetActorLocation().Y, GetActorLocation().Z));
		GetWorld()->GetNavigationSystem()->Build();
	}
}

void ATileActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(TilePool!=nullptr && NavMesh!=nullptr)
	TilePool->ReturnToPool(NavMesh);
}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}