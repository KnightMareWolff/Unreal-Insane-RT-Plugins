/******************************************************************************/
/*Project: ZOAN Editor Extensions                                             */
/*Description:                                                                */
/*The Zoan Editor Extensions is a plug-In responsible to handle the runtime   */
/*Object Customizations and Parameterization for the Zoan Runtime Production  */
/*Plug-In                                                                     */
/******************************************************************************/
/*Object Description:                                                         */
/******************************************************************************/
/*Copyright Zoan Oy, Inc. All Rights Reserved.                                */
/*Author: William D. Wolff                                                    */
/******************************************************************************/
#include "ZED_WidgetBuilder.h"
#include "ZED_PropertyCustomizer.h"
#include "PropertyCustomizationHelpers.h"
#include "UnrealEd.h"


//Reference of the static view component
TSharedPtr<IDetailsView> FZED_WidgetBuilder::pWidgetView;

FZED_WidgetBuilder::FZED_WidgetBuilder()
{
	//The property and asset editors are Singleton! So...just initialize the reference , make the job and Go!
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(UZED_ObjectData::StaticClass()->GetFName(),
		                                     FOnGetDetailCustomizationInstance::CreateStatic(&FZED_DetailCustomizer::MakeInstance));

	PropertyModule.RegisterCustomPropertyTypeLayout(UZED_ObjectData::StaticClass()->GetFName(),
		                                            FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FZED_PropertyCustomizer::MakeInstance));

	PropertyModule.NotifyCustomizationModuleChanged();

	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);

	DetailsViewArgs.bShowActorLabel = false;

	// create the detail view widget
	pWidgetView = PropertyModule.CreateDetailView(DetailsViewArgs);

	// Instance a new Object (For Realtime processing  must be an AActor and use the World)
	ZED_ConfigurationDataSource = NewObject<UZED_ObjectData>(GetTransientPackage(), UZED_ObjectData::StaticClass());

	ConfigFilesFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / "Config" / "ZOAN_VP");

	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	if (PF.CreateDirectoryTree(*ConfigFilesFolderPath) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create/ensure plugin config folder creation!"));
		return;
	}

	ReadSession();
	ReadProject();
	
	//session config
	ZED_ConfigurationDataSource->ZED_SessionConfig.ZED_MachineName				= SessionConfig.ZED_MachineName;
	ZED_ConfigurationDataSource->ZED_SessionConfig.ZED_CameraInputSoftPtr		= SessionConfig.ZED_CameraInputSoftPtr;
	ZED_ConfigurationDataSource->ZED_SessionConfig.ZED_CameraOutputSoftPtr		= SessionConfig.ZED_CameraOutputSoftPtr;
	ZED_ConfigurationDataSource->ZED_SessionConfig.ZED_DefaultCameraType		= SessionConfig.ZED_DefaultCameraType;
	ZED_ConfigurationDataSource->ZED_SessionConfig.ZED_DefaultCameraGroup		= SessionConfig.ZED_DefaultCameraGroup;
	//project config
	ZED_ConfigurationDataSource->ZED_ProjectConfig.ZED_EventManagerClassSoftPtr		= ProjectConfig.ZED_EventManagerClassSoftPtr;
	ZED_ConfigurationDataSource->ZED_ProjectConfig.ZED_EventListenerClassSoftPtr	= ProjectConfig.ZED_EventListenerClassSoftPtr;
	ZED_ConfigurationDataSource->ZED_ProjectConfig.ZED_SongsDataTableSoftPtr		= ProjectConfig.ZED_SongsDataTableSoftPtr;
	ZED_ConfigurationDataSource->ZED_ProjectConfig.ZED_LevelsDataTableSoftPtr		= ProjectConfig.ZED_LevelsDataTableSoftPtr;
	ZED_ConfigurationDataSource->ZED_ProjectConfig.ZED_UDPPort						= ProjectConfig.ZED_UDPPort;

	// set the object to have its properties displayed
	pWidgetView->SetObject(ZED_ConfigurationDataSource);
	
	pWidgetView->OnFinishedChangingProperties().AddRaw(this, &FZED_WidgetBuilder::OnFinishedChangingProperties);

}

