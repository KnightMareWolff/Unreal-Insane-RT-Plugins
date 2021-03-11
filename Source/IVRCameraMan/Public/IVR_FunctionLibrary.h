/************************************************************************/
/*Project              :IVR CameraMan - Unreal Plugin                   */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2021 William Wolff. All rights reserved                 */
/************************************************************************/
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
#include "IVROpenCVHelper.h"
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

#include "IVR_FunctionLibrary.generated.h"

using namespace std;
using namespace cv;
using namespace cv::videostab;
using namespace cv::xfeatures2d;


class AIVR_CameraMan;

/**
* Represent a camera frame on the global camera storage.
* This struct are used to control video recordings without need access the real cameras
* Inside of the enviroment and Collect specific recording Frames.
*/
USTRUCT(BlueprintType)
struct FIVR_CameraFrame
{
	GENERATED_BODY()

public:
	//Store the real camera name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FString IVR_CameraName;
	//Store the Frame FPS Collected by the camera recordings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	float   IVR_FrameFPS;
	//Reference Position for the Frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FVector IVR_Position;
	//Reference Rotation for the Frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FVector IVR_Rotation;
	//Reference Scale for the Frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FVector IVR_Scale;
};

/**
* Represent a message to a camera on the global camera storage.
* This struct are used to control video recordings without need access the real cameras
* Inside of the enviroment and Collect specific recording Frames.
*/
USTRUCT(BlueprintType)
struct FIVR_CameraMessage
{
	GENERATED_BODY()

public:
	//Store the real camera name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FString IVR_CameraName;
	//Store the action to be performed by the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FString IVR_Action;
	//Reference Position for the Action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FVector IVR_Position;
	//Reference Rotation for the Action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FVector IVR_Rotation;
	//Reference Scale for the Action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FVector IVR_Scale;
};

/**
* Represent a camera on the global camera storage.
* This struct are used to control video recordings without need access the real cameras
* Inside of the enviroment and Collect specific recording Frames.
*/
USTRUCT(BlueprintType)
struct FIVR_CameraStruct
{
	GENERATED_BODY()

public:
	//Store the real camera name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	FString                   IVR_CameraName;
	//Store the Last FPS Collected by the camera recordings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	float                     IVR_FPS;
	//If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	bool                      IVR_IsStabilized;
	//Flag to Know the Camera State.(Take Care to not enable it in the wrong time!)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	bool                      IVR_IsEnabled;
	//For every frame recorded in a session, we record it in a list of frames at Camera´s Struct.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMan|Video|Structs")
	TArray<FIVR_CameraFrame>  IVR_Frames;
};

/**
 * 
 */
