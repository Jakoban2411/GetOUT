// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseTheNextWay.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"PatrolRoute.h"
#include"Classes/AIController.h"

EBTNodeResult::Type UChooseTheNextWay::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* AIOwner=OwnerComp.GetAIOwner();
	auto AICharacter=AIOwner-> GetPawn();
	UPatrolRoute* RouteWay = AICharacter->FindComponentByClass<UPatrolRoute>();
	if (!RouteWay) 
	{
		UE_LOG(LogTemp,Warning,TEXT("SHIT"))
		return EBTNodeResult::Failed;
	}
	int32 PatrolIndex = BlackboardComp->GetValueAsInt(Index.SelectedKeyName);
	if (AICharacter)
	{
		TArray<AActor*> Points=RouteWay->PatrolPoints;
		BlackboardComp->SetValueAsObject(KeySelector.SelectedKeyName,Points[PatrolIndex]);
		BlackboardComp->SetValueAsInt(Index.SelectedKeyName, (PatrolIndex+1)% Points.Num());
		
	}
	
	return EBTNodeResult::Succeeded;
}