void FZED_WidgetBuilder::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	//Decleare Local values for standalone execution 
	FString                      LocalConfigFilesFolderPath;
	FString                      LocalMachineName;
	UObject                    * LocalCameraInputSoftPtr  = NULL;
	UObject                    * LocalCameraOutputSoftPtr = NULL;
	FString                      LocalDefaultCameraType;
	FString                      LocalDefaultCameraGroup;
	FString                      LocalVirtualCameraFocusType;//Not yet implemented
	UObject                    * LocalEventManagerClassSoftPtr = NULL;
	UObject                    * LocalEventListenerClassSoftPtr = NULL;
	UObject                    * LocalSongsDataTableSoftPtr = NULL;
	UObject                    * LocalLevelsDataTableSoftPtr = NULL;
	int32                        LocalUDPPort = 8888;

	int NumberOfHandles = FZED_DetailCustomizer::ZED_PropertyHandleList.Num();

	//Allways get the Path, since the Unreal Architecture Lost the Entire Class scope during execution
	//(Remember we are inside of a class function being executed as a standalone pointer we not have the execution stack anymore...)
	LocalConfigFilesFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / "Config" / "ZOAN_VP");
	
	//Recurse all the handles extracted by the View (Just to help if we need threat specific cases...)
	for (int32 i = 0; i < NumberOfHandles; i++)
	{
		FString tFieldName;
		FString tObjectValue;
		
		tFieldName   = FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldName;
		
		if (tFieldName == "ZED_MachineName")
		{
			FProperty* pProperty = FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty;

			FString* StrPtr = pProperty->ContainerPtrToValuePtr<FString>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
			if (StrPtr != NULL)
			{
				LocalMachineName = *StrPtr;
			}
		}
		else if (tFieldName == "ZED_CameraInputSoftPtr")
		{
			FSoftObjectProperty* pProperty = CastField<FSoftObjectProperty>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty);
			
			if (pProperty->IsValidLowLevel())
			{
				void* StrPtr = pProperty->ContainerPtrToValuePtr<void>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
				if (StrPtr != NULL)
				{
					LocalCameraInputSoftPtr = pProperty->LoadObjectPropertyValue(StrPtr);
				}
			}
		}
		else if (tFieldName == "ZED_CameraOutputSoftPtr")
		{
			FSoftObjectProperty* pProperty = CastField<FSoftObjectProperty>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty);

			if (pProperty->IsValidLowLevel())
			{
				void* StrPtr = pProperty->ContainerPtrToValuePtr<void>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
				if (StrPtr != NULL)
				{
					LocalCameraOutputSoftPtr = pProperty->LoadObjectPropertyValue(StrPtr);
				}
			}
		}
		else if (tFieldName == "ZED_DefaultCameraType")
		{
			FEnumProperty* pProperty = CastField<FEnumProperty>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty);
			UEnum* EnumPtr = pProperty->GetEnum();

			//Get the Enum Value
			int* StrPtr = pProperty->ContainerPtrToValuePtr<int>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
			if (StrPtr != NULL)
			{
				//Get the string of the Value
				LocalDefaultCameraType = EnumPtr->GetDisplayNameTextByValue(*StrPtr).ToString().Replace(TEXT(" "), TEXT(""));
			}

		}
		else if (tFieldName == "ZED_DefaultCameraGroup")
		{
			FEnumProperty* pProperty = CastField<FEnumProperty>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty);
			UEnum* EnumPtr = pProperty->GetEnum();

			//Get the Enum Value
			int* StrPtr = pProperty->ContainerPtrToValuePtr<int>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
			if (StrPtr != NULL)
			{
				//Get the string of the Value
				LocalDefaultCameraGroup = EnumPtr->GetDisplayNameTextByValue(*StrPtr).ToString().Replace(TEXT(" "), TEXT(""));
			}
		}
		else if (tFieldName == "ZED_EventManagerClassSoftPtr")
		{
			FSoftClassProperty* pProperty = CastField<FSoftClassProperty>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty);

			if (pProperty->IsValidLowLevel())
			{
				void* StrPtr = pProperty->ContainerPtrToValuePtr<void>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
				if (StrPtr != NULL)
				{
					LocalEventManagerClassSoftPtr = pProperty->LoadObjectPropertyValue(StrPtr);
				}
			}
		}
		else if (tFieldName == "ZED_EventListenerClassSoftPtr")
		{
			FSoftClassProperty* pProperty = CastField<FSoftClassProperty>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty);

			if (pProperty->IsValidLowLevel())
			{
				void* StrPtr = pProperty->ContainerPtrToValuePtr<void>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
				if (StrPtr != NULL)
				{
					LocalEventListenerClassSoftPtr = pProperty->LoadObjectPropertyValue(StrPtr);
				}
			}
		}
		else if (tFieldName == "ZED_SongsDataTableSoftPtr")
		{
			FSoftObjectProperty* pProperty = CastField<FSoftObjectProperty>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty);

			if (pProperty->IsValidLowLevel())
			{
				void* StrPtr = pProperty->ContainerPtrToValuePtr<void>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
				if (StrPtr != NULL)
				{
					LocalSongsDataTableSoftPtr = pProperty->LoadObjectPropertyValue(StrPtr);
				}
			}
		}
		else if (tFieldName == "ZED_LevelsDataTableSoftPtr")
		{
			FSoftObjectProperty* pProperty = CastField<FSoftObjectProperty>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty);

			if (pProperty->IsValidLowLevel())
			{
				void* StrPtr = pProperty->ContainerPtrToValuePtr<void>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
				if (StrPtr != NULL)
				{
					LocalLevelsDataTableSoftPtr = pProperty->LoadObjectPropertyValue(StrPtr);
				}
			}
		}
		else if (tFieldName == "ZED_UDPPort")
		{
			FProperty* pProperty = FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldProperty;

			int* StrPtr = pProperty->ContainerPtrToValuePtr<int>(FZED_DetailCustomizer::ZED_PropertyHandleList[i].Get()->FieldContainer);
			if (StrPtr != NULL)
			{
				LocalUDPPort = *StrPtr;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%d] Handle"), i);
		}
		
	}

	WriteSession(LocalConfigFilesFolderPath,
		         LocalMachineName,
		         LocalCameraInputSoftPtr,
		         LocalCameraOutputSoftPtr,
		         LocalDefaultCameraType,
		         LocalDefaultCameraGroup);

	WriteProject(LocalConfigFilesFolderPath,
		         LocalVirtualCameraFocusType,
		         LocalEventManagerClassSoftPtr,
		         LocalEventListenerClassSoftPtr,
		         LocalSongsDataTableSoftPtr,
		         LocalLevelsDataTableSoftPtr,
		         LocalUDPPort);
}