UCLASS()
class IVRCAMERAMAN_API UIVR_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
    * Creates an new RenderTarget ready to use without the user need create one in the Editor.
    */
	UFUNCTION(BlueprintCallable, Category="CameraMan|Video|Functions")
	static UTextureRenderTarget2D* IVR_CreateTextureRenderTarget2D(int32 Width = 256, int32 Height = 256, FLinearColor ClearColor = FLinearColor::White, float Gamma = 1)
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

	/**
	* Creates an wrapper to load image files and the raw bytes comming from it (This function are not avaliable in Blueprints are used as a support function for the .
	* Frame/image loading functions).
	*/
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

	/**
	* Takes a snapshot from a Rendertarget and record the image on the specifyed path.
	* This funcion is good to just take some images being rendered somewhere and was the beginning function when i start develop the video recording.
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static bool IVR_TakeSnapshot(class USceneCaptureComponent2D* Target, const FString ImagePath, const FLinearColor ClearColour)
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

	/**
	* This function reads an image directly from the hard drive and creates a new fresh Texture2D for you.
	* Aditionally returns if the operation was valid and the size of the Image(Good to use in Panels and Canvas).
	* Take Care with this function if your target is to load a lot of textures during a session becouse it creates a new texture!
	* To load a lot of images is better have just one and for every image updates the texture! ;) (See LoadFrame Function.)
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static UTexture2D* IVR_LoadTexture(const FString& ImagePath, bool& IsValid, int32& OutWidth, int32& OutHeight)
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

	/**
	* This function records a camera frame assinchronously, That´s It!
	* This function are critical to make the video recordings work and is an atomic operation.
	* We need look at the problem of the LogFileWatcher freezing Unreal when a lot of frames are being recorded at HD...
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static void IVR_AsyncRecordFrame(FString pIVR_CameraName, int32 pIVR_Frame, TArray<FColor> RawPixels, int32 Width , int32 Height , FColor ClearFColour)
	{
		AsyncTask(ENamedThreads::AnyBackgroundHiPriTask, [pIVR_CameraName, pIVR_Frame,RawPixels, Width, Height, ClearFColour]()
			{
				pIVR_WriteCriticalSection.Lock();
				
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

				
				FString FrameFilesPath = FPaths::ConvertRelativePathToFull(IVR_GetAppRepository());
				FString FramesCounter = FString::FromInt(pIVR_Frame);
				FString FramesPath = FrameFilesPath + "/" + pIVR_CameraName + "_" + FramesCounter + ".jpg";

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

				pIVR_WriteCriticalSection.Unlock();

			});
	}

	/**
	* This function Loads a camera frame from the HD, That´s It!
	* This function read an frame image based on the camera name and frame ID. Basically we are using this function "PlayBack" a recorded video
	* during a recording session. During our tests we reach the limit of texture pool from unreal, so we create at startup a single texture and
	* update it with the new image. 
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static UTexture2D* IVR_LoadFrame(FString pIVR_CameraName, int32 pIVR_Frame, bool& IsValid, int32& OutWidth, int32& OutHeight)
	{
		IsValid = false;
		int32 CameraIndex=0;

		FString IVR_FrameFilesPath;
		FString IVR_FramesPath;
		FString Frame = FString::FromInt(pIVR_Frame);

		//get the camera index
		for (int32 CameraID = 0; CameraID < pIVR_CameraPool.Num(); CameraID++)
		{
			if (pIVR_CameraPool[CameraID].IVR_CameraName == pIVR_CameraName)CameraIndex = CameraID;
		}

		IVR_FrameFilesPath = FPaths::ConvertRelativePathToFull(IVR_GetAppRepository());
		IVR_FramesPath     = IVR_FrameFilesPath + "/" + pIVR_CameraPool[CameraIndex].IVR_CameraName + "_" + Frame + ".jpg";
		
		// To avoid log spam, make sure it exists before doing anything else.
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*IVR_FramesPath))
		{
			return nullptr;
		}

		TArray<uint8> CompressedData;
		if (!FFileHelper::LoadFileToArray(CompressedData, *IVR_FramesPath))
		{
			return nullptr;
		}

		TSharedPtr<IImageWrapper> ImageWrapper = GetImageWrapperByExtention(IVR_FramesPath);

		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(CompressedData.GetData(), CompressedData.Num()))
		{
			TArray<uint8> UncompressedRGBA;

			if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
			{
				if (pIVR_Texture != nullptr)
				{
					auto TSize     = ImageWrapper->GetWidth();
					auto Pitch     = GPixelFormats[pIVR_Texture->GetPixelFormat()].BlockBytes * TSize;
					auto BlockSize = GPixelFormats[pIVR_Texture->GetPixelFormat()].BlockBytes;

					pIVR_Texture->UpdateTextureRegions(0,1, pIVR_TextureRegion.get(), Pitch, BlockSize, UncompressedRGBA.GetData());
					
					IsValid = true;

					OutWidth  = ImageWrapper->GetWidth();
					OutHeight = ImageWrapper->GetHeight();
				}
				else
				{
					pIVR_TextureRegion = std::unique_ptr<FUpdateTextureRegion2D>(new FUpdateTextureRegion2D(0, 0, 0, 0, ImageWrapper->GetWidth(), ImageWrapper->GetHeight()));
					pIVR_Texture       = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_R8G8B8A8);
					if (pIVR_Texture != nullptr)
					{
						IsValid = true;

						OutWidth = ImageWrapper->GetWidth();
						OutHeight = ImageWrapper->GetHeight();

						void* TextureData = pIVR_Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
						FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
						pIVR_Texture->PlatformData->Mips[0].BulkData.Unlock();
						pIVR_Texture->UpdateResource();
					}

				}
			}
		}
		else
		{
			return nullptr;
		}

		return pIVR_Texture;
	}

	/**
	* This function Loads a camera frame from the HD usin OpenCV Library , for optimizations and to make possible work on the Texture before give
	* it back to the system(We can draw quads texts, resize etc...)
	* we include an native sleep of 60 miliseconds becouse the RHI are not having time to update the texture before the texture be avaliable, so
	* dont forget to check if the operation is valid since this can vary from different machines and graphic cards...
	* We are resizing the image to a fixed 256x256 , since the purpose is only for small canvas at HUD objects for pre-visualization
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static UTexture2D* IVR_CVLoadFrame(FString pIVR_CameraName, int32 pIVR_Frame, bool& IsValid, int32& OutWidth, int32& OutHeight)
	{
		IsValid = false;
		int32 CameraIndex=0;

		FString IVR_FrameFilesPath;
		FString IVR_FramesPath;
		FString Frame = FString::FromInt(pIVR_Frame);

		//Warning!!! 
		//In my tests here if we not sleep the rendering at least 60 miliseconds Unreal Crashes becouse not have time to update the Resource at GPU.
		//This was done only to make possible we previsualize video frames in the HUD and wait 60ms to load a single image will not hurt... ;)
		//dont forget to check in Blueprints if the operation is valid since this can vary from different machines and graphic cards...
		std::this_thread::sleep_for(std::chrono::milliseconds(60));

		//get the camera index
		for (int32 CameraID = 0; CameraID < pIVR_CameraPool.Num(); CameraID++)
		{
			if (pIVR_CameraPool[CameraID].IVR_CameraName == pIVR_CameraName)CameraIndex = CameraID;
		}

		IVR_FrameFilesPath = FPaths::ConvertRelativePathToFull(IVR_GetAppRepository());
		IVR_FramesPath     = IVR_FrameFilesPath + "/" + pIVR_CameraPool[CameraIndex].IVR_CameraName + "_" + Frame + ".jpg";
		
		// To avoid log spam, make sure it exists before doing anything else.
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*IVR_FramesPath))
		{
			return nullptr;
		}

		TArray<FColor> CompressedData;
		Mat  tCVImage;
		Mat  tCVResizedImage;

		tCVImage = imread(TCHAR_TO_UTF8(*IVR_FramesPath), IMREAD_COLOR);

		cv::resize(tCVImage, tCVResizedImage,cv::Size(256, 256));
		
		CompressedData.Empty();
		CompressedData.Init(FColor(0, 0, 0, 255), tCVResizedImage.rows * tCVResizedImage.cols);

		// Copy Mat data to Data array
		for (int y = 0; y < tCVResizedImage.cols; y++)
		{
		    for (int x = 0; x < tCVResizedImage.rows; x++)
		    {
		       int i = x + (y * tCVResizedImage.rows);
			   if (i < tCVResizedImage.cols * tCVResizedImage.rows)
			   {
				   CompressedData[i].B = tCVResizedImage.data[i * 3 + 2];
				   CompressedData[i].G = tCVResizedImage.data[i * 3 + 1];
				   CompressedData[i].R = tCVResizedImage.data[i * 3 + 0];
			   }
			}
		}
			  
		if (pIVR_Texture != nullptr && pIVR_Texture->PlatformData != nullptr)
		{
			
			auto TSize     = tCVResizedImage.rows;
			auto Pitch     = GPixelFormats[pIVR_Texture->GetPixelFormat()].BlockBytes * TSize;
			auto BlockSize = GPixelFormats[pIVR_Texture->GetPixelFormat()].BlockBytes;
			pIVR_Texture->UpdateTextureRegions(0, 1, pIVR_TextureRegion.get(), Pitch, BlockSize , (uint8*)CompressedData.GetData());
			
			IsValid = true;
			OutWidth  = tCVResizedImage.rows;
			OutHeight = tCVResizedImage.cols;
			
			return pIVR_Texture;
		}
		else
		{
			pIVR_TextureRegion = std::unique_ptr<FUpdateTextureRegion2D>(new FUpdateTextureRegion2D(0, 0, 0, 0, tCVResizedImage.cols, tCVResizedImage.rows));
			pIVR_Texture       = UTexture2D::CreateTransient(tCVResizedImage.cols, tCVResizedImage.rows, PF_R8G8B8A8);

			if (pIVR_Texture != nullptr)
			{
				IsValid = true;

				OutWidth  = tCVResizedImage.cols;
				OutHeight = tCVResizedImage.rows;

				void* TextureData = pIVR_Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, (uint8*)CompressedData.GetData(), (tCVResizedImage.rows * tCVResizedImage.cols));
				pIVR_Texture->PlatformData->Mips[0].BulkData.Unlock();
				pIVR_Texture->UpdateResource();

				return pIVR_Texture;
			}

		}

		//never reach here but...
		return nullptr;
		
	}

	/**
	* This function add a camera on the global camera pool.
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static void IVR_AddCamera(FIVR_CameraStruct pIVR_Camera)
	{
		//if The Camera already exist, Do nothing! Unreal creates many instances of a Single actor in Many Threads...
		for (int32 CameraID = 0; CameraID < pIVR_CameraPool.Num(); CameraID++)
		{
			if (pIVR_CameraPool[CameraID].IVR_CameraName == pIVR_Camera.IVR_CameraName)return;
		}
		pIVR_CameraPool.Add(pIVR_Camera);
		return;
	}

	/**
	* This function updates a camera on the global camera pool.
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static void IVR_UpdCamera(FIVR_CameraStruct pIVR_Camera)
	{
		//In Future this routines can be improved , like a hash map or something... :)
		for (int32 CameraID = 0; CameraID < pIVR_CameraPool.Num(); CameraID++)
		{
			//If found something, update...
			if (pIVR_CameraPool[CameraID].IVR_CameraName == pIVR_Camera.IVR_CameraName)
			{
				pIVR_CameraPool[CameraID].IVR_CameraName   = pIVR_Camera.IVR_CameraName;
				pIVR_CameraPool[CameraID].IVR_IsStabilized = pIVR_Camera.IVR_IsStabilized;
				pIVR_CameraPool[CameraID].IVR_IsEnabled    = pIVR_Camera.IVR_IsEnabled;
				pIVR_CameraPool[CameraID].IVR_FPS          = pIVR_Camera.IVR_FPS;
				return;
			}
		}
		return;
	}

	/**
	* We are updating the camera frames only when a recording finish.
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static void IVR_UpdCameraFrames(FIVR_CameraStruct pIVR_Camera)
	{
		//In Future this routines can be improved , like a hash map or something... :)
		for (int32 CameraID = 0; CameraID < pIVR_CameraPool.Num(); CameraID++)
		{
			//If found something, update...
			if (pIVR_CameraPool[CameraID].IVR_CameraName == pIVR_Camera.IVR_CameraName)
			{
				//CleanUp the Pool List
				pIVR_CameraPool[CameraID].IVR_Frames.Empty();
				for (int i = 0; i < pIVR_Camera.IVR_Frames.Num(); i++)
				{
					pIVR_CameraPool[CameraID].IVR_Frames.Add(pIVR_Camera.IVR_Frames[i]);
				}
				//CleanUp the CameraFramesPool for Sanity...
				pIVR_Camera.IVR_Frames.Empty();
				return;
			}
		}
		return;
	}

	/**
	* This is how we are informing all the cameras the state they must follow (Start Record-0 , StopRecord-1 , Iddle-2).
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static void IVR_SingleShotRecordingMessage(int pIVR_State)
	{
		pIVR_GlobalRecording = pIVR_State;
		return;
	}

	/**
	* During the tick event all cameras check the Recording state configured in the SingleShotMessage (SingleShot == ForAllCameras).
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static int IVR_CheckRecordingState()
	{
		int  AllDisabled = 0;
		
		//If we are disabling a Recording we change to iddle only when all the cameras was Disabled Properly...
		if (pIVR_GlobalRecording == 1)
		{
			//In Future this routines can be improved , like a hash map or something... :)
			for (int32 CameraID = 0; CameraID < pIVR_CameraPool.Num(); CameraID++)
			{
				//We count how many cameras are disabled
				if (!pIVR_CameraPool[CameraID].IVR_IsEnabled)AllDisabled++;
			}

			//If all the cameras are disabled we enter in the Iddle Mode...
			//Probably this will be changed when we start control individual messages...
			//By now is sufficient to mantain a good recording experince in Parallel for any number of cameras by a single Manager...
			if (AllDisabled == pIVR_CameraPool.Num())IVR_SingleShotRecordingMessage(2);
		}
		return pIVR_GlobalRecording;
	}

	/**
	* Support Function to get the Global recordings Path.
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static FString IVR_GetAppRepository()
	{
		return pIVR_FrameFilesPath;
	}

	/**
	* Support Function to Set the Global recordings Path.
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static void IVR_SetAppRepository(FString pIVR_AppPath)
	{
		pIVR_FrameFilesPath = pIVR_AppPath;
	}

	/**
	* This function will get all the camera frames and record their respective Videos.
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static bool IVR_SingleShotVideoRecording()
	{
		FString IVR_FrameFilesPath;
		FString IVR_FramesPath;

		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Starting Record the Videos...This will take a lot of Time! \n (Check Before if the System are not recording frames yet...)")));
		//Record the video for each Camera we have
		for (int32 CameraID = 0; CameraID < pIVR_CameraPool.Num(); CameraID++)
		{
			uint FrameNumber = 0;

			IVR_FrameFilesPath = FPaths::ConvertRelativePathToFull(IVR_GetAppRepository());
			IVR_FramesPath = IVR_FrameFilesPath + "/" + pIVR_CameraPool[CameraID].IVR_CameraName + "_%d.jpg";


			//Cria Video de entrada com os frames gravados.
			cv::VideoCapture cap(TCHAR_TO_UTF8(*IVR_FramesPath));

			// if not success, exit program
			if (cap.isOpened() == false)
			{
				FString Message = "There is no recording for the Camera = " + pIVR_CameraPool[CameraID].IVR_CameraName + "!";

				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
				continue;
			}

			int frame_width  = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
			int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video

			cv::Size frame_size(frame_width, frame_height);
			
			//Get The Last Frame Collected by the Camera
			//int frames_per_second = (uint)pIVR_CameraPool[CameraID].IVR_FPS;
			
			int frames_per_second=0;
			for (int i = 0; i < (int)pIVR_CameraPool[CameraID].IVR_Frames.Num(); i++)
			{
				frames_per_second += (int)pIVR_CameraPool[CameraID].IVR_Frames[i].IVR_FrameFPS;
			}
			
			frames_per_second = frames_per_second / (int)pIVR_CameraPool[CameraID].IVR_Frames.Num();

			FString VideoPath = IVR_FrameFilesPath + "/" + pIVR_CameraPool[CameraID].IVR_CameraName + "Output.mp4";

			//Create and initialize the VideoWriter object
			cv::VideoWriter oVideoWriter(TCHAR_TO_UTF8(*VideoPath),
				cv::VideoWriter::fourcc('3', 'I', 'V', 'D'),
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
				FString FileToDeletePath = "/" + pIVR_CameraPool[CameraID].IVR_CameraName + FString::Printf(TEXT("_%d.jpg"), i);
				FString FinalPath        = IVR_FrameFilesPath + FileToDeletePath;

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
	
	/**
	* This function will clean up all the camera pool and prepare the scene for a new recording.
	*/
	UFUNCTION(Category = "CameraMan|Video|Functions", BlueprintCallable)
	static void IVR_ResetCameraPool()
	{
		pIVR_CameraPool.Empty();

		pIVR_GlobalRecording = 2;
		pIVR_GlobalReset     = false;
	}
	
	//Global storage for the Video recording sessions
	static TArray<FIVR_CameraStruct>               pIVR_CameraPool;
	static int                                     pIVR_GlobalRecording;
	static bool                                    pIVR_GlobalReset;

	//Since the textures are handled by garbage collection and syncronized by the RHI we not delete it!
	static UTexture2D*                             pIVR_Texture;
	static std::unique_ptr<FUpdateTextureRegion2D> pIVR_TextureRegion;
	
	static FCriticalSection                        pIVR_WriteCriticalSection;
	static FCriticalSection                        pIVR_ReadCriticalSection;
	static FString                                 pIVR_FrameFilesPath;
	
};
