// Fill out your copyright notice in the Description page of Project Settings.

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

#include "ZVR_FunctionLibrary.h" //The Function Library already have the OpenCV Includes

//Macros Definitions
#include "ZVR_CameraMan.generated.h"

UCLASS()
class ZOANVIDEO_API AZVR_CameraMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZVR_CameraMan();

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

	bool CaptureFrame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	int32                     ZVR_Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	int32                     ZVR_Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	FLinearColor              ZVR_ClearColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float                     ZVR_Gamma;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	bool                      ZVR_EnableStabilization;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float                     ZVR_StabilizationRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float                     ZVR_StabilizationArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float                     ZVR_LagDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	FString                   ZVR_CameraManName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float                     ZVR_CameraVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float                     ZVR_BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float                     ZVR_BaseLookUpRate;
	
	
	int32                     ZVR_FrameCounter   ;
	FDateTime                 ZVR_RecordingStart ;
	FDateTime                 ZVR_RecordingFinish;
	float                     ZVR_FPS            ;
	FString                   ZVR_RecordingPath  ;
	uint                      ZVR_RecordingState ;
	bool                      ZVR_SelfRegistered ;
	bool                      ZVR_Enabled        ;
	FZVR_CameraStruct         ZVR_CameraID       ;
	FCriticalSection          ZVR_CriticalSection;
	UTextureRenderTarget2D  * ZVR_RenderTarget   ;
	USceneCaptureComponent2D* ZVR_CameraCapture  ;
	UCameraComponent        * ZVR_Camera         ;
	USpringArmComponent     * ZVR_Stabilizer     ;

	//If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load).
	TQueue<FZVR_CameraMessage, EQueueMode::Mpsc> ZVR_MessageQueue;

};
