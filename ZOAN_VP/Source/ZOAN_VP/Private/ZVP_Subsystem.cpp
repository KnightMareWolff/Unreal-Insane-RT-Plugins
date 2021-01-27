// Fill out your copyright notice in the Description page of Project Settings.


#include "ZVP_Subsystem.h"

#include "Misc/ConfigCacheIni.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "EngineUtils.h"
//#include "MediaOutput.h"


void UZVP_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    // Plugin config folder location
    ConfigFilesFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / "Config" / "ZOAN_VP");
    
    // Creating config folder if needed
    if (EnsurePluginConfigFolder() == false)
    {
        UE_LOG(ZVPLog, Error, TEXT("Could not ensure that plugin configuration folder exists! Aborting initialization..."));
        return;
    }
    
    // =============== Loading ZVP_Session.ini file
    
    LoadSessionConfig();

    // =============== Loading ZVP_Project.ini file
    
    LoadProjectConfig();
    
}

bool UZVP_Subsystem::EnsurePluginConfigFolder()
{
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

    if (PF.CreateDirectoryTree(*ConfigFilesFolderPath) == false)
    {
        UE_LOG(ZVPLog, Error, TEXT("Could not create/ensure plugin config folder creation!"));
        return false;
    }
    return true;
}

void UZVP_Subsystem::LoadSessionConfig()
{
    const FString SessionConfigFilePath = ConfigFilesFolderPath / "ZVP_Session.ini";
    SessionConfigFile.Read(SessionConfigFilePath);
    const TCHAR* SectionName = TEXT("MachineSettings");
    
    LoadMachineName(SectionName);
    LoadSoftObjectPtr(SessionConfigFile, SectionName, TEXT("CameraInputSoftPtr"), SessionConfig.CameraInputSoftPtr);
    LoadSoftObjectPtr(SessionConfigFile, SectionName, TEXT("CameraOutputSoftPtr"), SessionConfig.CameraOutputSoftPtr);
    LoadDefaultCameraType(SectionName);
    LoadDefaultCameraGroup(SectionName);

}

void UZVP_Subsystem::LoadDefaultCameraGroup(const TCHAR* SectionName)
{
	FString CameraGroupStr;

	if (SessionConfigFile.GetString(SectionName, TEXT("DefaultCameraGroup"), CameraGroupStr) == false)
	{
		UE_LOG(ZVPLog, Error, TEXT("Could not load [%s] DefaultCameraGroup"), SectionName);
	}
	else
	{
		if (CameraGroupStr.Contains(TEXT("None")))
		{
			SetCameraGroup(EZVP_CameraGroup::ZVP_CamGroupNone);
		}
		else if (CameraGroupStr.Contains(TEXT("Avatars")))
		{
			SetCameraGroup(EZVP_CameraGroup::ZVP_CamGroupAvatars);
		}
		else if (CameraGroupStr.Contains(TEXT("Group")))
		{
			const bool ReplaceResult = CameraGroupStr.RemoveFromStart(TEXT("Group"));

			if (ReplaceResult && CameraGroupStr.IsNumeric())
			{
				const int32 GroupNumberStr = FCString::Atoi(*CameraGroupStr);
				SetCameraGroup(static_cast<EZVP_CameraGroup>(GroupNumberStr));
			}
			else
			{
				UE_LOG(ZVPLog, Error, TEXT("Wrong value for [%s] DefaultCameraGroup, should start with 'Group' and then a number! e.g. 'Group3'"), SectionName);
			}
		}
		else
		{
			UE_LOG(ZVPLog, Error, TEXT("Wrong value for [%s] DefaultCameraGroup"), SectionName);
		}
	}
}

void UZVP_Subsystem::LoadDefaultCameraType(const TCHAR* SectionName)
{
	FString CameraTypeStr;

	if (SessionConfigFile.GetString(SectionName, TEXT("DefaultCameraType"), CameraTypeStr) == false)
	{
		UE_LOG(ZVPLog, Error, TEXT("Could not load [%s] DefaultCameraType"), SectionName);
	}
	else
	{
		// Defines what type of camera it should be at start up

		if (CameraTypeStr.Contains(TEXT("Virtual")))
		{
			SetCameraType(EZVP_CameraType::ZVP_Virtual);
		}
		else if (CameraTypeStr.Contains(TEXT("OnRails")))
		{
			SetCameraType(EZVP_CameraType::ZVP_OnRails);
		}
		else
		{
			SetCameraType(EZVP_CameraType::ZVP_Handheld);
		}

	}
}

