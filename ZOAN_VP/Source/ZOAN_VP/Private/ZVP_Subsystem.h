// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZOAN_VP.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/ObjectMacros.h"
#include "MediaSource.h"
#include "MediaOutput.h"

#include "ZVP_Subsystem.generated.h"

#pragma region Data Types

/**
* Enumerates all possible focus point types:
*
* ZVP_None:				Everything looks as sharp as possible
* ZVP_Manual:			Focus point is fully controlled by the cameraman
* ZVP_Automatic:		Focus point is tracked from the center of the virtual camera
* ZVP_Fixed:			Uses a fixed focus point already placed in the world
*/
UENUM(BlueprintType)
enum class EZVP_VirtualCameraFocusType : uint8
{
	ZVP_None			UMETA(DisplayName = "All Sharp"),
    ZVP_Manual			UMETA(DisplayName = "Fully Manual"),
	ZVP_Automatic		UMETA(DisplayName = "Automatic"),
	ZVP_Fixed			UMETA(DisplayName = "Fixed Point Actor")
};

/**
* Enumerates all possible camera types:
*
* ZVP_Virtual:		Cameraman can control the camera using Vive controllers, camera feed is shown on screens in the scene
* ZVP_Handheld:		Movable camera is rigged and tracked
* ZVP_OnRails:		Camera moves automatically, usually by a Level Sequence
*/
UENUM(BlueprintType)
enum class EZVP_CameraType : uint8
{
	ZVP_Virtual		UMETA(DisplayName = "Virtual"),
	ZVP_Handheld	UMETA(DisplayName = "Handheld"),
	ZVP_OnRails		UMETA(DisplayName = "On Rails")
};

/**
* Enumerates all possible camera groups:
*
* ZVP_CamGroupNone:		Belongs to no group (default)
* ZVP_CamGroup*:		Predefined group
* ZVP_CamGroupAvatars:	Cameras designed to aim to avatars
*/
UENUM(BlueprintType)
enum class EZVP_CameraGroup : uint8
{
	ZVP_CamGroupNone		UMETA(DisplayName = "None"),
	ZVP_CamGroup1			UMETA(DisplayName = "Group 1"),
	ZVP_CamGroup2			UMETA(DisplayName = "Group 2"),
	ZVP_CamGroup3			UMETA(DisplayName = "Group 3"),
	ZVP_CamGroup4			UMETA(DisplayName = "Group 4"),
	ZVP_CamGroup5			UMETA(DisplayName = "Group 5"),
	ZVP_CamGroup6			UMETA(DisplayName = "Group 6"),
	ZVP_CamGroup7			UMETA(DisplayName = "Group 7"),
	ZVP_CamGroup8			UMETA(DisplayName = "Group 8"),
	ZVP_CamGroup9			UMETA(DisplayName = "Group 9"),
	ZVP_CamGroupAvatars		UMETA(DisplayName = "Avatars")
};

/**
* Holds project configuration, it's loaded from ini file and
* accessed from the toolbar in Unreal Editor.
*/
USTRUCT(BlueprintType)
struct FZVP_ProjectConfig
{
	GENERATED_BODY()

	// Soft reference to event manager class
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftClassPtr<UObject> EventManagerClassSoftPtr;

	// Soft reference to event listener class
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftClassPtr<UObject> EventListenerClassSoftPtr;
	
	// Soft reference to a song list
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> SongsDataTableSoftPtr;

	// Soft reference to a level name list
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UDataTable> LevelsDataTableSoftPtr;

	// Holds UDP port for event listening
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UDPPort;
};

/**
* Holds specific machine session configuration, it's loaded from
* ini file and edited manually by the user using any notepad app.
*/
USTRUCT(BlueprintType)
struct FZVP_SessionConfig
{
	GENERATED_BODY()

	// Holds local machine name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MachineName;

	// Soft reference to a camera media input asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UMediaSource> CameraInputSoftPtr;

	// Soft reference to a camera media output asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UMediaOutput> CameraOutputSoftPtr;

	// Holds local machine startup camera type
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EZVP_CameraType DefaultCameraType;

	// Holds local machine startup camera group
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EZVP_CameraGroup DefaultCameraGroup;
};

#pragma endregion

// Broadcast when changing current camera type  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FZVP_OnCameraTypeChangedEvent, EZVP_CameraType, CameraType);
// Broadcast when changing current virtual camera focus type
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FZVP_OnVirtualCameraFocusTypeChangedEvent, EZVP_VirtualCameraFocusType, VirtualCameraFocusType);
// Broadcast when changing camera group
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FZVP_OnCameraGroupChangedEvent, EZVP_CameraGroup, CameraGroup);

