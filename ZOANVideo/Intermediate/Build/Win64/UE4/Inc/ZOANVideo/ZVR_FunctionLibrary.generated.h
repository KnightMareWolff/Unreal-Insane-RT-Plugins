// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FZVR_CameraStruct;
class UTexture2D;
struct FColor;
class USceneCaptureComponent2D;
struct FLinearColor;
class UTextureRenderTarget2D;
#ifdef ZOANVIDEO_ZVR_FunctionLibrary_generated_h
#error "ZVR_FunctionLibrary.generated.h already included, missing '#pragma once' in ZVR_FunctionLibrary.h"
#endif
#define ZOANVIDEO_ZVR_FunctionLibrary_generated_h

#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_117_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics; \
	ZOANVIDEO_API static class UScriptStruct* StaticStruct();


template<> ZOANVIDEO_API UScriptStruct* StaticStruct<struct FZVR_CameraStruct>();

#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_89_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics; \
	ZOANVIDEO_API static class UScriptStruct* StaticStruct();


template<> ZOANVIDEO_API UScriptStruct* StaticStruct<struct FZVR_CameraMessage>();

#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_61_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics; \
	ZOANVIDEO_API static class UScriptStruct* StaticStruct();


template<> ZOANVIDEO_API UScriptStruct* StaticStruct<struct FZVR_CameraFrame>();

#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_SPARSE_DATA
#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execZVR_SingleShotVideoRecording); \
	DECLARE_FUNCTION(execZVR_SetAppRepository); \
	DECLARE_FUNCTION(execZVR_GetAppRepository); \
	DECLARE_FUNCTION(execZVR_CheckRecordingState); \
	DECLARE_FUNCTION(execZVR_SingleShotRecordingMessage); \
	DECLARE_FUNCTION(execZVR_UpdCameraFrames); \
	DECLARE_FUNCTION(execZVR_UpdCamera); \
	DECLARE_FUNCTION(execZVR_AddCamera); \
	DECLARE_FUNCTION(execZVR_CVLoadFrame); \
	DECLARE_FUNCTION(execZVR_LoadFrame); \
	DECLARE_FUNCTION(execZVR_AsyncRecordFrame); \
	DECLARE_FUNCTION(execZVR_LoadTexture); \
	DECLARE_FUNCTION(execZVR_TakeSnapshot); \
	DECLARE_FUNCTION(execZVR_CreateTextureRenderTarget2D);


#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execZVR_SingleShotVideoRecording); \
	DECLARE_FUNCTION(execZVR_SetAppRepository); \
	DECLARE_FUNCTION(execZVR_GetAppRepository); \
	DECLARE_FUNCTION(execZVR_CheckRecordingState); \
	DECLARE_FUNCTION(execZVR_SingleShotRecordingMessage); \
	DECLARE_FUNCTION(execZVR_UpdCameraFrames); \
	DECLARE_FUNCTION(execZVR_UpdCamera); \
	DECLARE_FUNCTION(execZVR_AddCamera); \
	DECLARE_FUNCTION(execZVR_CVLoadFrame); \
	DECLARE_FUNCTION(execZVR_LoadFrame); \
	DECLARE_FUNCTION(execZVR_AsyncRecordFrame); \
	DECLARE_FUNCTION(execZVR_LoadTexture); \
	DECLARE_FUNCTION(execZVR_TakeSnapshot); \
	DECLARE_FUNCTION(execZVR_CreateTextureRenderTarget2D);


#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUZVR_FunctionLibrary(); \
	friend struct Z_Construct_UClass_UZVR_FunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UZVR_FunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ZOANVideo"), NO_API) \
	DECLARE_SERIALIZER(UZVR_FunctionLibrary)


#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_INCLASS \
private: \
	static void StaticRegisterNativesUZVR_FunctionLibrary(); \
	friend struct Z_Construct_UClass_UZVR_FunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UZVR_FunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ZOANVideo"), NO_API) \
	DECLARE_SERIALIZER(UZVR_FunctionLibrary)


#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UZVR_FunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UZVR_FunctionLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UZVR_FunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UZVR_FunctionLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UZVR_FunctionLibrary(UZVR_FunctionLibrary&&); \
	NO_API UZVR_FunctionLibrary(const UZVR_FunctionLibrary&); \
public:


#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UZVR_FunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UZVR_FunctionLibrary(UZVR_FunctionLibrary&&); \
	NO_API UZVR_FunctionLibrary(const UZVR_FunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UZVR_FunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UZVR_FunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UZVR_FunctionLibrary)


#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_140_PROLOG
#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_SPARSE_DATA \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_RPC_WRAPPERS \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_INCLASS \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_SPARSE_DATA \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h_143_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ZOANVIDEO_API UClass* StaticClass<class UZVR_FunctionLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_ZOANVideo_Source_ZOANVideo_Public_ZVR_FunctionLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