void FZED_WidgetBuilder::ReadSession()
{
	const FString SessionConfigFilePath = ConfigFilesFolderPath / "ZVP_Session.ini";

	SessionConfigFile.Read(SessionConfigFilePath);

	const auto SectionName = TEXT("MachineSettings");

	if (SessionConfigFile.GetString(SectionName, TEXT("MachineName"), SessionConfig.ZED_MachineName) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load [%s] MachineName"), SectionName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *(SessionConfig.ZED_MachineName));
	}

	LoadSoftObjectPtr(SessionConfigFile, SectionName, TEXT("CameraInputSoftPtr") , SessionConfig.ZED_CameraInputSoftPtr);
	LoadSoftObjectPtr(SessionConfigFile, SectionName, TEXT("CameraOutputSoftPtr"), SessionConfig.ZED_CameraOutputSoftPtr);

	FString CameraTypeStr;

	if (SessionConfigFile.GetString(SectionName, TEXT("DefaultCameraType"), CameraTypeStr) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load [%s] DefaultCameraType"), SectionName);
	}
	else
	{
		// Defines what type of camera it should be at start up

		if (CameraTypeStr.Contains(TEXT("Virtual")))
		{
			SessionConfig.ZED_DefaultCameraType = EZED_CameraType::ZED_Virtual;
		}
		else if (CameraTypeStr.Contains(TEXT("OnRails")))
		{
			SessionConfig.ZED_DefaultCameraType = EZED_CameraType::ZED_OnRails;
		}
		else
		{
			SessionConfig.ZED_DefaultCameraType = EZED_CameraType::ZED_Handheld;
		}

	}

	FString CameraGroupStr;

	if (SessionConfigFile.GetString(SectionName, TEXT("DefaultCameraGroup"), CameraGroupStr) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load [%s] DefaultCameraGroup"), SectionName);
	}
	else
	{
		if (CameraGroupStr.Contains(TEXT("None")))
		{
			SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroupNone;
		}
		else if (CameraGroupStr.Contains(TEXT("Avatars")))
		{
			SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroupAvatars;
		}
		else if (CameraGroupStr.Contains(TEXT("Group")))
		{
			const bool ReplaceResult = CameraGroupStr.RemoveFromStart(TEXT("Group"));

			if (ReplaceResult && CameraGroupStr.IsNumeric())
			{
				const int32 GroupNumberStr = FCString::Atoi(*CameraGroupStr);
				switch (GroupNumberStr)
				{
				case 1: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup1; }break;
				case 2: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup2; }break;
				case 3: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup3; }break;
				case 4: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup4; }break;
				case 5: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup5; }break;
				case 6: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup6; }break;
				case 7: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup7; }break;
				case 8: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup8; }break;
				case 9: { SessionConfig.ZED_DefaultCameraGroup = EZED_CameraGroup::ZED_CamGroup9; }break;
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Wrong value for [%s] DefaultCameraGroup, should start with 'Group' and then a number! e.g. 'Group3'"), SectionName);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Wrong value for [%s] DefaultCameraGroup"), SectionName);
		}
	}
}

