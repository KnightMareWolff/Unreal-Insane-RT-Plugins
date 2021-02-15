// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "ZVR_FunctionLibrary.h" //The Function Library already have the OpenCV Includes

#include "ZOANVideoSystem.generated.h"

/**
 * 
 */
UCLASS()
class ZOANVIDEO_API UZOANVideoSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
    
	// Triggered when starting the application
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	static bool IsSimulationRunning;	
};
