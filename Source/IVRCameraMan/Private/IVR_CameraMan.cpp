/************************************************************************/
/*Project              :IVR CameraMan - Unreal Plugin                   */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2021 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IVR_CameraMan.h"

// Sets default values
AIVR_CameraMan::AIVR_CameraMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add static mesh component to actor
	IVR_Camera        = CreateDefaultSubobject<UCameraComponent>(TEXT("ManCamera"));

	// Add static mesh component to actor
	IVR_CameraCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("FrameGrabber"));

	// Add the mechanical stabilizer to actor
	IVR_Stabilizer    = CreateDefaultSubobject<USpringArmComponent>(TEXT("FrameStabilizer"));
	
	// Add the audio capture component
	IVR_SoundCapture  = CreateDefaultSubobject<UAudioCaptureComponent>(TEXT("AudioCaptureDevice"));

	// Initialize the default parameters
	LoadDefault();

	//Initialize the Default Processing State
	IVR_FrameCounter          = 0;
	IVR_RecordingState        = 2;//Initially Iddle
	IVR_SelfRegistered        = false;
	IVR_FPS                   = 0;
	IVR_Enabled               = false;
	
	// Just to Guarantee a new render target at system initialization. In Most Cases this render target are deinitialized
	// before the rendering starts...
	IVR_RenderTarget = NewObject<UTextureRenderTarget2D>();
	if (IVR_RenderTarget)
	{
		IVR_RenderTarget->ClearColor = IVR_ClearColor;
		IVR_RenderTarget->TargetGamma = IVR_Gamma;
		IVR_RenderTarget->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8_SRGB;
		IVR_RenderTarget->InitAutoFormat(IVR_Width, IVR_Height);
	}

	//We Attach the stabilizer to the Capsule and all the cameras on the Arm.
	IVR_Stabilizer   ->AttachTo(GetCapsuleComponent());
	//IVR_Stabilizer   ->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	IVR_Stabilizer   ->bEnableCameraLag         = true;
	IVR_Stabilizer   ->bEnableCameraRotationLag = true;
	IVR_Stabilizer   ->CameraLagMaxDistance     = IVR_LagDistance;
	IVR_Stabilizer   ->TargetArmLength          = IVR_StabilizationArm;
	
	//Attach the camera
	IVR_Camera       ->AttachTo(IVR_Stabilizer       );
	//IVR_Camera       ->AttachToComponent(IVR_Stabilizer, FAttachmentTransformRules::SnapToTargetIncludingScale);
	IVR_Camera       ->SetActive(true);
	IVR_Camera       ->bUsePawnControlRotation = true;

	//Attach the Frame Grabber
	IVR_CameraCapture->AttachTo(IVR_Stabilizer       );
	//IVR_CameraCapture->AttachToComponent(IVR_Stabilizer, FAttachmentTransformRules::SnapToTargetIncludingScale);
	IVR_CameraCapture->bCaptureOnMovement = true;
	IVR_CameraCapture->SetRelativeRotation(IVR_Camera->GetRelativeRotation());
	IVR_CameraCapture->TextureTarget = IVR_RenderTarget;

	//Setup Character Initial Values
	GetCharacterMovement()->MaxWalkSpeed    = IVR_CameraVelocity;
	
}

