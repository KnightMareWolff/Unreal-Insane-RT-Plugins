/************************************************************************/
/*Project              :IVR CameraMan - Unreal Plugin                   */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2021 William Wolff. All rights reserved                 */
/************************************************************************/

#include "IVR_WidgetBuilder.h"
#include "PropertyCustomizationHelpers.h"
#include "UnrealEd.h"
#include "IVRCameraManEditorSubsystem.h"


void UIVR_WidgetBuilder::BuildWidget()
{

	// Instance a new Object for the Screen Templates(Will be used to read and Write The User Inputs)
	IVR_ConfigurationDataSource = NewObject<UIVR_DefaultCameraParameters>(GetTransientPackage(), UIVR_DefaultCameraParameters::StaticClass());
	IVR_SuperResDataSource = NewObject<UIVR_SuperResolutionParameters>(GetTransientPackage(), UIVR_SuperResolutionParameters::StaticClass());

	//The property and asset editors are Singleton! So...just initialize the reference , make the job and Go!
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//Register the custam class for the Default Parameters
	PropertyModule.RegisterCustomClassLayout(UIVR_DefaultCameraParameters::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FIVR_DetailCustomizer::MakeInstance));

	PropertyModule.RegisterCustomPropertyTypeLayout(UIVR_DefaultCameraParameters::StaticClass()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FIVR_PropertyCustomizer::MakeInstance));
	
	PropertyModule.NotifyCustomizationModuleChanged();

	//Fill the Default Parameters View Args
	FDetailsViewArgs DefaultDetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);
	//DefaultDetailsViewArgs.bShowActorLabel = false;
	
	// create the detail view widget
	pWidgetView     = PropertyModule.CreateDetailView(DefaultDetailsViewArgs);

	//Now we already have the main Detail View, we register the Experimental Parameters View
	PropertyModule.RegisterCustomClassLayout(UIVR_SuperResolutionParameters::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FIVR_SuperDetailCustomizer::MakeInstance));

	PropertyModule.RegisterCustomPropertyTypeLayout(UIVR_SuperResolutionParameters::StaticClass()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FIVR_SuperPropertyCustomizer::MakeInstance));
	
	//Fill the Experimental Parameters View Args
	FDetailsViewArgs SuperDetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);
	//SuperDetailsViewArgs.bShowActorLabel = false;

	// create the Experimental View
	pSuperResWidget = PropertyModule.CreateDetailView(SuperDetailsViewArgs);
	
	const FString ConfigFilesFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / "Config" / "IVRCameraMan");

	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	if (PF.CreateDirectoryTree(*ConfigFilesFolderPath) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create/ensure plugin config folder creation!"));
		return;
	}

	UIVRCameraManEditorSubsystem::ReadCameraManDefaultValues(IVR_ConfigurationDataSource->IVR_RecordingPath,
		IVR_ConfigurationDataSource->IVR_Width,
		IVR_ConfigurationDataSource->IVR_Height,
		IVR_ConfigurationDataSource->IVR_ClearColor,
		IVR_ConfigurationDataSource->IVR_Gamma,
		IVR_ConfigurationDataSource->IVR_EnableTurboRecording,
		IVR_ConfigurationDataSource->IVR_TurboRate,
		IVR_ConfigurationDataSource->IVR_StabilizationArm,
		IVR_ConfigurationDataSource->IVR_LagDistance,
		IVR_ConfigurationDataSource->IVR_CameraManName,
		IVR_ConfigurationDataSource->IVR_CameraVelocity,
		IVR_ConfigurationDataSource->IVR_BaseTurnRate,
		IVR_ConfigurationDataSource->IVR_BaseLookUpRate);

	FString OpticalFlow;
	UIVRCameraManEditorSubsystem::ReadExperimentalParametersValues(IVR_SuperResDataSource->IVR_SuperScale,
		IVR_SuperResDataSource->IVR_SuperIterations,
		IVR_SuperResDataSource->IVR_SuperTemporalRadius,
		OpticalFlow);

	//Fill the Enum Details.
	if (OpticalFlow.Contains(TEXT("Farneback")))
	{
		IVR_SuperResDataSource->IVR_SuperOpticalFlow = EIVR_OpticalFlowType::IVR_Farneback;
	}
	else if (OpticalFlow.Contains(TEXT("TVL1")))
	{
		IVR_SuperResDataSource->IVR_SuperOpticalFlow = EIVR_OpticalFlowType::IVR_TVL1;
	}
	else if (OpticalFlow.Contains(TEXT("Brox")))
	{
		IVR_SuperResDataSource->IVR_SuperOpticalFlow = EIVR_OpticalFlowType::IVR_Brox;
	}
	else if (OpticalFlow.Contains(TEXT("PYRLK")))
	{
		IVR_SuperResDataSource->IVR_SuperOpticalFlow = EIVR_OpticalFlowType::IVR_PYRLK;
	}
	else
	{
		IVR_SuperResDataSource->IVR_SuperOpticalFlow = EIVR_OpticalFlowType::IVR_Farneback;
	}
	

	// set the object to have its properties displayed
	pWidgetView->SetObject(IVR_ConfigurationDataSource);
	pSuperResWidget->SetObject(IVR_SuperResDataSource);

	//pWidgetView->OnFinishedChangingProperties().AddRaw(this, &UIVR_WidgetBuilder::OnFinishedChangingProperties);
	pWidgetView    ->OnFinishedChangingProperties().AddUObject(this,&UIVR_WidgetBuilder::OnFinishedChangingProperties);
	pSuperResWidget->OnFinishedChangingProperties().AddUObject(this, &UIVR_WidgetBuilder::OnFinishedChangingProperties);
}

