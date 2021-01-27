// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../Screens/ZED_ConfigurationData.h"
#include "Interfaces/IPluginManager.h"
#include "ZED_FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ZOAN_VP_EDITOR_API UZED_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Returns project configuration (the same for all machines)
	UFUNCTION(BlueprintCallable, Category = "ZOAN|ED")
    static bool ZEDInitializeGameInstance(UGameInstance *pGameInstance)
	{
		pEditorRealtimeInstance = pGameInstance;

		UWorld*  pWorld = pGameInstance->GetWorld();
		
		FVector location = FVector(-500, 500, 90);

		if (pWorld->IsValidLowLevel())
	    {
			AActor* SpawnedConfigTool = (AActor*)pWorld->SpawnActor(AZED_ConfigurationData::StaticClass(), &location);

	    	UGameplayStatics::GetAllActorsOfClass(pWorld, AZED_ConfigurationData::StaticClass(), FoundActors);
	    }

		// Plugin config folder location
		ZED_ConfigurationPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / "Config" / "ZOAN_VP");

		return true;
	}

	// Returns project configuration (the same for all machines)
	UFUNCTION(BlueprintCallable, Category = "ZOAN|ED")
	static UObject* ZEDGetObjectRef()
	{
		if (FoundActors.Num() > 0)	return Cast<UObject>(FoundActors[0]);
		else
			return NULL;
	}

	// Returns project configuration (the same for all machines)
	UFUNCTION(BlueprintCallable, Category = "ZOAN|ED")
	static FString ZEDGetRuntimePluginPath()
	{
		return ZED_ConfigurationPath;
	}
	

	static UGameInstance*  pEditorRealtimeInstance;
	static TArray<AActor*> FoundActors;
	static FString         ZED_ConfigurationPath;
	static FConfigFile     ZED_SessionConfigurationFile;
	static FConfigFile     ZED_ProjectConfigurationFile;
};