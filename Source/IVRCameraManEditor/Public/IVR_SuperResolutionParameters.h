/************************************************************************/
/*Project              :IVR CameraMan - Unreal Plugin                   */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2021 William Wolff. All rights reserved                 */
/************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IVR_SuperResolutionParameters.generated.h"


/**
* Enumerates all possible focus point types:
*
* ZED_None:				Everything looks as sharp as possible
* ZED_Manual:			Focus point is fully controlled by the cameraman
* ZED_Automatic:		Focus point is tracked from the center of the virtual camera
* ZED_Fixed:			Uses a fixed focus point already placed in the world
*/
UENUM(BlueprintType)
enum class EIVR_OpticalFlowType : uint8
{
	IVR_Farneback		UMETA(DisplayName = "Farneback"),
	IVR_TVL1			UMETA(DisplayName = "TVL1"),
	IVR_Brox		    UMETA(DisplayName = "Brox"),
	IVR_PYRLK			UMETA(DisplayName = "PYRLK")
};

/**
 * 
 */
UCLASS()
class IVRCAMERAMANEDITOR_API UIVR_SuperResolutionParameters : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Resolution Scale")
	int32                     IVR_SuperScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Algorithm Iterations")
	int32                     IVR_SuperIterations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Temporal Area Radius")
    int32                     IVR_SuperTemporalRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Optical Flow Type")
	EIVR_OpticalFlowType      IVR_SuperOpticalFlow;

	//Important Method to collect the struct containers
	void* GetStructContainer(FName pPropertyName);
	UObject* GetStructObject(FName pPropertyName);
};
