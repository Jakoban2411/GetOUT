// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolActComp.h"

// Sets default values for this component's properties
UPoolActComp::UPoolActComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPoolActComp::BeginPlay()
{
	Super::BeginPlay();
		
	
}


// Called every frame
void UPoolActComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPoolActComp::Add(AActor * ActorToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Add Called"))
	ReturnToPool(ActorToAdd);
}

AActor * UPoolActComp::CheckOut()
{
	if (PoolActors.Num() == 0)
	{
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkout Pop Successfull"))
			return PoolActors.Pop();//return nullptr;		
	}
}

void UPoolActComp::ReturnToPool(AActor * ReturnedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Pushing Successfull"))
	PoolActors.Push(ReturnedActor);
}

