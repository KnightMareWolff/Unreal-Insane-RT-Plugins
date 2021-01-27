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
#pragma once

#include "Engine.h"
#include "Screens/ZED_ObjectData.h"
#include "ZED_PropertyCustomizer.h"
#include "PropertyEditorModule.h"
#include "Toolkits/AssetEditorManager.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "IPropertyTypeCustomization.h"
#include "ISinglePropertyView.h"

class FPropertyParameters : public FSinglePropertyParams
{
public:
	FPropertyParameters()
	{
		
	}
};

class FViewParameters : public FDetailsViewArgs
{
public:
	FViewParameters(){}

};

class FStructParameters : public FStructureDetailsViewArgs
{
public:
	FStructParameters(){}
};

class FDetailParameters : public FDetailsViewArgs
{
public:
	FDetailParameters() {}
};

class FZED_WidgetBuilder 
{
public:
	// Sets default values for this actor's properties
	FZED_WidgetBuilder();
  
	TSharedRef<IDetailsView>          GetRef();
	
	TSharedPtr<ISinglePropertyView>   GetPropertyWidget(UObject* InObject, FName InPropertyName);
	TSharedPtr<IStructureDetailsView> GetStructWidget  (UObject* InObject, FName InPropertyName);
	TSharedPtr<IDetailsView>          GetDetailWidget  (UObject* InObject, FName InPropertyName);

	// Loads soft pointer to a object
	template<typename T>
	void LoadSoftObjectPtr(const FConfigFile& ConfigFile, const TCHAR* SectionName, const TCHAR* VariableName, TSoftObjectPtr<T>& SoftObjectPtr)
	{
		FString ObjectPath;

		if (ConfigFile.GetString(SectionName, VariableName, ObjectPath))
		{
			SoftObjectPtr = FSoftObjectPath(ObjectPath);
			UE_LOG(LogTemp, Log, TEXT("[%s] %s : %s"), SectionName, VariableName, *ObjectPath);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] %s"), SectionName, VariableName);
		}
	}

	// Loads soft pointer to a class
	template<typename T>
	void LoadSoftClassPtr(const FConfigFile& ConfigFile, const TCHAR* SectionName, const TCHAR* VariableName, TSoftClassPtr<T>& SoftClassPtr)
	{
		FString ObjectPath;

		if (ConfigFile.GetString(SectionName, VariableName, ObjectPath))
		{
			SoftClassPtr = FSoftClassPath(ObjectPath);
			UE_LOG(LogTemp, Log, TEXT("[%s] %s : %s"), SectionName, VariableName, *ObjectPath);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] %s"), SectionName, VariableName);
		}
	}

	void SetCameraType(EZED_CameraType NewCameraType);

	void ReadSession();
	void ReadProject();

	void WriteSession(FString                      LocalConfigFilesFolderPath,
		              FString                      LocalMachineName,
		              UObject                    * LocalCameraInputSoftPtr,
		              UObject                    * LocalCameraOutputSoftPtr,
		              FString                      LocalDefaultCameraType,
		              FString                      LocalDefaultCameraGroup);
	
	void WriteProject(FString                      LocalConfigFilesFolderPath    ,
		              FString                      LocalVirtualCameraFocusType   ,
		              UObject                    * LocalEventManagerClassSoftPtr,
		              UObject                    * LocalEventListenerClassSoftPtr,
		              UObject                    * LocalSongsDataTableSoftPtr,
		              UObject                    * LocalLevelsDataTableSoftPtr,
	                  int32                        LocalUDPPort                  );

	// Path for this plugin configuration files
	FString ConfigFilesFolderPath;

	// Holds specific machine configuration file
	FConfigFile SessionConfigFile;

	// Session configuration (specific machine values)
	FZED_SessionConfig SessionConfig;

	// Holds project configuration file
	FConfigFile ProjectConfigFile;

	// Project configuration (doesn't change between machines)
	FZED_ProjectConfig ProjectConfig;

	// What type of camera is being used at the moment
	EZED_CameraType CameraType;

	// Tells what type of focus method virtual cameras should process
	EZED_VirtualCameraFocusType VirtualCameraFocusType;

	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);

	static TSharedPtr<IDetailsView>  pWidgetView;

	UZED_ObjectData* ZED_ConfigurationDataSource;

};

