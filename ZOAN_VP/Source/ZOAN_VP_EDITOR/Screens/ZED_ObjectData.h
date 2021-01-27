// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MediaSource.h"
#include "MediaOutput.h"
#include "ZED_ConfigurationData.h"
#include "ZED_ObjectData.generated.h"


/**
 * 
 */
UCLASS()
class ZOAN_VP_EDITOR_API UZED_ObjectData : public UObject
{
	GENERATED_BODY()
public:
	
	// Session configuration (specific machine values)
	UPROPERTY(EditAnywhere, Category = "Machine Settings", DisplayName = "Session Configuration")
	FZED_SessionConfig ZED_SessionConfig;

	// Project configuration (doesn't change between machines)
	UPROPERTY(EditAnywhere, Category = "Project Settings", DisplayName = "Project Objects")
	FZED_ProjectConfig ZED_ProjectConfig;


	//Important Method to collect the struct containers
	void   * GetStructContainer(FName pPropertyName);
	UObject* GetStructObject(FName pPropertyName);
	
};
