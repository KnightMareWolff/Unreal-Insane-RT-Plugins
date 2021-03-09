/************************************************************************/
/*Project              :IVR CameraMan - Unreal Plugin                   */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2021 William Wolff. All rights reserved                 */
/************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IVR_DefaultCameraParameters.generated.h"

/**
 * 
 */
UCLASS()
class IVRCAMERAMANEDITOR_API UIVR_DefaultCameraParameters : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite , DisplayName ="Recording Path")
		FString                   IVR_RecordingPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Screen Width")
		int32                     IVR_Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Screen Height")
		int32                     IVR_Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Clear Color")
		FLinearColor              IVR_ClearColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Gamma")
		float                     IVR_Gamma;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Enable Turbo?")
		bool                      IVR_EnableTurboRecording;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Turbo Rate")
		float                     IVR_TurboRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Stabilization Arm Distance")
		float                     IVR_StabilizationArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Lag Distance")
		float                     IVR_LagDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Camera Name")
		FString                   IVR_CameraManName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Camera Velocity")
		float                     IVR_CameraVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Turn Rate")
		float                     IVR_BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Look Up Rate")
		float                     IVR_BaseLookUpRate;

	//Important Method to collect the struct containers
	void*    GetStructContainer(FName pPropertyName);
	UObject* GetStructObject   (FName pPropertyName);
	
};
