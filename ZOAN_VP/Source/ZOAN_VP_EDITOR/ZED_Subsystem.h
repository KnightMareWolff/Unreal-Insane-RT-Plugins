// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ZED_Subsystem.generated.h"

/**
 * 
 */
UCLASS()
class ZOAN_VP_EDITOR_API UZED_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// Triggered when starting the application
	void Initialize  (FSubsystemCollectionBase& Collection) override;
	void Deinitialize(                                    ) override;

	static bool IsSimulationRunning;
	
};
