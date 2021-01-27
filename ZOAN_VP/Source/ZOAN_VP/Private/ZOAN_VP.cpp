// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZOAN_VP.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "FZOAN_VPModule"

void FZOAN_VPModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FZOAN_VPModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FZOAN_VPModule, ZOAN_VP)

DEFINE_LOG_CATEGORY(ZVPLog);