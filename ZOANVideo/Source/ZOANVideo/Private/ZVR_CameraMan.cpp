// Fill out your copyright notice in the Description page of Project Settings.


#include "ZVR_CameraMan.h"

// Sets default values
AZVR_CameraMan::AZVR_CameraMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add static mesh component to actor
	ZVR_Camera        = CreateDefaultSubobject<UCameraComponent>(TEXT("ManCamera"));

	// Add static mesh component to actor
	ZVR_CameraCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("FrameGrabber"));

	// Add the mechanical stabilizer to actor
	ZVR_Stabilizer    = CreateDefaultSubobject<USpringArmComponent>(TEXT("FrameStabilizer"));

	// Initialize the default parameters
	ZVR_CameraManName         = FString("DefaultCameraMan");
	ZVR_Width                 = 1024;
	ZVR_Height                = 768;
	ZVR_ClearColor            = FLinearColor::Black;
	ZVR_Gamma                 = 0.0;
	ZVR_EnableStabilization   = true;
	ZVR_CameraVelocity        = 350.0f;
    ZVR_BaseTurnRate          = 35.f;
	ZVR_BaseLookUpRate        = 35.f;
	ZVR_FrameCounter          = 0;
	ZVR_RecordingState        = 2;//Initially Iddle
	ZVR_SelfRegistered        = false;
	ZVR_FPS                   = 0;
	ZVR_StabilizationArm      = 0.0f;
	ZVR_LagDistance           = 25.0f;
	ZVR_Enabled               = false;

	// Just to Guarantee a new render target at system initialization. In Most Cases this render target are deinitialized
	// before the rendering starts...
	ZVR_RenderTarget = NewObject<UTextureRenderTarget2D>();
	if (ZVR_RenderTarget)
	{
		ZVR_RenderTarget->ClearColor = ZVR_ClearColor;
		ZVR_RenderTarget->TargetGamma = ZVR_Gamma;
		ZVR_RenderTarget->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8_SRGB;
		ZVR_RenderTarget->InitAutoFormat(ZVR_Width, ZVR_Height);
	}

	//We Attach the stabilizer to the Capsule and all the cameras on the Arm.
	ZVR_Stabilizer   ->AttachTo(GetCapsuleComponent());
	ZVR_Stabilizer   ->bEnableCameraLag         = true;
	ZVR_Stabilizer   ->bEnableCameraRotationLag = true;
	ZVR_Stabilizer   ->CameraLagMaxDistance     = ZVR_LagDistance;
	ZVR_Stabilizer   ->TargetArmLength          = ZVR_StabilizationArm;
	
	//Attach the camera
	ZVR_Camera       ->AttachTo(ZVR_Stabilizer       );
	ZVR_Camera       ->SetActive(true);
	ZVR_Camera       ->bUsePawnControlRotation = true;

	//Attach the Frame Grabber
	ZVR_CameraCapture->AttachTo(ZVR_Stabilizer       );
	ZVR_CameraCapture->bCaptureOnMovement = true;
	ZVR_CameraCapture->SetRelativeRotation(ZVR_Camera->GetRelativeRotation());
	ZVR_CameraCapture->TextureTarget = ZVR_RenderTarget;

	//Setup Character Initial Values
	GetCharacterMovement()->MaxWalkSpeed    = ZVR_CameraVelocity;
	
}

// Called when the game starts or when spawned
void AZVR_CameraMan::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AZVR_CameraMan::CaptureFrame()
{
	// We need a rendertarget to get the frames , so here we guarantee we have one (The User dont need create one!)
	if ((!ZVR_CameraCapture->IsValidLowLevel()) || (!ZVR_RenderTarget->IsValidLowLevel()))
	{
		ZVR_RenderTarget = NewObject<UTextureRenderTarget2D>();
		if (ZVR_RenderTarget)
		{
			ZVR_RenderTarget->ClearColor = ZVR_ClearColor;
			ZVR_RenderTarget->TargetGamma = ZVR_Gamma;
			ZVR_RenderTarget->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8_SRGB;
			ZVR_RenderTarget->InitAutoFormat(ZVR_Width, ZVR_Height);
		}

		ZVR_CameraCapture->TextureTarget = ZVR_RenderTarget;
	}

	//We attach the Rendertarget here to guarantee a Dinamic Texture Too...This avoid the Texture streaming invalidate The texture.
	ZVR_CameraCapture->TextureTarget = ZVR_RenderTarget;

	//This is Critical!
	//Since we are getting a GameThread Resource everything we do after it must be done in another Thread, so be careful to develop
	//Thread safe routines to threat the frames.
	FRenderTarget* RenderTarget = ZVR_CameraCapture->TextureTarget->GameThread_GetRenderTargetResource();
	if (RenderTarget == nullptr)
	{
		return false;
	}

	TArray<FColor> RawPixels;

	// Format not supported - use PF_B8G8R8A8.
	if (ZVR_CameraCapture->TextureTarget->GetFormat() != PF_B8G8R8A8)
	{
		return false;
	}

	//The raw pixels of the final frame recording
	if (!RenderTarget->ReadPixels(RawPixels))
	{
		return false;
	}

	//Here you put your Thread safe code, ok?
	UZVR_FunctionLibrary::ZVR_AsyncRecordFrame(ZVR_CameraManName, ZVR_FrameCounter, RawPixels, ZVR_Width, ZVR_Height, ZVR_ClearColor.ToFColor(false));
	
	//Increase the FrameCounter
	ZVR_FrameCounter++;

	//huhuuuu!
	return true;

}


