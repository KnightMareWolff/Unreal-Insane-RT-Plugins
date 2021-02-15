// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/MessageDialog.h"
#include "Containers/Queue.h"

//Audio
#include "Components/AudioComponent.h"
#include "AudioDecompress.h"
#include "AudioDevice.h"
#include "ActiveSound.h"
#include "Audio.h"
#include "Developer/TargetPlatform/Public/Interfaces/IAudioFormat.h"
#include "VorbisAudioInfo.h"

//Texture2D
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Engine/Texture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "DDSLoader.h"

#if WITH_OPENCV
#include "OpenCVHelper.h"
OPENCV_INCLUDES_START
#undef check // the check macro causes problems with opencv headers
#include "opencv2/core.hpp"
#include "opencv2/core/base.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/video.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/videostab.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
OPENCV_INCLUDES_END
#endif

#include "ZVR_FunctionLibrary.generated.h"

using namespace std;
using namespace cv;
using namespace cv::videostab;
using namespace cv::xfeatures2d;

/**
* Represent a camera frame on the global camera storage.
* This struct are used to control video recordings without need access the real cameras
* Inside of the enviroment and Collect specific recording Frames.
*/
USTRUCT(BlueprintType)
struct FZVR_CameraFrame
{
	GENERATED_BODY()

public:
	//Store the real camera name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ZVR_CameraName;
	//Store the Min FPS Collected by the camera recordings
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float   ZVR_FrameFPS;
	//Reference Position for the Frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZVR_Position;
	//Reference Rotation for the Frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZVR_Rotation;
	//Reference Scale for the Frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZVR_Scale;
};

/**
* Represent a message to a camera on the global camera storage.
* This struct are used to control video recordings without need access the real cameras
* Inside of the enviroment and Collect specific recording Frames.
*/
USTRUCT(BlueprintType)
struct FZVR_CameraMessage
{
	GENERATED_BODY()

public:
	//Store the real camera name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ZVR_CameraName;
	//Store the Min FPS Collected by the camera recordings
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ZVR_Action;
	//Reference Position for the Action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZVR_Position;
	//Reference Rotation for the Action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZVR_Rotation;
	//Reference Scale for the Action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZVR_Scale;
};

/**
* Represent a camera on the global camera storage.
* This struct are used to control video recordings without need access the real cameras
* Inside of the enviroment and Collect specific recording Frames.
*/
USTRUCT(BlueprintType)
struct FZVR_CameraStruct
{
	GENERATED_BODY()

public:
	//Store the real camera name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString                   ZVR_CameraName;
	//Store the Last FPS Collected by the camera recordings
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float                     ZVR_FPS;
	//If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool                      ZVR_IsStabilized;
	//Flag to Know the Camera State.(Take Care to not enable it in the wrong time!)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool                      ZVR_IsEnabled;
	//If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FZVR_CameraFrame>  ZVR_Frames;
};

/**
 * 
 */
