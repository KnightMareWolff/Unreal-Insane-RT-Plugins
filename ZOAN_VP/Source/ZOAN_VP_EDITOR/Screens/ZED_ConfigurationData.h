// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MediaSource.h"
#include "MediaOutput.h"
#include "ZED_ConfigurationData.generated.h"

/**
* Enumerates all possible focus point types:
*
* ZED_None:				Everything looks as sharp as possible
* ZED_Manual:			Focus point is fully controlled by the cameraman
* ZED_Automatic:		Focus point is tracked from the center of the virtual camera
* ZED_Fixed:			Uses a fixed focus point already placed in the world
*/
UENUM(BlueprintType)
enum class EZED_VirtualCameraFocusType : uint8
{
	ZED_None			UMETA(DisplayName = "All Sharp"),
	ZED_Manual			UMETA(DisplayName = "Fully Manual"),
	ZED_Automatic		UMETA(DisplayName = "Automatic"),
	ZED_Fixed			UMETA(DisplayName = "Fixed Point Actor")
};

/**
* Enumerates all possible camera types:
*
* ZED_Virtual:		Cameraman can control the camera using Vive controllers, camera feed is shown on screens in the scene
* ZED_Handheld:		Movable camera is rigged and tracked
* ZED_OnRails:		Camera moves automatically, usually by a Level Sequence
*/
UENUM(BlueprintType)
enum class EZED_CameraType : uint8
{
	ZED_Virtual		UMETA(DisplayName = "Virtual"),
	ZED_Handheld	UMETA(DisplayName = "Handheld"),
	ZED_OnRails		UMETA(DisplayName = "On Rails")
};

/**
* Enumerates all possible camera groups:
*
* ZED_CamGroupNone:		Belongs to no group (default)
* ZED_CamGroup*:		Predefined group
* ZED_CamGroupAvatars:	Cameras designed to aim to avatars
*/
UENUM(BlueprintType)
enum class EZED_CameraGroup : uint8
{
	ZED_CamGroupNone		UMETA(DisplayName = "None"),
	ZED_CamGroup1			UMETA(DisplayName = "Group 1"),
	ZED_CamGroup2			UMETA(DisplayName = "Group 2"),
	ZED_CamGroup3			UMETA(DisplayName = "Group 3"),
	ZED_CamGroup4			UMETA(DisplayName = "Group 4"),
	ZED_CamGroup5			UMETA(DisplayName = "Group 5"),
	ZED_CamGroup6			UMETA(DisplayName = "Group 6"),
	ZED_CamGroup7			UMETA(DisplayName = "Group 7"),
	ZED_CamGroup8			UMETA(DisplayName = "Group 8"),
	ZED_CamGroup9			UMETA(DisplayName = "Group 9"),
	ZED_CamGroupAvatars		UMETA(DisplayName = "Avatars")
};

/**
* Holds project configuration, it's loaded from ini file and
* accessed from the toolbar in Unreal Editor.
*/
USTRUCT(BlueprintType)
struct FZED_ProjectConfig
{
	GENERATED_BODY()

	// Soft reference to event manager class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "UDP Event Manager")
	TSoftClassPtr<UObject> ZED_EventManagerClassSoftPtr;

	// Soft reference to event listener class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "UDP Event Listener")
	TSoftClassPtr<UObject> ZED_EventListenerClassSoftPtr;

	// Soft reference to a song list
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Songs List")
	TSoftObjectPtr<UDataTable> ZED_SongsDataTableSoftPtr;

	// Soft reference to a level name list
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Level List")
	TSoftObjectPtr<UDataTable> ZED_LevelsDataTableSoftPtr;

	// Holds UDP port for event listening
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "UDP Listening Port")
	int32 ZED_UDPPort;
};

/**
* Holds specific machine session configuration, it's loaded from
* ini file and edited manually by the user using any notepad app.
*/
USTRUCT(BlueprintType)
struct FZED_SessionConfig
{
	GENERATED_BODY()

	// Holds local machine name
	UPROPERTY(EditAnywhere, BlueprintReadWrite , DisplayName = "Machine Name")
	FString ZED_MachineName;

	// Soft reference to a camera media input asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Media Input")
	TSoftObjectPtr<UMediaSource> ZED_CameraInputSoftPtr;

	// Holds local machine startup camera group
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Default Camera Group")
	EZED_CameraGroup ZED_DefaultCameraGroup;

	// Soft reference to a camera media output asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Media Output")
	TSoftObjectPtr<UMediaOutput> ZED_CameraOutputSoftPtr;

	// Holds local machine startup real camera type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Default Camera Type")
	EZED_CameraType ZED_DefaultCameraType;

};

UCLASS()
class ZOAN_VP_EDITOR_API AZED_ConfigurationData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZED_ConfigurationData();

	// Path for this plugin configuration files
	UPROPERTY(EditAnywhere, Category = "Global Settings")
	FString ZED_ConfigFilesFolderPath;

	// Session configuration (specific machine values)
	UPROPERTY(EditAnywhere, Category = "Machine Settings")
	FZED_SessionConfig ZED_SessionConfig;

	// Project configuration (doesn't change between machines)
	UPROPERTY(EditAnywhere, Category = "Project Settings")
	FZED_ProjectConfig ZED_ProjectConfig;

	// What type of camera is being used at the moment
	UPROPERTY(EditAnywhere, Category = "Global Settings")
	EZED_CameraType ZED_CameraType;

	// Tells what type of focus method virtual cameras should process
	UPROPERTY(EditAnywhere, Category = "Global Settings")
	EZED_VirtualCameraFocusType ZED_VirtualCameraFocusType;

	//Important Method to collect the struct containers
	void    * GetStructContainer(FName pPropertyName);
	UObject * GetStructObject   (FName pPropertyName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