// Called every frame
void AZVR_CameraMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ZVR_FPS = (1.0 / DeltaTime);

	if (!ZVR_SelfRegistered)
	{
		ZVR_CameraID.ZVR_CameraName   = ZVR_CameraManName;
		ZVR_CameraID.ZVR_IsStabilized = ZVR_EnableStabilization;
		ZVR_CameraID.ZVR_IsEnabled    = ZVR_Enabled;
		ZVR_CameraID.ZVR_FPS          = ZVR_FPS;
		
		UZVR_FunctionLibrary::ZVR_AddCamera(ZVR_CameraID);

		ZVR_SelfRegistered = true;
	}

	//Mantain the base data updated with the Master! :)
	ZVR_CameraID.ZVR_CameraName   = ZVR_CameraManName;
	ZVR_CameraID.ZVR_IsStabilized = ZVR_EnableStabilization;
	ZVR_CameraID.ZVR_IsEnabled    = ZVR_Enabled;
	ZVR_CameraID.ZVR_FPS          = ZVR_FPS;
	UZVR_FunctionLibrary::ZVR_UpdCamera(ZVR_CameraID);

	ZVR_RecordingState = UZVR_FunctionLibrary::ZVR_CheckRecordingState();
	switch (ZVR_RecordingState)
	{
	case 0:	//Start Recording
	{
		//We Enable the Camera
		ZVR_Enabled = true;
		
		FZVR_CameraFrame Frame;

		Frame.ZVR_CameraName = ZVR_CameraManName;
		Frame.ZVR_FrameFPS = ZVR_FPS;
		Frame.ZVR_Position = GetActorLocation();
		Frame.ZVR_Rotation = GetActorRotation().Vector();
		Frame.ZVR_Scale = GetActorScale();

		//Collect the Historical data of the Recording(This will be usefull for Post-Recording Purposes)
		ZVR_CameraID.ZVR_Frames.Add(Frame);

		//Effectively capture a rendered frame and asyncronously record the frame at Hard Drive.
		CaptureFrame();
	}break;
	case 1: //Stop Recording
	{
		//The manager will take care to change the transition in the next checking...
		if (ZVR_Enabled)
		{
			//Since the recording Stop we give to the Manager all Collected Frames and CleanUp For the next Section
			UZVR_FunctionLibrary::ZVR_UpdCameraFrames(ZVR_CameraID);
			//Reset the Counter!
			ZVR_FrameCounter = 0;
			//We Disable the Camera
			ZVR_Enabled = false;
		}
	}break;
	case 2: //Iddle
	{
		if (!ZVR_EnableStabilization)
		{
			ZVR_Stabilizer->bEnableCameraLag = false;
			ZVR_Stabilizer->bEnableCameraRotationLag = false;
			ZVR_Stabilizer->CameraLagMaxDistance = 0.0f;
			ZVR_Stabilizer->TargetArmLength = 0.0f;
			ZVR_Stabilizer->CameraLagSpeed = 0.0f;
			ZVR_Stabilizer->CameraRotationLagSpeed = 0.0f;
		}
		else
		{
			ZVR_Stabilizer->bEnableCameraLag = true;
			ZVR_Stabilizer->bEnableCameraRotationLag = true;
			ZVR_Stabilizer->CameraLagMaxDistance = ZVR_LagDistance;
			ZVR_Stabilizer->TargetArmLength = ZVR_StabilizationArm;
			ZVR_Stabilizer->CameraLagSpeed = ZVR_StabilizationRate;
			ZVR_Stabilizer->CameraRotationLagSpeed = ZVR_StabilizationRate;
		}
	}break;
	}
}

// Called to bind functionality to input
void AZVR_CameraMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveCameraManFoward"    , this, &AZVR_CameraMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveCameraManRight"     , this, &AZVR_CameraMan::MoveRight);
	PlayerInputComponent->BindAxis("MoveCameraManTurnRate"  , this, &AZVR_CameraMan::TurnAtRate);
	PlayerInputComponent->BindAxis("MoveCameraManLookUpRate", this, &AZVR_CameraMan::LookUpAtRate);
	
	PlayerInputComponent->BindAction("StartRecord"  , IE_Pressed, this, &AZVR_CameraMan::StartRecord);
	PlayerInputComponent->BindAction("StopRecord"   , IE_Pressed, this, &AZVR_CameraMan::StopRecord);
	PlayerInputComponent->BindAction("CompileVideos", IE_Pressed, this, &AZVR_CameraMan::CompileVideo);
}

// Called to bind functionality to input
void AZVR_CameraMan::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

// Called to bind functionality to input
void AZVR_CameraMan::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

// Called to bind functionality to input
void AZVR_CameraMan::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * ZVR_BaseTurnRate * GetWorld()->GetDeltaSeconds());
	ZVR_CameraCapture->SetRelativeRotation(ZVR_Camera->GetRelativeRotation());
}

// Called to bind functionality to input
void AZVR_CameraMan::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * ZVR_BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	ZVR_CameraCapture->SetRelativeRotation(ZVR_Camera->GetRelativeRotation());
}

void AZVR_CameraMan::StartRecord()
{
	UZVR_FunctionLibrary::ZVR_SingleShotRecordingMessage(0);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Recording Start!"));
}
void AZVR_CameraMan::StopRecord()
{
	//As a Commander Camera we give a SingleShot Stop Message
	UZVR_FunctionLibrary::ZVR_SingleShotRecordingMessage(1);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Recording Stop!"));
}
void AZVR_CameraMan::CompileVideo()
{
	UZVR_FunctionLibrary::ZVR_SingleShotVideoRecording();
}