void FZED_WidgetBuilder::ReadProject()
{
	const FString ProjectConfigFilePath = ConfigFilesFolderPath / "ZVP_Project.ini";

	ProjectConfigFile.Read(ProjectConfigFilePath);

	const auto SectionName = TEXT("ProjectSettings");

	LoadSoftClassPtr (ProjectConfigFile, SectionName, TEXT("EventManagerSoftPtr")   , ProjectConfig.ZED_EventManagerClassSoftPtr);
	LoadSoftClassPtr (ProjectConfigFile, SectionName, TEXT("EventListenerSoftPtr")  , ProjectConfig.ZED_EventListenerClassSoftPtr);
	LoadSoftObjectPtr(ProjectConfigFile, SectionName, TEXT("SongsDataTableSoftPtr") , ProjectConfig.ZED_SongsDataTableSoftPtr);
	LoadSoftObjectPtr(ProjectConfigFile, SectionName, TEXT("LevelsDataTableSoftPtr"), ProjectConfig.ZED_LevelsDataTableSoftPtr);

	if (ProjectConfigFile.GetInt(SectionName, TEXT("UDPPort"), ProjectConfig.ZED_UDPPort) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load [%s] UDPPort"), SectionName);
	}
}
void FZED_WidgetBuilder::WriteSession(FString                      LocalConfigFilesFolderPath,
	                                  FString                      LocalMachineName          ,
	                                  UObject                    * LocalCameraInputSoftPtr   ,
	                                  UObject                    * LocalCameraOutputSoftPtr  ,
                                      FString                      LocalDefaultCameraType,
	                                  FString                      LocalDefaultCameraGroup)
{
	const FString SessionConfigFilePath = LocalConfigFilesFolderPath / "ZVP_Session.ini";
	FString CameraTypeStr;
	// Holds specific machine configuration file
	FConfigFile SConfigFile;

	TSoftObjectPtr<UMediaSource> FileCameraInputSoftPtr  = Cast<UMediaSource>(LocalCameraInputSoftPtr);
	TSoftObjectPtr<UMediaOutput> FileCameraOutputSoftPtr = Cast<UMediaOutput>(LocalCameraOutputSoftPtr);

	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	if (PF.CreateDirectoryTree(*LocalConfigFilesFolderPath) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create/ensure plugin config folder creation!"));
		return;
	}

	const auto SectionName = TEXT("MachineSettings");

	SConfigFile.SetString(SectionName, TEXT("MachineName")        , *LocalMachineName);
	SConfigFile.SetString(SectionName, TEXT("CameraInputSoftPtr") , *FileCameraInputSoftPtr.ToSoftObjectPath().ToString());
	SConfigFile.SetString(SectionName, TEXT("CameraOutputSoftPtr"), *FileCameraOutputSoftPtr.ToSoftObjectPath().ToString());
	SConfigFile.SetString(SectionName, TEXT("DefaultCameraType")  , *LocalDefaultCameraType);
	SConfigFile.SetString(SectionName, TEXT("DefaultCameraGroup") , *LocalDefaultCameraGroup);

	SConfigFile.Write(SessionConfigFilePath);
}

