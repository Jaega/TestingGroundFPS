// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "PatrolRoute.h"
#include "Classes/AIController.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
    auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
    if(!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }
    // Get Patrol Points
    PatrolPoints = PatrolRoute->GetPatrolPoints();
    if(PatrolPoints.Num() == 0) 
    { 
        UE_LOG(LogTemp, Warning, TEXT("A guard missing patrol route"))
        return EBTNodeResult::Failed; 
    }

    // Set Next Way Point
    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    auto CurrentIndex = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    auto WayPoint = PatrolPoints[CurrentIndex];
    BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName, WayPoint);

    // Cycle Way Point Index
    auto NextIndex = (CurrentIndex + 1)%(PatrolPoints.Num());
    BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

    return EBTNodeResult::Succeeded;
}