/**
 * Holds important information for ZOAN's Virtual Production plugin
 */
UCLASS()
class UZVP_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	// Path for this plugin configuration files
	FString ConfigFilesFolderPath;
	
	// Holds specific machine configuration file
	FConfigFile SessionConfigFile;

	// Session configuration (specific machine values)
	FZVP_SessionConfig SessionConfig;

	// Holds project configuration file
	FConfigFile ProjectConfigFile;

	// Project configuration (doesn't change between machines)
	FZVP_ProjectConfig ProjectConfig;
	
	// What type of camera is being used at the moment
    EZVP_CameraType CameraType;

	// Tells what type of focus method virtual cameras should process
	EZVP_VirtualCameraFocusType VirtualCameraFocusType;

	// What camera group is being used at the moment
	EZVP_CameraGroup CameraGroup;
	
public:

	// Triggered when starting the application
    void Initialize(FSubsystemCollectionBase& Collection) override;

	// Ensures that plugin configuration folder exists
	bool EnsurePluginConfigFolder();

	// Loads session configuration (machine specific)
	void LoadSessionConfig();

	// Loads default camera group used during begin play
	void LoadDefaultCameraGroup(const TCHAR* SectionName);

	// Loads the default camera type used during begin play
	void LoadDefaultCameraType(const TCHAR* SectionName);

	// Loads local machine names
	void LoadMachineName(const TCHAR* SectionName);

	// Loads soft pointer to a object
	template<typename T>
	void LoadSoftObjectPtr(const FConfigFile& ConfigFile, const TCHAR* SectionName, const TCHAR* VariableName, TSoftObjectPtr<T>& SoftObjectPtr)
	{
		FString ObjectPath;
    
		if (ConfigFile.GetString(SectionName, VariableName, ObjectPath))
		{
			SoftObjectPtr = FSoftObjectPath(ObjectPath);
			UE_LOG(ZVPLog, Log, TEXT("[%s] %s : %s"), SectionName, VariableName, *ObjectPath);
		}
		else
		{
			UE_LOG(ZVPLog, Error, TEXT("Could not load [%s] %s"), SectionName, VariableName);
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
			UE_LOG(ZVPLog, Log, TEXT("[%s] %s : %s"), SectionName, VariableName, *ObjectPath);
		}
		else
		{
			UE_LOG(ZVPLog, Error, TEXT("Could not load [%s] %s"), SectionName, VariableName);
		}
	}
	
	// Loads project configuration (the same for all machines)
	void LoadProjectConfig();

	// Returns session configuration (machine specific)
	UFUNCTION(BlueprintCallable, Category = "ZOAN|VP")
	const FZVP_SessionConfig& GetSessionConfig() const;

	// Returns project configuration (the same for all machines)
	UFUNCTION(BlueprintCallable, Category = "ZOAN|VP")
	const FZVP_ProjectConfig& GetProjectConfig() const;

	// Called when changing internal camera type
	UPROPERTY(BlueprintAssignable, Category = "ZOAN|VP")
	FZVP_OnCameraTypeChangedEvent OnCameraTypeChanged;

	// Returns camera type being used at the moment 
	UFUNCTION(BlueprintCallable, Category = "ZOAN|VP")
	EZVP_CameraType GetCameraType() const;

	// Setter for camera type
	UFUNCTION(BlueprintCallable, Category = "ZOAN|VP")
	void SetCameraType(EZVP_CameraType NewCameraType);

	// Called when changing internal virtual camera focus type
	UPROPERTY(BlueprintAssignable, Category = "ZOAN|VP")
    FZVP_OnVirtualCameraFocusTypeChangedEvent OnVirtualCameraFocusTypeChanged;

	// Returns current camera type
	UFUNCTION(BlueprintCallable, Category = "ZOAN|VP")
	EZVP_VirtualCameraFocusType GetVirtualCameraFocusType() const;

	// Setter for camera focus type
	UFUNCTION(BlueprintCallable, Category = "ZOAN|VP")
	void SetVirtualCameraFocusType(EZVP_VirtualCameraFocusType NewVirtualCameraFocusType);

	// Called when changing camera group
	UPROPERTY(BlueprintAssignable, Category = "ZOAN|VP")
	FZVP_OnCameraGroupChangedEvent OnCameraGroupChanged;

	// Returns current camera group
	UFUNCTION(BlueprintCallable, Category = "ZOAN|VP")
	EZVP_CameraGroup GetCameraGroup() const;

	// Setter for camera group
	UFUNCTION(BlueprintCallable, Category = "ZOAN|VP")
	void SetCameraGroup(EZVP_CameraGroup NewCameraGroup);
	
};