void FZED_WidgetBuilder::WriteProject(FString                      LocalConfigFilesFolderPath,
	                                  FString                      LocalVirtualCameraFocusType,
	                                  UObject                    * LocalEventManagerClassSoftPtr,
	                                  UObject                    * LocalEventListenerClassSoftPtr,
	                                  UObject                    * LocalSongsDataTableSoftPtr,
	                                  UObject                    * LocalLevelsDataTableSoftPtr,
	                                  int32                        LocalUDPPort)
{
	const FString ProjectConfigFilePath = LocalConfigFilesFolderPath / "ZVP_Project.ini";

	TSoftClassPtr<UObject>       FileEventManagerClassSoftPtr  = TSoftClassPtr<UObject>(LocalEventManagerClassSoftPtr);
	TSoftClassPtr<UObject>       FileEventListenerClassSoftPtr = TSoftClassPtr<UObject>(LocalEventListenerClassSoftPtr);
	TSoftObjectPtr<UDataTable>   FileSongsDataTableSoftPtr     = Cast<UDataTable>(LocalSongsDataTableSoftPtr);
	TSoftObjectPtr<UDataTable>   FileLevelsDataTableSoftPtr    = Cast<UDataTable>(LocalLevelsDataTableSoftPtr);
	
	// Holds specific machine configuration file
	FConfigFile SConfigFile;

	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	if (PF.CreateDirectoryTree(*LocalConfigFilesFolderPath) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create/ensure plugin config folder creation!"));
		return;
	}

	const auto SectionName = TEXT("ProjectSettings");

	SConfigFile.SetString(SectionName, TEXT("EventManagerSoftPtr")   , *FileEventManagerClassSoftPtr.ToSoftObjectPath().ToString());
	SConfigFile.SetString(SectionName, TEXT("EventListenerSoftPtr")  , *FileEventListenerClassSoftPtr.ToSoftObjectPath().ToString());
	SConfigFile.SetString(SectionName, TEXT("SongsDataTableSoftPtr") , *FileSongsDataTableSoftPtr.ToSoftObjectPath().ToString());
	SConfigFile.SetString(SectionName, TEXT("LevelsDataTableSoftPtr"), *FileLevelsDataTableSoftPtr.ToSoftObjectPath().ToString());
	SConfigFile.SetString(SectionName, TEXT("UDPPort")               , *FString::FromInt(LocalUDPPort));

	SConfigFile.Write(ProjectConfigFilePath);

}

void FZED_WidgetBuilder::SetCameraType(EZED_CameraType NewCameraType)
{
	if (NewCameraType != CameraType)
	{
		UE_LOG(LogTemp, Log, TEXT("Setting new Real Camera Type!"));
		CameraType = NewCameraType;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed setting new Real Camera Type, new value is the same as current one!"));
	}
}

TSharedPtr<ISinglePropertyView> FZED_WidgetBuilder::GetPropertyWidget(UObject* InObject, FName InPropertyName)
{
	FPropertyParameters param;
	
	//The property and asset editors are Singleton! So...just initialize the reference , make the job and Go!
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	//PropertyModule.CreateStructureDetailView()
	return PropertyModule.CreateSingleProperty(InObject, InPropertyName, param);
}

TSharedPtr<IStructureDetailsView> FZED_WidgetBuilder::GetStructWidget(UObject* InObject, FName InPropertyName)
{
	FViewParameters   ViewParameters;
	FStructParameters StructParameters;

	FStructProperty* StructProperty = Cast< FStructProperty >(InObject);

	TSharedPtr<FStructOnScope> ScopedStructure;
	
	ScopedStructure.Get()->Initialize(StructProperty->Struct);

	//The property and asset editors are Singleton! So...just initialize the reference , make the job and Go!
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//PropertyModule.CreateStructureDetailView()
	return PropertyModule.CreateStructureDetailView(ViewParameters   , 
		                                            StructParameters , 
		                                            ScopedStructure  , 
		                                            FText::FromName(InPropertyName));
}

TSharedPtr<IDetailsView> FZED_WidgetBuilder::GetDetailWidget(UObject* InObject, FName InPropertyName)
{
	FDetailParameters   ViewParameters;
	
	//The property and asset editors are Singleton! So...just initialize the reference , make the job and Go!
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//PropertyModule.CreateStructureDetailView()
	return PropertyModule.CreateDetailView(ViewParameters);
}

TSharedRef<IDetailsView> FZED_WidgetBuilder::GetRef()
{
	return pWidgetView.ToSharedRef();
}