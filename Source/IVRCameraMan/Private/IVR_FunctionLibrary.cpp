/************************************************************************/
/*Project              :IVR CameraMan - Unreal Plugin                   */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2021 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IVR_FunctionLibrary.h"

//All global objects must be decleared in the CPP file to avoid errors...

/**
 *The Camera Pool stores all the cameras included by the users in the system. 
 * It works very simple, everytime a camera will record something it register itself on the system to make possible
 * We automatically record the final videos by camera name , etc...
 * WARNING! 
 * We are not checking yet cameras with the same name so...ensure we have individual cameras(Different Names)
 */
TArray<FIVR_CameraStruct> UIVR_FunctionLibrary::pIVR_CameraPool;

/**
 *The Global Recording signal is the main place where the AI Camera Mans will look for to know if they must start to
 * record something or not.
 * WARNING!
 * In Future we can have more signals to individual cameras etc...so dont forget enable them before see the recordings.. ;)
 * 0= StartRecord 1=StopRecord 2=Iddle
 */
int  UIVR_FunctionLibrary::pIVR_GlobalRecording = 2;
bool UIVR_FunctionLibrary::pIVR_GlobalReset     = false;

/**
 *The Global Texture is the temporary place to load and update the pixels of the screen textures. 
 * to make possible save space and performance this is a transition texture.
 * WARNING!
 * In Future its possible we create one for each camera in the level ;)
 */
UTexture2D*                             UIVR_FunctionLibrary::pIVR_Texture = nullptr;
std::unique_ptr<FUpdateTextureRegion2D> UIVR_FunctionLibrary::pIVR_TextureRegion;

/**
 *The Global Critical Section makes some critical processes be ThreadSafe during a Background Process.
 * This is Critical for the runtime performance since we will record many video frames at Backgrount.
 * WARNING!
 * In Future its possible we create more critical areas to handle video streamming... ;)
 */
FCriticalSection  UIVR_FunctionLibrary::pIVR_ReadCriticalSection;
FCriticalSection  UIVR_FunctionLibrary::pIVR_WriteCriticalSection;

/**
 *The Global Frame Files Path will be used to record , read frames and generate all videos.
 * In Future its possible we create a tool to configure this parameters... ;)
 */
FString           UIVR_FunctionLibrary::pIVR_FrameFilesPath = FPaths::ProjectDir() / "Plugins" / "IVRCameraMan" / "Recordings";