void UIVR_WidgetBuilder::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	int NumberOfHandles = FIVR_DetailCustomizer::IVR_PropertyHandleList.Num();

	UIVRCameraManEditorSubsystem::WriteCameraManDefaultValues(
	IVR_ConfigurationDataSource->IVR_RecordingPath,
	IVR_ConfigurationDataSource->IVR_Width,
	IVR_ConfigurationDataSource->IVR_Height,
	IVR_ConfigurationDataSource->IVR_ClearColor,
	IVR_ConfigurationDataSource->IVR_Gamma,
	IVR_ConfigurationDataSource->IVR_EnableTurboRecording,
	IVR_ConfigurationDataSource->IVR_TurboRate,
	IVR_ConfigurationDataSource->IVR_StabilizationArm,
	IVR_ConfigurationDataSource->IVR_LagDistance,
	IVR_ConfigurationDataSource->IVR_CameraManName,
	IVR_ConfigurationDataSource->IVR_CameraVelocity,
	IVR_ConfigurationDataSource->IVR_BaseTurnRate,
	IVR_ConfigurationDataSource->IVR_BaseLookUpRate);

	FString OpticalFlow;
	//Fill the Enum Details.
	if (IVR_SuperResDataSource->IVR_SuperOpticalFlow == EIVR_OpticalFlowType::IVR_Farneback)
	{
		OpticalFlow = "Farneback";
	}
	else if (IVR_SuperResDataSource->IVR_SuperOpticalFlow == EIVR_OpticalFlowType::IVR_TVL1)
	{
		OpticalFlow = "TVL1";
	}
	else if (IVR_SuperResDataSource->IVR_SuperOpticalFlow == EIVR_OpticalFlowType::IVR_Brox)
	{
		OpticalFlow = "Brox";
	}
	else if (IVR_SuperResDataSource->IVR_SuperOpticalFlow == EIVR_OpticalFlowType::IVR_PYRLK)
	{
		OpticalFlow = "PYRLK";
	}
	else
	{
		OpticalFlow = "Farneback";
	}

	UIVRCameraManEditorSubsystem::WriteExperimentalParametersValues(
		IVR_SuperResDataSource->IVR_SuperScale,
		IVR_SuperResDataSource->IVR_SuperIterations,
		IVR_SuperResDataSource->IVR_SuperTemporalRadius,
		OpticalFlow);

	
}
