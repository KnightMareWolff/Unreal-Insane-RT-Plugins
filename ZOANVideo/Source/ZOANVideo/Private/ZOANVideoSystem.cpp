// Fill out your copyright notice in the Description page of Project Settings.


#include "ZOANVideoSystem.h"


bool UZOANVideoSystem::IsSimulationRunning = false;

void UZOANVideoSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    IsSimulationRunning = true;
    
    //Just a checking message box...
    //FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Simulation Start")));

}


void UZOANVideoSystem::Deinitialize()
{
    IsSimulationRunning = false;    
}