// Called when the game starts or when spawned
bool AIVR_CameraMan::LoadDefault()
{
	const FString SessionConfigFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / "Config" / "IVRCameraMan" / "DefaultCameraMan.ini");
	FString tStr;

	//If the Configuration File Not Exists Load Fixed Parameters... ;)
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SessionConfigFilePath))
	{
		IVR_ProjectConfigFile.Read(SessionConfigFilePath);

		const auto SectionName = TEXT("DefaultCameraParameters");

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("RecordingPath"), IVR_RecordingPath) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] RecordingPath"), SectionName);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *(IVR_RecordingPath));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("Width"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] RecordingPath"), SectionName);
		}
		else
		{
			IVR_Width = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("Height"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] RecordingPath"), SectionName);
		}
		else
		{
			IVR_Height = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("Gamma"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] Gamma"), SectionName);
		}
		else
		{
			IVR_Gamma = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("EnableTurboRecording"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] Gamma"), SectionName);
		}
		else
		{
			IVR_EnableTurboRecording = tStr.ToBool();
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("TurboRate"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] TurboRate"), SectionName);
		}
		else
		{
			IVR_TurboRate = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}


		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("StabilizationArm"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] StabilizationArm"), SectionName);
		}
		else
		{
			IVR_StabilizationArm = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("LagDistance"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] LagDistance"), SectionName);
		}
		else
		{
			IVR_LagDistance = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("CameraManName"), IVR_CameraManName) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] CameraManName"), SectionName);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *(IVR_CameraManName));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("CameraVelocity"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] CameraVelocity"), SectionName);
		}
		else
		{
			IVR_CameraVelocity = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("BaseTurnRate"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] BaseTurnRate"), SectionName);
		}
		else
		{
			IVR_BaseTurnRate = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		if (IVR_ProjectConfigFile.GetString(SectionName, TEXT("BaseLookUpRate"), tStr) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not load [%s] BaseLookUpRate"), SectionName);
		}
		else
		{
			IVR_BaseLookUpRate = atof(TCHAR_TO_UTF8(*tStr));
			UE_LOG(LogTemp, Log, TEXT("%s"), *(tStr));
		}

		return true;
	}
	else
	{
		IVR_Width = 1024;
		IVR_Height = 768;
		IVR_ClearColor = FLinearColor::Black;
		IVR_Gamma = 1.0f;
		IVR_EnableTurboRecording = false;
		IVR_TurboRate = 3.0f;
		IVR_StabilizationArm = 0.0f;
		IVR_LagDistance = 3.0f;
		IVR_CameraManName = "DefaultCameraMan";
		IVR_CameraVelocity = 350.0f;
		IVR_BaseTurnRate = 30.0f;
		IVR_BaseLookUpRate = 30.0f;

		return true;
	}

	return false;
}

// Called when the game starts or when spawned
void AIVR_CameraMan::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AIVR_CameraMan::CaptureFrame()
{
	// We need a rendertarget to get the frames , so here we guarantee we have one (The User dont need create one!)
	if ((!IVR_CameraCapture->IsValidLowLevel()) || (!IVR_RenderTarget->IsValidLowLevel()))
	{
		IVR_RenderTarget = NewObject<UTextureRenderTarget2D>();
		if (IVR_RenderTarget)
		{
			IVR_RenderTarget->ClearColor = IVR_ClearColor;
			IVR_RenderTarget->TargetGamma = IVR_Gamma;
			IVR_RenderTarget->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8_SRGB;
			IVR_RenderTarget->InitAutoFormat(IVR_Width, IVR_Height);
		}

		IVR_CameraCapture->TextureTarget = IVR_RenderTarget;
	}

	//We attach the Rendertarget here to guarantee a Dinamic Texture Too...This avoid the Texture streaming invalidate The texture.
	IVR_CameraCapture->TextureTarget = IVR_RenderTarget;

	//This is Critical!
	//Since we are getting a GameThread Resource everything we do after it must be done in another Thread, so be careful to develop
	//Thread safe routines to threat the frames.
	FRenderTarget* RenderTarget = IVR_CameraCapture->TextureTarget->GameThread_GetRenderTargetResource();
	if (RenderTarget == nullptr)
	{
		return false;
	}

	TArray<FColor> RawPixels;

	// Format not supported - use PF_B8G8R8A8.
	if (IVR_CameraCapture->TextureTarget->GetFormat() != PF_B8G8R8A8)
	{
		return false;
	}

	//The raw pixels of the final frame recording
	if (!RenderTarget->ReadPixels(RawPixels))
	{
		return false;
	}

	//Here you put your Thread safe code, ok?
	UIVR_FunctionLibrary::IVR_AsyncRecordFrame(IVR_CameraManName, IVR_FrameCounter, RawPixels, IVR_Width, IVR_Height, IVR_ClearColor.ToFColor(false));
	
	//Increase the FrameCounter
	IVR_FrameCounter++;

	//huhuuuu!
	return true;

}