void UZVP_Subsystem::LoadMachineName(const TCHAR* SectionName)
{
	if (SessionConfigFile.GetString(SectionName, TEXT("MachineName"), SessionConfig.MachineName) == false)
	{
		UE_LOG(ZVPLog, Error, TEXT("Could not load [%s] MachineName"), SectionName);
	}
	else
	{
		UE_LOG(ZVPLog, Log, TEXT("%s"), *(SessionConfig.MachineName));
	}
}

void UZVP_Subsystem::LoadProjectConfig()
{
    const FString ProjectConfigFilePath = ConfigFilesFolderPath / "ZVP_Project.ini";
    
    ProjectConfigFile.Read(ProjectConfigFilePath);

    const auto SectionName = TEXT("ProjectSettings");

    LoadSoftClassPtr(ProjectConfigFile, SectionName, TEXT("EventManagerSoftPtr"), ProjectConfig.EventManagerClassSoftPtr);
    LoadSoftClassPtr(ProjectConfigFile, SectionName, TEXT("EventListenerSoftPtr"), ProjectConfig.EventListenerClassSoftPtr);
    LoadSoftObjectPtr(ProjectConfigFile, SectionName, TEXT("SongsDataTableSoftPtr"), ProjectConfig.SongsDataTableSoftPtr);
    LoadSoftObjectPtr(ProjectConfigFile, SectionName, TEXT("LevelsDataTableSoftPtr"), ProjectConfig.LevelsDataTableSoftPtr);

    if (ProjectConfigFile.GetInt(SectionName, TEXT("UDPPort"), ProjectConfig.UDPPort) == false)
    {
        UE_LOG(ZVPLog, Error, TEXT("Could not load [%s] UDPPort"), SectionName);
    }
}

const FZVP_SessionConfig& UZVP_Subsystem::GetSessionConfig() const
{
    return SessionConfig;
}

const FZVP_ProjectConfig& UZVP_Subsystem::GetProjectConfig() const
{
    return ProjectConfig;
}

EZVP_CameraType UZVP_Subsystem::GetCameraType() const
{
    return CameraType;
}

void UZVP_Subsystem::SetCameraType(EZVP_CameraType NewCameraType)
{
    if (NewCameraType != CameraType)
    {
        UE_LOG(ZVPLog, Log, TEXT("Setting new Camera Type!"));
        CameraType = NewCameraType;
        OnCameraTypeChanged.Broadcast(CameraType);
    }
    else
    {
        UE_LOG(ZVPLog, Log, TEXT("Failed setting new Camera Type, new value is the same as current one!"));
    }
}

EZVP_VirtualCameraFocusType UZVP_Subsystem::GetVirtualCameraFocusType() const
{
    return VirtualCameraFocusType;
}

void UZVP_Subsystem::SetVirtualCameraFocusType(EZVP_VirtualCameraFocusType NewVirtualCameraFocusType)
{
    if (NewVirtualCameraFocusType != VirtualCameraFocusType)
    {
        UE_LOG(ZVPLog, Log, TEXT("Setting new Virtual Camera Focus Type!"));
        VirtualCameraFocusType = NewVirtualCameraFocusType;
        OnVirtualCameraFocusTypeChanged.Broadcast(VirtualCameraFocusType);
    }
    else
    {
        UE_LOG(ZVPLog, Log, TEXT("Failed setting new Virtual Camera Focus Type, new value is the same as current one!"));
    }
}

EZVP_CameraGroup UZVP_Subsystem::GetCameraGroup() const
{
	return CameraGroup;
}

void UZVP_Subsystem::SetCameraGroup(EZVP_CameraGroup NewCameraGroup)
{
	if (NewCameraGroup != CameraGroup)
	{
		UE_LOG(ZVPLog, Log, TEXT("Setting new Camera Group!"));
		CameraGroup = NewCameraGroup;
		OnCameraGroupChanged.Broadcast(CameraGroup);
	}
	else
	{
		UE_LOG(ZVPLog, Log, TEXT("Failed setting new Camera Group, new value is the same as current one!"));
	}
}
