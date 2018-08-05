// Fill out your copyright notice in the Description page of Project Settings.

#include "TileActor.h"
#include"Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATileActor::ATileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATileActor::SpawnPointGenerator(TSubclassOf<AActor>SpawnProps,int MinSpawn,int MaxSpawn,float Radius)
{
	int NumbertoSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	FVector SpawnPoint;
	for (size_t i = 0; i <= NumbertoSpawn; i++)
	{
		if (GetEmptySpace(SpawnPoint,Radius))
		{
			UE_LOG(LogTemp, Warning, TEXT("Free to Spawn"))
			SpawnProp(SpawnProps, SpawnPoint);
		}
		else
			UE_LOG(LogTemp,Warning,TEXT("SweepResult returns hit"))
	}
}

bool ATileActor::GetEmptySpace(FVector &SpawnPoint,float Radius)
{
	FVector Min(0, -2000, 400);
	FVector Max(4000, 2000, 600);
	FBox Bounds = FBox(Min, Max);
	int MaxAttempts = 100;
	FVector CandidateKey;
	for (int i = 0; i < MaxAttempts; i++)
	{
		CandidateKey=FMath::RandPointInBox(Bounds);
		if (CastSphere(CandidateKey, Radius))
		{
			SpawnPoint = CandidateKey;
			return true;
		}
	}
	return false;
}

void ATileActor::SpawnProp(TSubclassOf<AActor>SpawnProps, FVector SpawnLocation)
{
	AActor* SpawnedProp = GetWorld()->SpawnActor<AActor>(SpawnProps);
	SpawnedProp->SetActorRelativeLocation(SpawnLocation);
	SpawnedProp->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
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

bool ATileActor::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation=ActorToWorld().TransformPosition(Location);
	bool HasHit=GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12, FCollisionShape::MakeSphere(Radius));
	if (HasHit)
	{
		auto HitActor=	HitResult.Actor;
		UE_LOG(LogTemp,Warning,TEXT("%s is colliding"),*HitActor->GetName())
	}
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(),GlobalLocation, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	return !HasHit;
}

