/************************************************************************/
/*Project              :IVR CameraMan - Unreal Plugin                   */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2021 William Wolff. All rights reserved                 */
/************************************************************************/
#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
//Texture2D
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Engine/Texture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "DDSLoader.h"
#include "AudioCaptureComponent.h"

#include "AudioMixerBlueprintLibrary.h"
#include "IVR_FunctionLibrary.h" //The Function Library already have the OpenCV Includes

//Macros Definitions
#include "IVR_CameraMan.generated.h"

UCLASS()
class IVRCAMERAMAN_API AIVR_CameraMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIVR_CameraMan();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward (float Val );
	void MoveRight   (float Val );
	void TurnAtRate  (float Rate);
	void LookUpAtRate(float Rate);
	void StartRecord (          );
	void StopRecord  (          );
	void CompileVideo(          );
	bool CaptureFrame(          );
	bool LoadDefault (          );


	UFUNCTION(Category = "CameraMan|Video|Functions ", BlueprintCallable)
	void CameraGrabbSpawner();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	int32                     IVR_Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	int32                     IVR_Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	FLinearColor              IVR_ClearColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	float                     IVR_Gamma;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	bool                      IVR_EnableStabilization;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	float                     IVR_StabilizationRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	bool                      IVR_EnableTurboRecording;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	float                     IVR_TurboRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	float                     IVR_StabilizationArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	float                     IVR_LagDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	FString                   IVR_CameraManName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "CameraMan|Video|Parameters")
	float                     IVR_CameraVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Parameters")
	float                     IVR_BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Parameters")
	float                     IVR_BaseLookUpRate;
	
	
	int32                     IVR_FrameCounter   ;
	FDateTime                 IVR_RecordingStart ;
	FDateTime                 IVR_RecordingFinish;
	float                     IVR_FPS            ;
	FString                   IVR_RecordingPath  ;
	FConfigFile               IVR_ProjectConfigFile;
	uint                      IVR_RecordingState ;
	bool                      IVR_SelfRegistered ;
	bool                      IVR_Enabled        ;
	FIVR_CameraStruct         IVR_CameraID       ;
	FCriticalSection          IVR_CriticalSection;
	UTextureRenderTarget2D  * IVR_RenderTarget   ;
	USceneCaptureComponent2D* IVR_CameraCapture  ;
	UAudioCaptureComponent  * IVR_SoundCapture   ;
	UCameraComponent        * IVR_Camera         ;
	USpringArmComponent     * IVR_Stabilizer     ;

	//If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load).
	TQueue<FIVR_CameraMessage, EQueueMode::Mpsc> IVR_MessageQueue;
	TArray<AIVR_CameraMan*>    IVR_ChildCams;

};
