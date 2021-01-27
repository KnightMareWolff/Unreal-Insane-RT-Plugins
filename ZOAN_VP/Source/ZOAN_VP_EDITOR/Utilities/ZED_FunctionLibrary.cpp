// Fill out your copyright notice in the Description page of Project Settings.


#include "ZED_FunctionLibrary.h"

UGameInstance*  UZED_FunctionLibrary::pEditorRealtimeInstance = NULL;
TArray<AActor*> UZED_FunctionLibrary::FoundActors;
FString         UZED_FunctionLibrary::ZED_ConfigurationPath;
FConfigFile     UZED_FunctionLibrary::ZED_SessionConfigurationFile;
FConfigFile     UZED_FunctionLibrary::ZED_ProjectConfigurationFile;