UCLASS()
class ZOANVIDEO_API UZVR_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="ZOAN|Video|Functions")
	static UTextureRenderTarget2D* ZVR_CreateTextureRenderTarget2D(int32 Width = 256, int32 Height = 256, FLinearColor ClearColor = FLinearColor::White, float Gamma = 1)
	{
		UTextureRenderTarget2D* NewRenderTarget2D = NewObject<UTextureRenderTarget2D>();
		if (!NewRenderTarget2D)
		{
			return nullptr;
		}
		NewRenderTarget2D->ClearColor = ClearColor;
		NewRenderTarget2D->TargetGamma = Gamma;
		NewRenderTarget2D->InitAutoFormat(Width, Height);
		return NewRenderTarget2D;
	}

	static TSharedPtr<IImageWrapper> GetImageWrapperByExtention(const FString InImagePath)
	{
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		if (InImagePath.EndsWith(".png"))
		{
			return ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
		}
		else if (InImagePath.EndsWith(".jpg") || InImagePath.EndsWith(".jpeg"))
		{
			return ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
		}
		else if (InImagePath.EndsWith(".bmp"))
		{
			return ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
		}
		else if (InImagePath.EndsWith(".ico"))
		{
			return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICO);
		}
		else if (InImagePath.EndsWith(".exr"))
		{
			return ImageWrapperModule.CreateImageWrapper(EImageFormat::EXR);
		}
		else if (InImagePath.EndsWith(".icns"))
		{
			return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICNS);
		}

		return nullptr;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static bool ZVR_TakeSnapshot(class USceneCaptureComponent2D* Target, const FString ImagePath, const FLinearColor ClearColour)
	{
		// Bad scene capture component! No render target! Stay! Stay! Ok, feed!... wait, where was I?
		if ((Target == nullptr) || (Target->TextureTarget == nullptr))
		{
			return false;
		}

		FRenderTarget* RenderTarget = Target->TextureTarget->GameThread_GetRenderTargetResource();
		if (RenderTarget == nullptr)
		{
			return false;
		}

		TArray<FColor> RawPixels;

		// Format not supported - use PF_B8G8R8A8.
		if (Target->TextureTarget->GetFormat() != PF_B8G8R8A8)
		{
			// TRACEWARN("Format not supported - use PF_B8G8R8A8.");
			return false;
		}

		if (!RenderTarget->ReadPixels(RawPixels))
		{
			return false;
		}

		// Convert to FColor.
		FColor ClearFColour = ClearColour.ToFColor(false); // FIXME - want sRGB or not?

		for (auto& Pixel : RawPixels)
		{
			// Switch Red/Blue changes.
			const uint8 PR = Pixel.R;
			const uint8 PB = Pixel.B;
			Pixel.R = PB;
			Pixel.B = PR;

			// Set alpha based on RGB values of ClearColour.
			Pixel.A = ((Pixel.R == ClearFColour.R) && (Pixel.G == ClearFColour.G) && (Pixel.B == ClearFColour.B)) ? 0 : 255;
		}

		TSharedPtr<IImageWrapper> ImageWrapper = GetImageWrapperByExtention(ImagePath);

		const int32 Width = Target->TextureTarget->SizeX;
		const int32 Height = Target->TextureTarget->SizeY;

		if (ImageWrapper.IsValid() && ImageWrapper->SetRaw(&RawPixels[0], RawPixels.Num() * sizeof(FColor), Width, Height, ERGBFormat::RGBA, 8))
		{
			FFileHelper::SaveArrayToFile(ImageWrapper->GetCompressed(), *ImagePath);
			return true;
		}

		return false;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static UTexture2D* ZVR_LoadTexture(const FString& ImagePath, bool& IsValid, int32& OutWidth, int32& OutHeight)
	{
		UTexture2D* Texture = nullptr;
		IsValid = false;

		// To avoid log spam, make sure it exists before doing anything else.
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*ImagePath))
		{
			return nullptr;
		}

		TArray<uint8> CompressedData;
		if (!FFileHelper::LoadFileToArray(CompressedData, *ImagePath))
		{
			return nullptr;
		}

		TSharedPtr<IImageWrapper> ImageWrapper = GetImageWrapperByExtention(ImagePath);

		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(CompressedData.GetData(), CompressedData.Num()))
		{
			TArray<uint8> UncompressedRGBA;

			if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
			{
				Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_R8G8B8A8);

				if (Texture != nullptr)
				{
					IsValid = true;

					OutWidth = ImageWrapper->GetWidth();
					OutHeight = ImageWrapper->GetHeight();

					void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
					Texture->PlatformData->Mips[0].BulkData.Unlock();
					Texture->UpdateResource();
				}
			}
		}

		return Texture;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static void ZVR_AsyncRecordFrame(FString pZVR_CameraName, int32 pZVR_Frame, TArray<FColor> RawPixels, int32 Width , int32 Height , FColor ClearFColour)
	{
		AsyncTask(ENamedThreads::AnyBackgroundHiPriTask, [pZVR_CameraName, pZVR_Frame,RawPixels, Width, Height, ClearFColour]()
			{
				pZVR_WriteCriticalSection.Lock();
				
				TArray<FColor> PixelsToWrite = RawPixels;

				for (auto& Pixel : PixelsToWrite)
				{
					// Switch Red/Blue changes.
					const uint8 PR = Pixel.R;
					const uint8 PB = Pixel.B;
					Pixel.R = PB;
					Pixel.B = PR;

					// Set alpha based on RGB values of ClearColour.
					Pixel.A = ((Pixel.R == ClearFColour.R) && (Pixel.G == ClearFColour.G) && (Pixel.B == ClearFColour.B)) ? 0 : 255;
				}

				
				FString FrameFilesPath = FPaths::ConvertRelativePathToFull(ZVR_GetAppRepository());
				FString FramesCounter = FString::FromInt(pZVR_Frame);
				FString FramesPath = FrameFilesPath + "/" + pZVR_CameraName + "_" + FramesCounter + ".jpg";

				TSharedPtr<IImageWrapper> ImageWrapper;

				IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
				if (FramesPath.EndsWith(".png"))
				{
					ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
				}
				else if (FramesPath.EndsWith(".jpg") || FramesPath.EndsWith(".jpeg"))
				{
					ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
				}
				else if (FramesPath.EndsWith(".bmp"))
				{
					ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
				}
				else if (FramesPath.EndsWith(".ico"))
				{
					ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::ICO);
				}
				else if (FramesPath.EndsWith(".exr"))
				{
					ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::EXR);
				}
				else if (FramesPath.EndsWith(".icns"))
				{
					ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::ICNS);
				}


				if (ImageWrapper.IsValid() && ImageWrapper->SetRaw(&PixelsToWrite[0], PixelsToWrite.Num() * sizeof(FColor), Width, Height, ERGBFormat::RGBA, 8))
				{
					FFileHelper::SaveArrayToFile(ImageWrapper->GetCompressed(), *FramesPath);
				}

				pZVR_WriteCriticalSection.Unlock();

			});
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static UTexture2D* ZVR_LoadFrame(FString pZVR_CameraName, int32 pZVR_Frame, bool& IsValid, int32& OutWidth, int32& OutHeight)
	{
		IsValid = false;
		int32 CameraIndex=0;

		FString ZVR_FrameFilesPath;
		FString ZVR_FramesPath;
		FString Frame = FString::FromInt(pZVR_Frame);

		//get the camera index
		for (int32 CameraID = 0; CameraID < pZVR_CameraPool.Num(); CameraID++)
		{
			if (pZVR_CameraPool[CameraID].ZVR_CameraName == pZVR_CameraName)CameraIndex = CameraID;
		}

		ZVR_FrameFilesPath = FPaths::ConvertRelativePathToFull(ZVR_GetAppRepository());
		ZVR_FramesPath     = ZVR_FrameFilesPath + "/" + pZVR_CameraPool[CameraIndex].ZVR_CameraName + "_" + Frame + ".jpg";
		
		// To avoid log spam, make sure it exists before doing anything else.
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*ZVR_FramesPath))
		{
			return nullptr;
		}

		TArray<uint8> CompressedData;
		if (!FFileHelper::LoadFileToArray(CompressedData, *ZVR_FramesPath))
		{
			return nullptr;
		}

		TSharedPtr<IImageWrapper> ImageWrapper = GetImageWrapperByExtention(ZVR_FramesPath);

		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(CompressedData.GetData(), CompressedData.Num()))
		{
			TArray<uint8> UncompressedRGBA;

			if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
			{
				if (pZVR_Texture != nullptr)
				{
					auto TSize     = ImageWrapper->GetWidth();
					auto Pitch     = GPixelFormats[pZVR_Texture->GetPixelFormat()].BlockBytes * TSize;
					auto BlockSize = GPixelFormats[pZVR_Texture->GetPixelFormat()].BlockBytes;

					pZVR_Texture->UpdateTextureRegions(0,1, pZVR_TextureRegion.get(), Pitch, BlockSize, UncompressedRGBA.GetData());
					
					IsValid = true;

					OutWidth  = ImageWrapper->GetWidth();
					OutHeight = ImageWrapper->GetHeight();
				}
				else
				{
					pZVR_TextureRegion = std::unique_ptr<FUpdateTextureRegion2D>(new FUpdateTextureRegion2D(0, 0, 0, 0, ImageWrapper->GetWidth(), ImageWrapper->GetHeight()));
					pZVR_Texture       = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_R8G8B8A8);
					if (pZVR_Texture != nullptr)
					{
						IsValid = true;

						OutWidth = ImageWrapper->GetWidth();
						OutHeight = ImageWrapper->GetHeight();

						void* TextureData = pZVR_Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
						FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
						pZVR_Texture->PlatformData->Mips[0].BulkData.Unlock();
						pZVR_Texture->UpdateResource();
					}

				}
			}
		}
		else
		{
			return nullptr;
		}

		return pZVR_Texture;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static UTexture2D* ZVR_CVLoadFrame(FString pZVR_CameraName, int32 pZVR_Frame, bool& IsValid, int32& OutWidth, int32& OutHeight)
	{
		IsValid = false;
		int32 CameraIndex=0;

		FString ZVR_FrameFilesPath;
		FString ZVR_FramesPath;
		FString Frame = FString::FromInt(pZVR_Frame);

		//Warning!!! 
		//In my tests here if we not sleep the rendering at least 60 miliseconds Unreal Crashes becouse not have time to update the Resource at GPU.
		//This is Why in all the cases Unreal try preload resourses , ok?
		//This was done only to make possible we previsualize video frames in the HUD and wait 60ms to load a single image will not hurt... ;)
		std::this_thread::sleep_for(std::chrono::milliseconds(60));

		//get the camera index
		for (int32 CameraID = 0; CameraID < pZVR_CameraPool.Num(); CameraID++)
		{
			if (pZVR_CameraPool[CameraID].ZVR_CameraName == pZVR_CameraName)CameraIndex = CameraID;
		}

		ZVR_FrameFilesPath = FPaths::ConvertRelativePathToFull(ZVR_GetAppRepository());
		ZVR_FramesPath     = ZVR_FrameFilesPath + "/" + pZVR_CameraPool[CameraIndex].ZVR_CameraName + "_" + Frame + ".jpg";
		
		// To avoid log spam, make sure it exists before doing anything else.
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*ZVR_FramesPath))
		{
			return nullptr;
		}

		TArray<FColor> CompressedData;
		Mat  tCVImage;

		tCVImage = imread(TCHAR_TO_UTF8(*ZVR_FramesPath), IMREAD_COLOR);
		
		CompressedData.Empty();
		CompressedData.Init(FColor(0, 0, 0, 255), tCVImage.rows * tCVImage.cols);

		// Copy Mat data to Data array
		for (int y = 0; y < tCVImage.cols; y++)
		{
		    for (int x = 0; x < tCVImage.rows; x++)
		    {
		       int i = x + (y * tCVImage.cols);
			   CompressedData[i].B = tCVImage.data[i * 3 + 2];
			   CompressedData[i].G = tCVImage.data[i * 3 + 1];
			   CompressedData[i].R = tCVImage.data[i * 3 + 0];
			}
		}
			  
		if (pZVR_Texture != nullptr && pZVR_Texture->PlatformData != nullptr)
		{
			
			auto TSize     = tCVImage.rows;
			auto Pitch     = GPixelFormats[pZVR_Texture->GetPixelFormat()].BlockBytes * TSize;
			auto BlockSize = GPixelFormats[pZVR_Texture->GetPixelFormat()].BlockBytes;
			pZVR_Texture->UpdateTextureRegions(0, 1, pZVR_TextureRegion.get(), Pitch, BlockSize , (uint8*)CompressedData.GetData());
			
			IsValid = true;
			OutWidth  = tCVImage.rows;
			OutHeight = tCVImage.cols;
			
			return pZVR_Texture;
		}
		else
		{
			pZVR_TextureRegion = std::unique_ptr<FUpdateTextureRegion2D>(new FUpdateTextureRegion2D(0, 0, 0, 0, tCVImage.cols, tCVImage.rows));
			pZVR_Texture       = UTexture2D::CreateTransient(tCVImage.cols, tCVImage.rows, PF_R8G8B8A8);

			if (pZVR_Texture != nullptr)
			{
				IsValid = true;

				OutWidth  = tCVImage.cols;
				OutHeight = tCVImage.rows;

				void* TextureData = pZVR_Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, (uint8*)CompressedData.GetData(), (tCVImage.rows * tCVImage.cols));
				pZVR_Texture->PlatformData->Mips[0].BulkData.Unlock();
				pZVR_Texture->UpdateResource();

				return pZVR_Texture;
			}

		}

		//never reach here but...
		return nullptr;
		
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static void ZVR_AddCamera(FZVR_CameraStruct pZVR_Camera)
	{
		//if The Camera already exist, Do nothing! Unreal creates many instances of a Single actor in Many Threads...
		for (int32 CameraID = 0; CameraID < pZVR_CameraPool.Num(); CameraID++)
		{
			if (pZVR_CameraPool[CameraID].ZVR_CameraName == pZVR_Camera.ZVR_CameraName)return;
		}
		pZVR_CameraPool.Add(pZVR_Camera);
		return;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static void ZVR_UpdCamera(FZVR_CameraStruct pZVR_Camera)
	{
		//In Future this routines can be improved , like a hash map or something... :)
		for (int32 CameraID = 0; CameraID < pZVR_CameraPool.Num(); CameraID++)
		{
			//If found something, update...
			if (pZVR_CameraPool[CameraID].ZVR_CameraName == pZVR_Camera.ZVR_CameraName)
			{
				pZVR_CameraPool[CameraID].ZVR_CameraName   = pZVR_Camera.ZVR_CameraName;
				pZVR_CameraPool[CameraID].ZVR_IsStabilized = pZVR_Camera.ZVR_IsStabilized;
				pZVR_CameraPool[CameraID].ZVR_IsEnabled    = pZVR_Camera.ZVR_IsEnabled;
				pZVR_CameraPool[CameraID].ZVR_FPS          = pZVR_Camera.ZVR_FPS;
				return;
			}
		}
		return;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static void ZVR_UpdCameraFrames(FZVR_CameraStruct pZVR_Camera)
	{
		//In Future this routines can be improved , like a hash map or something... :)
		for (int32 CameraID = 0; CameraID < pZVR_CameraPool.Num(); CameraID++)
		{
			//If found something, update...
			if (pZVR_CameraPool[CameraID].ZVR_CameraName == pZVR_Camera.ZVR_CameraName)
			{
				//CleanUp the Pool List
				pZVR_CameraPool[CameraID].ZVR_Frames.Empty();
				for (int i = 0; i < pZVR_Camera.ZVR_Frames.Num(); i++)
				{
					pZVR_CameraPool[CameraID].ZVR_Frames.Add(pZVR_Camera.ZVR_Frames[i]);
				}
				//CleanUp the CameraFramesPool for Sanity...
				pZVR_Camera.ZVR_Frames.Empty();
				return;
			}
		}
		return;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static void ZVR_SingleShotRecordingMessage(int pZVR_State)
	{
		pZVR_GlobalRecording = pZVR_State;
		return;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static int ZVR_CheckRecordingState()
	{
		int  AllDisabled = 0;
		
		//If we are disabling a Recording we change to iddle only when all the cameras was Disabled Properly...
		if (pZVR_GlobalRecording == 1)
		{
			//In Future this routines can be improved , like a hash map or something... :)
			for (int32 CameraID = 0; CameraID < pZVR_CameraPool.Num(); CameraID++)
			{
				//We count how many cameras are disabled
				if (!pZVR_CameraPool[CameraID].ZVR_IsEnabled)AllDisabled++;
			}

			//If all the cameras are disabled we enter in the Iddle Mode...
			//Probably this will be changed when we start control individual messages...
			//By now is sufficient to mantain a good recording experince in Parallel for any number of cameras by a single Manager...
			if (AllDisabled == pZVR_CameraPool.Num())ZVR_SingleShotRecordingMessage(2);
		}
		return pZVR_GlobalRecording;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static FString ZVR_GetAppRepository()
	{
		return pZVR_FrameFilesPath;
	}

	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static void ZVR_SetAppRepository(FString pZVR_AppPath)
	{
		pZVR_FrameFilesPath = pZVR_AppPath;
	}

	
	//This function will get all the camera frames and record their respective Videos
	UFUNCTION(Category = "ZOAN|Video|Functions", BlueprintCallable)
	static bool ZVR_SingleShotVideoRecording()
	{
		FString ZVR_FrameFilesPath;
		FString ZVR_FramesPath;

		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Starting Record the Videos...This will take a lot of Time! \n (Check Before if the System are not recording frames yet...)")));
		//Record the video for each Camera we have
		for (int32 CameraID = 0; CameraID < pZVR_CameraPool.Num(); CameraID++)
		{
			uint FrameNumber = 0;

			ZVR_FrameFilesPath = FPaths::ConvertRelativePathToFull(ZVR_GetAppRepository());
			ZVR_FramesPath = ZVR_FrameFilesPath + "/" + pZVR_CameraPool[CameraID].ZVR_CameraName + "_%d.jpg";


			//Cria Video de entrada com os frames gravados.
			cv::VideoCapture cap(TCHAR_TO_UTF8(*ZVR_FramesPath));

			// if not success, exit program
			if (cap.isOpened() == false)
			{
				FString Message = "There is no recording for the Camera = " + pZVR_CameraPool[CameraID].ZVR_CameraName + "!";

				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
				continue;
			}

			int frame_width  = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
			int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video

			cv::Size frame_size(frame_width, frame_height);
			
			//Get The Last Frame Collected by the Camera
			//int frames_per_second = (uint)pZVR_CameraPool[CameraID].ZVR_FPS;
			
			int frames_per_second=0;
			for (int i = 0; i < (int)pZVR_CameraPool[CameraID].ZVR_Frames.Num(); i++)
			{
				frames_per_second += (int)pZVR_CameraPool[CameraID].ZVR_Frames[i].ZVR_FrameFPS;
			}
			
			frames_per_second = frames_per_second / (int)pZVR_CameraPool[CameraID].ZVR_Frames.Num();

			FString VideoPath = ZVR_FrameFilesPath + "/" + pZVR_CameraPool[CameraID].ZVR_CameraName + "Output.avi";

			//Create and initialize the VideoWriter object
			cv::VideoWriter oVideoWriter(TCHAR_TO_UTF8(*VideoPath),
				0,
				frames_per_second,
				frame_size,
				true);

			//If the VideoWriter object is not initialized successfully, exit the program
			if (oVideoWriter.isOpened() == false)
			{
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Video Capture was not deinitialized properly.")));
				return false;
			}

			while (true)
			{
				cv::Mat frame;
				bool isSuccess = cap.read(frame); // read a new frame from the video camera

				//Breaking the while loop if frames cannot be read from the camera
				if (isSuccess == false)
				{
					frame.release();
					oVideoWriter.release();
					cap.release();
					break;
				}

				/*
				Make changes to the frame as necessary
				e.g.
				1. Change brightness/contrast of the image
				2. Smooth/Blur image
				3. Crop the image
				4. Rotate the image
				5. Draw shapes on the image
				*/

				//write the video frame to the file
				oVideoWriter.write(frame);

				FrameNumber++;

			}

			
			//Delete the Frames
			for (uint i = 0; i < FrameNumber; i++)
			{
				FString FileToDeletePath = "/" + pZVR_CameraPool[CameraID].ZVR_CameraName + FString::Printf(TEXT("_%d.jpg"), i);
				FString FinalPath        = ZVR_FrameFilesPath + FileToDeletePath;

				if (!FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*FinalPath))
				{
					FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Could Not Find File")));
					return false;
				}
			}
		}

		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Great!...All The Videos are avaliable!")));
		return true;
	}
	
	//Global storage for the Video recording sessions
	static TArray<FZVR_CameraStruct>               pZVR_CameraPool;
	static int                                     pZVR_GlobalRecording;
	static bool                                    pZVR_GlobalReset;
	static UTexture2D*                             pZVR_Texture;
	static std::unique_ptr<FUpdateTextureRegion2D> pZVR_TextureRegion;
	static FCriticalSection                        pZVR_WriteCriticalSection;
	static FCriticalSection                        pZVR_ReadCriticalSection;
	static FString                                 pZVR_FrameFilesPath;
	
};
