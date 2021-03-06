/************************************************************************/
/*Project              :IVR CameraMan - Unreal Plugin                   */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2021 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IVROpenCVHelperModule.h"
#include "Modules/ModuleManager.h" // for IMPLEMENT_MODULE()
#include "Interfaces/IPluginManager.h"
#include "HAL/PlatformProcess.h"
#include "Core.h"

class FIVRCVHelperModule : public IVRCVHelperModule
{
public:
	FIVRCVHelperModule();

public:
	//~ IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void* OpenCvDllHandle;
};

FIVRCVHelperModule::FIVRCVHelperModule()
	: OpenCvDllHandle(nullptr)
{}

void FIVRCVHelperModule::StartupModule()
{
	const FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("IVRCameraMan"))->GetBaseDir();

#if WITH_OPENCV
	const FString OpenCvBinPath = PluginDir / TEXT(PREPROCESSOR_TO_STRING(OPENCV_PLATFORM_PATH));
	const FString DLLPath = OpenCvBinPath / TEXT(PREPROCESSOR_TO_STRING(OPENCV_DLL_NAME));

	FPlatformProcess::PushDllDirectory(*OpenCvBinPath);
	OpenCvDllHandle = FPlatformProcess::GetDllHandle(*DLLPath);
	
	if (OpenCvDllHandle)
	{
		// Call the test function in the third party library that opens a message box
		//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Load OpenCV Properly")));
	}
	else
	{
   	    FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("OpenCV Load Error")));
	}

	FPlatformProcess::PopDllDirectory(*OpenCvBinPath);
#endif
}

void FIVRCVHelperModule::ShutdownModule()
{
#if WITH_OPENCV
	if (OpenCvDllHandle)
	{
		//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("OpenCV Was Deinitialized!")));
		FPlatformProcess::FreeDllHandle(OpenCvDllHandle);
		OpenCvDllHandle = nullptr;
	}
#endif
}

IMPLEMENT_MODULE(FIVRCVHelperModule, IVRCVHelper);