// Called every frame
void AIVR_CameraMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IVR_FPS = (1.0 / DeltaTime);

	if (IVR_EnableTurboRecording)
	{
		IVR_FPS = IVR_FPS * IVR_TurboRate;
	}

	if (!IVR_SelfRegistered)
	{
		IVR_CameraID.IVR_CameraName   = IVR_CameraManName;
		IVR_CameraID.IVR_IsStabilized = IVR_EnableStabilization;
		IVR_CameraID.IVR_IsEnabled    = IVR_Enabled;
		IVR_CameraID.IVR_FPS          = IVR_FPS;
		
		UIVR_FunctionLibrary::IVR_AddCamera(IVR_CameraID);

		IVR_SelfRegistered = true;
	}

	//Mantain the base data updated with the Master! :)
	IVR_CameraID.IVR_CameraName   = IVR_CameraManName;
	IVR_CameraID.IVR_IsStabilized = IVR_EnableStabilization;
	IVR_CameraID.IVR_IsEnabled    = IVR_Enabled;
	IVR_CameraID.IVR_FPS          = IVR_FPS;
	UIVR_FunctionLibrary::IVR_UpdCamera(IVR_CameraID);

	IVR_RecordingState = UIVR_FunctionLibrary::IVR_CheckRecordingState();
	switch (IVR_RecordingState)
	{
	case 0:	//Start Recording
	{
		//We Enable the Camera
		IVR_Enabled = true;
		
		FIVR_CameraFrame Frame;

		Frame.IVR_CameraName = IVR_CameraManName;
		Frame.IVR_FrameFPS   = IVR_FPS;
		Frame.IVR_Position   = GetActorLocation();
		Frame.IVR_Rotation   = GetActorRotation().Vector();
		Frame.IVR_Scale      = GetActorScale();

		//Collect the Historical data of the Recording(This will be usefull for Post-Recording Purposes)
		IVR_CameraID.IVR_Frames.Add(Frame);

		//Effectively capture a rendered frame and asyncronously record the frame at Hard Drive.
		CaptureFrame();
	}break;
	case 1: //Stop Recording
	{
		//The manager will take care to change the transition in the next checking...
		if (IVR_Enabled)
		{
			//Since the recording Stop we give to the Manager all Collected Frames and CleanUp For the next Section
			UIVR_FunctionLibrary::IVR_UpdCameraFrames(IVR_CameraID);
			//Reset the Counter!
			IVR_FrameCounter = 0;
			//We Disable the Camera
			IVR_Enabled = false;
		}
	}break;
	case 2: //Iddle
	{
		if (!IVR_EnableStabilization)
		{
			IVR_Stabilizer->bEnableCameraLag = false;
			IVR_Stabilizer->bEnableCameraRotationLag = false;
			IVR_Stabilizer->CameraLagMaxDistance = 0.0f;
			IVR_Stabilizer->TargetArmLength = 0.0f;
			IVR_Stabilizer->CameraLagSpeed = 0.0f;
			IVR_Stabilizer->CameraRotationLagSpeed = 0.0f;
		}
		else
		{
			IVR_Stabilizer->bEnableCameraLag = true;
			IVR_Stabilizer->bEnableCameraRotationLag = true;
			IVR_Stabilizer->CameraLagMaxDistance = IVR_LagDistance;
			IVR_Stabilizer->TargetArmLength = IVR_StabilizationArm;
			IVR_Stabilizer->CameraLagSpeed = IVR_StabilizationRate;
			IVR_Stabilizer->CameraRotationLagSpeed = IVR_StabilizationRate;
		}
	}break;
	}
}

// Called to bind functionality to input
void AIVR_CameraMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveCameraManFoward"    , this, &AIVR_CameraMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveCameraManRight"     , this, &AIVR_CameraMan::MoveRight);
	PlayerInputComponent->BindAxis("MoveCameraManTurnRate"  , this, &AIVR_CameraMan::TurnAtRate);
	PlayerInputComponent->BindAxis("MoveCameraManLookUpRate", this, &AIVR_CameraMan::LookUpAtRate);
	
	PlayerInputComponent->BindAction("StartRecord"  , IE_Pressed, this, &AIVR_CameraMan::StartRecord);
	PlayerInputComponent->BindAction("StopRecord"   , IE_Pressed, this, &AIVR_CameraMan::StopRecord);
	PlayerInputComponent->BindAction("CompileVideos", IE_Pressed, this, &AIVR_CameraMan::CompileVideo);
	PlayerInputComponent->BindAction("GrabbCameras" , IE_Pressed, this, &AIVR_CameraMan::CameraGrabbSpawner); 
}

// Called to bind functionality to input
void AIVR_CameraMan::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

// Called to bind functionality to input
void AIVR_CameraMan::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

// Called to bind functionality to input
void AIVR_CameraMan::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * IVR_BaseTurnRate * GetWorld()->GetDeltaSeconds());
	IVR_CameraCapture->SetRelativeRotation(IVR_Camera->GetRelativeRotation());
}

// Called to bind functionality to input
void AIVR_CameraMan::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * IVR_BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	IVR_CameraCapture->SetRelativeRotation(IVR_Camera->GetRelativeRotation());
}

void AIVR_CameraMan::StartRecord()
{
	UAudioMixerBlueprintLibrary::StartRecordingOutput(GetWorld(), 10000);
	UIVR_FunctionLibrary::IVR_SingleShotRecordingMessage(0);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Recording Start!"));
}
void AIVR_CameraMan::StopRecord()
{
	FString FrameFilesPath = FPaths::ConvertRelativePathToFull(UIVR_FunctionLibrary::IVR_GetAppRepository());
	FString FramesPath     = FrameFilesPath + "/";

	//As a Commander Camera we give a SingleShot Stop Message
	UAudioMixerBlueprintLibrary::StopRecordingOutput(GetWorld(), EAudioRecordingExportType::WavFile, IVR_CameraManName + ".wav", FramesPath);
	UIVR_FunctionLibrary::IVR_SingleShotRecordingMessage(1);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Recording Stop!"));
}
void AIVR_CameraMan::CompileVideo()
{
	UIVR_FunctionLibrary::IVR_SingleShotVideoRecording();
}


void AIVR_CameraMan::CameraGrabbSpawner()
{
	UWorld* pWorld = GetWorld();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(pWorld, ACameraActor::StaticClass(), FoundActors);

	IVR_ChildCams.Empty();

	int32 Counter = 0;
	for (AActor* TActor : FoundActors)
	{
		IVR_ChildCams.Add(NewObject<AIVR_CameraMan>());

		IVR_ChildCams[Counter] = pWorld->SpawnActorAbsolute< AIVR_CameraMan >(TActor->GetActorLocation(), TActor->GetActorRotation());

		if (IVR_ChildCams[Counter] != nullptr)
		{
			//Filling The Camera Data Initialization(Just to avoid any inconsistency...) , The only information for Mngmt is the name and ID struct 
			IVR_ChildCams[Counter]->IVR_CameraManName = "AutoSpawned" + FString::FromInt(Counter);
			IVR_ChildCams[Counter]->IVR_Width = 1024;
			IVR_ChildCams[Counter]->IVR_Height = 768;
			IVR_ChildCams[Counter]->IVR_ClearColor = FLinearColor::Black;
			IVR_ChildCams[Counter]->IVR_Gamma = 1.0;
			IVR_ChildCams[Counter]->IVR_EnableStabilization = true;
			IVR_ChildCams[Counter]->IVR_StabilizationRate = 10.0f;
			IVR_ChildCams[Counter]->IVR_CameraVelocity = 350.0f;
			IVR_ChildCams[Counter]->IVR_BaseTurnRate = 35.f;
			IVR_ChildCams[Counter]->IVR_BaseLookUpRate = 35.f;
			IVR_ChildCams[Counter]->IVR_FrameCounter = 0;
			IVR_ChildCams[Counter]->IVR_RecordingState = 2;//Initially Iddle
			IVR_ChildCams[Counter]->IVR_SelfRegistered = false;
			IVR_ChildCams[Counter]->IVR_FPS = 0;
			IVR_ChildCams[Counter]->IVR_StabilizationArm = 0.0f;
			IVR_ChildCams[Counter]->IVR_LagDistance = 25.0f;
			IVR_ChildCams[Counter]->IVR_Enabled = false;

			//For Turbo recording the Child get the values from the Owner...
			IVR_ChildCams[Counter]->IVR_EnableTurboRecording = IVR_EnableTurboRecording;
			IVR_ChildCams[Counter]->IVR_TurboRate            = IVR_TurboRate;

			IVR_ChildCams[Counter]->SetActorLocation(TActor->GetActorLocation());
			IVR_ChildCams[Counter]->SetActorRotation(TActor->GetActorRotation());

			//Filling The Camera Pooling Data For the Camera Management
			IVR_ChildCams[Counter]->IVR_CameraID.IVR_CameraName   = IVR_ChildCams[Counter]->IVR_CameraManName;
			IVR_ChildCams[Counter]->IVR_CameraID.IVR_IsStabilized = IVR_ChildCams[Counter]->IVR_EnableStabilization;
			IVR_ChildCams[Counter]->IVR_CameraID.IVR_IsEnabled    = IVR_ChildCams[Counter]->IVR_Enabled;
			
			UIVR_FunctionLibrary::IVR_AddCamera(IVR_ChildCams[Counter]->IVR_CameraID);

			Counter++;
		}	
	}
}

