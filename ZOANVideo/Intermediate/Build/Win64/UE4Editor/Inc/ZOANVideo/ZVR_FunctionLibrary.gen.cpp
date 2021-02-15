// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ZOANVideo/Public/ZVR_FunctionLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeZVR_FunctionLibrary() {}
// Cross Module References
	ZOANVIDEO_API UScriptStruct* Z_Construct_UScriptStruct_FZVR_CameraStruct();
	UPackage* Z_Construct_UPackage__Script_ZOANVideo();
	ZOANVIDEO_API UScriptStruct* Z_Construct_UScriptStruct_FZVR_CameraFrame();
	ZOANVIDEO_API UScriptStruct* Z_Construct_UScriptStruct_FZVR_CameraMessage();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ZOANVIDEO_API UClass* Z_Construct_UClass_UZVR_FunctionLibrary_NoRegister();
	ZOANVIDEO_API UClass* Z_Construct_UClass_UZVR_FunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneCaptureComponent2D_NoRegister();
// End Cross Module References
class UScriptStruct* FZVR_CameraStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ZOANVIDEO_API uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FZVR_CameraStruct, Z_Construct_UPackage__Script_ZOANVideo(), TEXT("ZVR_CameraStruct"), sizeof(FZVR_CameraStruct), Get_Z_Construct_UScriptStruct_FZVR_CameraStruct_Hash());
	}
	return Singleton;
}
template<> ZOANVIDEO_API UScriptStruct* StaticStruct<FZVR_CameraStruct>()
{
	return FZVR_CameraStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FZVR_CameraStruct(FZVR_CameraStruct::StaticStruct, TEXT("/Script/ZOANVideo"), TEXT("ZVR_CameraStruct"), false, nullptr, nullptr);
static struct FScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraStruct
{
	FScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraStruct()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("ZVR_CameraStruct")),new UScriptStruct::TCppStructOps<FZVR_CameraStruct>);
	}
} ScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraStruct;
	struct Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_Frames_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ZVR_Frames;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ZVR_Frames_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_IsEnabled_MetaData[];
#endif
		static void NewProp_ZVR_IsEnabled_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ZVR_IsEnabled;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_IsStabilized_MetaData[];
#endif
		static void NewProp_ZVR_IsStabilized_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ZVR_IsStabilized;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_FPS_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ZVR_FPS;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_CameraName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ZVR_CameraName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n* Represent a camera on the global camera storage.\n* This struct are used to control video recordings without need access the real cameras\n* Inside of the enviroment and Collect specific recording Frames.\n*/" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Represent a camera on the global camera storage.\nThis struct are used to control video recordings without need access the real cameras\nInside of the enviroment and Collect specific recording Frames." },
	};
#endif
	void* Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FZVR_CameraStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_Frames_MetaData[] = {
		{ "Category", "ZVR_CameraStruct" },
		{ "Comment", "//If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load).\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load)." },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_Frames = { "ZVR_Frames", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraStruct, ZVR_Frames), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_Frames_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_Frames_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_Frames_Inner = { "ZVR_Frames", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FZVR_CameraFrame, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsEnabled_MetaData[] = {
		{ "Category", "ZVR_CameraStruct" },
		{ "Comment", "//Flag to Know the Camera State.(Take Care to not enable it in the wrong time!)\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Flag to Know the Camera State.(Take Care to not enable it in the wrong time!)" },
	};
#endif
	void Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsEnabled_SetBit(void* Obj)
	{
		((FZVR_CameraStruct*)Obj)->ZVR_IsEnabled = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsEnabled = { "ZVR_IsEnabled", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FZVR_CameraStruct), &Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsEnabled_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsEnabled_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsEnabled_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsStabilized_MetaData[] = {
		{ "Category", "ZVR_CameraStruct" },
		{ "Comment", "//If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load).\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "If true this camera record Stabilized Frames on the HD.(Used To know the correct files to load)." },
	};
#endif
	void Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsStabilized_SetBit(void* Obj)
	{
		((FZVR_CameraStruct*)Obj)->ZVR_IsStabilized = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsStabilized = { "ZVR_IsStabilized", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FZVR_CameraStruct), &Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsStabilized_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsStabilized_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsStabilized_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_FPS_MetaData[] = {
		{ "Category", "ZVR_CameraStruct" },
		{ "Comment", "//Store the Last FPS Collected by the camera recordings\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Store the Last FPS Collected by the camera recordings" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_FPS = { "ZVR_FPS", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraStruct, ZVR_FPS), METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_FPS_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_FPS_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_CameraName_MetaData[] = {
		{ "Category", "ZVR_CameraStruct" },
		{ "Comment", "//Store the real camera name\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Store the real camera name" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_CameraName = { "ZVR_CameraName", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraStruct, ZVR_CameraName), METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_CameraName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_CameraName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_Frames,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_Frames_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsEnabled,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_IsStabilized,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_FPS,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::NewProp_ZVR_CameraName,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_ZOANVideo,
		nullptr,
		&NewStructOps,
		"ZVR_CameraStruct",
		sizeof(FZVR_CameraStruct),
		alignof(FZVR_CameraStruct),
		Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FZVR_CameraStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_ZOANVideo();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ZVR_CameraStruct"), sizeof(FZVR_CameraStruct), Get_Z_Construct_UScriptStruct_FZVR_CameraStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FZVR_CameraStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraStruct_Hash() { return 335560986U; }
class UScriptStruct* FZVR_CameraMessage::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ZOANVIDEO_API uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraMessage_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FZVR_CameraMessage, Z_Construct_UPackage__Script_ZOANVideo(), TEXT("ZVR_CameraMessage"), sizeof(FZVR_CameraMessage), Get_Z_Construct_UScriptStruct_FZVR_CameraMessage_Hash());
	}
	return Singleton;
}
template<> ZOANVIDEO_API UScriptStruct* StaticStruct<FZVR_CameraMessage>()
{
	return FZVR_CameraMessage::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FZVR_CameraMessage(FZVR_CameraMessage::StaticStruct, TEXT("/Script/ZOANVideo"), TEXT("ZVR_CameraMessage"), false, nullptr, nullptr);
static struct FScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraMessage
{
	FScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraMessage()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("ZVR_CameraMessage")),new UScriptStruct::TCppStructOps<FZVR_CameraMessage>);
	}
} ScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraMessage;
	struct Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_Scale_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ZVR_Scale;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_Rotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ZVR_Rotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_Position_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ZVR_Position;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_Action_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ZVR_Action;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_CameraName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ZVR_CameraName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n* Represent a message to a camera on the global camera storage.\n* This struct are used to control video recordings without need access the real cameras\n* Inside of the enviroment and Collect specific recording Frames.\n*/" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Represent a message to a camera on the global camera storage.\nThis struct are used to control video recordings without need access the real cameras\nInside of the enviroment and Collect specific recording Frames." },
	};
#endif
	void* Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FZVR_CameraMessage>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Scale_MetaData[] = {
		{ "Category", "ZVR_CameraMessage" },
		{ "Comment", "//Reference Scale for the Action.\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Reference Scale for the Action." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Scale = { "ZVR_Scale", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraMessage, ZVR_Scale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Scale_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Scale_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Rotation_MetaData[] = {
		{ "Category", "ZVR_CameraMessage" },
		{ "Comment", "//Reference Rotation for the Action.\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Reference Rotation for the Action." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Rotation = { "ZVR_Rotation", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraMessage, ZVR_Rotation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Rotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Rotation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Position_MetaData[] = {
		{ "Category", "ZVR_CameraMessage" },
		{ "Comment", "//Reference Position for the Action.\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Reference Position for the Action." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Position = { "ZVR_Position", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraMessage, ZVR_Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Position_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Position_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Action_MetaData[] = {
		{ "Category", "ZVR_CameraMessage" },
		{ "Comment", "//Store the Min FPS Collected by the camera recordings\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Store the Min FPS Collected by the camera recordings" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Action = { "ZVR_Action", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraMessage, ZVR_Action), METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Action_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Action_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_CameraName_MetaData[] = {
		{ "Category", "ZVR_CameraMessage" },
		{ "Comment", "//Store the real camera name\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Store the real camera name" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_CameraName = { "ZVR_CameraName", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraMessage, ZVR_CameraName), METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_CameraName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_CameraName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Scale,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Rotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Position,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_Action,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::NewProp_ZVR_CameraName,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_ZOANVideo,
		nullptr,
		&NewStructOps,
		"ZVR_CameraMessage",
		sizeof(FZVR_CameraMessage),
		alignof(FZVR_CameraMessage),
		Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FZVR_CameraMessage()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraMessage_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_ZOANVideo();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ZVR_CameraMessage"), sizeof(FZVR_CameraMessage), Get_Z_Construct_UScriptStruct_FZVR_CameraMessage_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FZVR_CameraMessage_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraMessage_Hash() { return 3868238154U; }
class UScriptStruct* FZVR_CameraFrame::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ZOANVIDEO_API uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraFrame_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FZVR_CameraFrame, Z_Construct_UPackage__Script_ZOANVideo(), TEXT("ZVR_CameraFrame"), sizeof(FZVR_CameraFrame), Get_Z_Construct_UScriptStruct_FZVR_CameraFrame_Hash());
	}
	return Singleton;
}
template<> ZOANVIDEO_API UScriptStruct* StaticStruct<FZVR_CameraFrame>()
{
	return FZVR_CameraFrame::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FZVR_CameraFrame(FZVR_CameraFrame::StaticStruct, TEXT("/Script/ZOANVideo"), TEXT("ZVR_CameraFrame"), false, nullptr, nullptr);
static struct FScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraFrame
{
	FScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraFrame()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("ZVR_CameraFrame")),new UScriptStruct::TCppStructOps<FZVR_CameraFrame>);
	}
} ScriptStruct_ZOANVideo_StaticRegisterNativesFZVR_CameraFrame;
	struct Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_Scale_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ZVR_Scale;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_Rotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ZVR_Rotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_Position_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ZVR_Position;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_FrameFPS_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ZVR_FrameFPS;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZVR_CameraName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ZVR_CameraName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n* Represent a camera frame on the global camera storage.\n* This struct are used to control video recordings without need access the real cameras\n* Inside of the enviroment and Collect specific recording Frames.\n*/" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Represent a camera frame on the global camera storage.\nThis struct are used to control video recordings without need access the real cameras\nInside of the enviroment and Collect specific recording Frames." },
	};
#endif
	void* Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FZVR_CameraFrame>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Scale_MetaData[] = {
		{ "Category", "ZVR_CameraFrame" },
		{ "Comment", "//Reference Scale for the Frame.\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Reference Scale for the Frame." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Scale = { "ZVR_Scale", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraFrame, ZVR_Scale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Scale_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Scale_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Rotation_MetaData[] = {
		{ "Category", "ZVR_CameraFrame" },
		{ "Comment", "//Reference Rotation for the Frame.\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Reference Rotation for the Frame." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Rotation = { "ZVR_Rotation", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraFrame, ZVR_Rotation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Rotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Rotation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Position_MetaData[] = {
		{ "Category", "ZVR_CameraFrame" },
		{ "Comment", "//Reference Position for the Frame.\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Reference Position for the Frame." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Position = { "ZVR_Position", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraFrame, ZVR_Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Position_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Position_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_FrameFPS_MetaData[] = {
		{ "Category", "ZVR_CameraFrame" },
		{ "Comment", "//Store the Min FPS Collected by the camera recordings\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Store the Min FPS Collected by the camera recordings" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_FrameFPS = { "ZVR_FrameFPS", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraFrame, ZVR_FrameFPS), METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_FrameFPS_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_FrameFPS_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_CameraName_MetaData[] = {
		{ "Category", "ZVR_CameraFrame" },
		{ "Comment", "//Store the real camera name\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "Store the real camera name" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_CameraName = { "ZVR_CameraName", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FZVR_CameraFrame, ZVR_CameraName), METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_CameraName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_CameraName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Scale,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Rotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_Position,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_FrameFPS,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::NewProp_ZVR_CameraName,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_ZOANVideo,
		nullptr,
		&NewStructOps,
		"ZVR_CameraFrame",
		sizeof(FZVR_CameraFrame),
		alignof(FZVR_CameraFrame),
		Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FZVR_CameraFrame()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraFrame_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_ZOANVideo();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ZVR_CameraFrame"), sizeof(FZVR_CameraFrame), Get_Z_Construct_UScriptStruct_FZVR_CameraFrame_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FZVR_CameraFrame_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FZVR_CameraFrame_Hash() { return 3948323839U; }
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_SingleShotVideoRecording)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UZVR_FunctionLibrary::ZVR_SingleShotVideoRecording();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_SetAppRepository)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_pZVR_AppPath);
		P_FINISH;
		P_NATIVE_BEGIN;
		UZVR_FunctionLibrary::ZVR_SetAppRepository(Z_Param_pZVR_AppPath);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_GetAppRepository)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UZVR_FunctionLibrary::ZVR_GetAppRepository();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_CheckRecordingState)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UZVR_FunctionLibrary::ZVR_CheckRecordingState();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_SingleShotRecordingMessage)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_pZVR_State);
		P_FINISH;
		P_NATIVE_BEGIN;
		UZVR_FunctionLibrary::ZVR_SingleShotRecordingMessage(Z_Param_pZVR_State);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_UpdCameraFrames)
	{
		P_GET_STRUCT(FZVR_CameraStruct,Z_Param_pZVR_Camera);
		P_FINISH;
		P_NATIVE_BEGIN;
		UZVR_FunctionLibrary::ZVR_UpdCameraFrames(Z_Param_pZVR_Camera);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_UpdCamera)
	{
		P_GET_STRUCT(FZVR_CameraStruct,Z_Param_pZVR_Camera);
		P_FINISH;
		P_NATIVE_BEGIN;
		UZVR_FunctionLibrary::ZVR_UpdCamera(Z_Param_pZVR_Camera);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_AddCamera)
	{
		P_GET_STRUCT(FZVR_CameraStruct,Z_Param_pZVR_Camera);
		P_FINISH;
		P_NATIVE_BEGIN;
		UZVR_FunctionLibrary::ZVR_AddCamera(Z_Param_pZVR_Camera);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_CVLoadFrame)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_pZVR_CameraName);
		P_GET_PROPERTY(FIntProperty,Z_Param_pZVR_Frame);
		P_GET_UBOOL_REF(Z_Param_Out_IsValid);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutWidth);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutHeight);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UTexture2D**)Z_Param__Result=UZVR_FunctionLibrary::ZVR_CVLoadFrame(Z_Param_pZVR_CameraName,Z_Param_pZVR_Frame,Z_Param_Out_IsValid,Z_Param_Out_OutWidth,Z_Param_Out_OutHeight);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_LoadFrame)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_pZVR_CameraName);
		P_GET_PROPERTY(FIntProperty,Z_Param_pZVR_Frame);
		P_GET_UBOOL_REF(Z_Param_Out_IsValid);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutWidth);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutHeight);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UTexture2D**)Z_Param__Result=UZVR_FunctionLibrary::ZVR_LoadFrame(Z_Param_pZVR_CameraName,Z_Param_pZVR_Frame,Z_Param_Out_IsValid,Z_Param_Out_OutWidth,Z_Param_Out_OutHeight);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_AsyncRecordFrame)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_pZVR_CameraName);
		P_GET_PROPERTY(FIntProperty,Z_Param_pZVR_Frame);
		P_GET_TARRAY(FColor,Z_Param_RawPixels);
		P_GET_PROPERTY(FIntProperty,Z_Param_Width);
		P_GET_PROPERTY(FIntProperty,Z_Param_Height);
		P_GET_STRUCT(FColor,Z_Param_ClearFColour);
		P_FINISH;
		P_NATIVE_BEGIN;
		UZVR_FunctionLibrary::ZVR_AsyncRecordFrame(Z_Param_pZVR_CameraName,Z_Param_pZVR_Frame,Z_Param_RawPixels,Z_Param_Width,Z_Param_Height,Z_Param_ClearFColour);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_LoadTexture)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ImagePath);
		P_GET_UBOOL_REF(Z_Param_Out_IsValid);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutWidth);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutHeight);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UTexture2D**)Z_Param__Result=UZVR_FunctionLibrary::ZVR_LoadTexture(Z_Param_ImagePath,Z_Param_Out_IsValid,Z_Param_Out_OutWidth,Z_Param_Out_OutHeight);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_TakeSnapshot)
	{
		P_GET_OBJECT(USceneCaptureComponent2D,Z_Param_Target);
		P_GET_PROPERTY(FStrProperty,Z_Param_ImagePath);
		P_GET_STRUCT(FLinearColor,Z_Param_ClearColour);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UZVR_FunctionLibrary::ZVR_TakeSnapshot(Z_Param_Target,Z_Param_ImagePath,Z_Param_ClearColour);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UZVR_FunctionLibrary::execZVR_CreateTextureRenderTarget2D)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Width);
		P_GET_PROPERTY(FIntProperty,Z_Param_Height);
		P_GET_STRUCT(FLinearColor,Z_Param_ClearColor);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Gamma);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UTextureRenderTarget2D**)Z_Param__Result=UZVR_FunctionLibrary::ZVR_CreateTextureRenderTarget2D(Z_Param_Width,Z_Param_Height,Z_Param_ClearColor,Z_Param_Gamma);
		P_NATIVE_END;
	}
	void UZVR_FunctionLibrary::StaticRegisterNativesUZVR_FunctionLibrary()
	{
		UClass* Class = UZVR_FunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ZVR_AddCamera", &UZVR_FunctionLibrary::execZVR_AddCamera },
			{ "ZVR_AsyncRecordFrame", &UZVR_FunctionLibrary::execZVR_AsyncRecordFrame },
			{ "ZVR_CheckRecordingState", &UZVR_FunctionLibrary::execZVR_CheckRecordingState },
			{ "ZVR_CreateTextureRenderTarget2D", &UZVR_FunctionLibrary::execZVR_CreateTextureRenderTarget2D },
			{ "ZVR_CVLoadFrame", &UZVR_FunctionLibrary::execZVR_CVLoadFrame },
			{ "ZVR_GetAppRepository", &UZVR_FunctionLibrary::execZVR_GetAppRepository },
			{ "ZVR_LoadFrame", &UZVR_FunctionLibrary::execZVR_LoadFrame },
			{ "ZVR_LoadTexture", &UZVR_FunctionLibrary::execZVR_LoadTexture },
			{ "ZVR_SetAppRepository", &UZVR_FunctionLibrary::execZVR_SetAppRepository },
			{ "ZVR_SingleShotRecordingMessage", &UZVR_FunctionLibrary::execZVR_SingleShotRecordingMessage },
			{ "ZVR_SingleShotVideoRecording", &UZVR_FunctionLibrary::execZVR_SingleShotVideoRecording },
			{ "ZVR_TakeSnapshot", &UZVR_FunctionLibrary::execZVR_TakeSnapshot },
			{ "ZVR_UpdCamera", &UZVR_FunctionLibrary::execZVR_UpdCamera },
			{ "ZVR_UpdCameraFrames", &UZVR_FunctionLibrary::execZVR_UpdCameraFrames },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_AddCamera_Parms
		{
			FZVR_CameraStruct pZVR_Camera;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_pZVR_Camera;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::NewProp_pZVR_Camera = { "pZVR_Camera", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_AddCamera_Parms, pZVR_Camera), Z_Construct_UScriptStruct_FZVR_CameraStruct, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::NewProp_pZVR_Camera,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_AddCamera", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_AddCamera_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_AsyncRecordFrame_Parms
		{
			FString pZVR_CameraName;
			int32 pZVR_Frame;
			TArray<FColor> RawPixels;
			int32 Width;
			int32 Height;
			FColor ClearFColour;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ClearFColour;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Height;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Width;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RawPixels;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RawPixels_Inner;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_pZVR_Frame;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_pZVR_CameraName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_ClearFColour = { "ClearFColour", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_AsyncRecordFrame_Parms, ClearFColour), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_AsyncRecordFrame_Parms, Height), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_AsyncRecordFrame_Parms, Width), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_RawPixels = { "RawPixels", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_AsyncRecordFrame_Parms, RawPixels), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_RawPixels_Inner = { "RawPixels", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_pZVR_Frame = { "pZVR_Frame", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_AsyncRecordFrame_Parms, pZVR_Frame), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_pZVR_CameraName = { "pZVR_CameraName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_AsyncRecordFrame_Parms, pZVR_CameraName), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_ClearFColour,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_Height,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_Width,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_RawPixels,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_RawPixels_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_pZVR_Frame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::NewProp_pZVR_CameraName,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_AsyncRecordFrame", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_AsyncRecordFrame_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_CheckRecordingState_Parms
		{
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CheckRecordingState_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_CheckRecordingState", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_CheckRecordingState_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_CreateTextureRenderTarget2D_Parms
		{
			int32 Width;
			int32 Height;
			FLinearColor ClearColor;
			float Gamma;
			UTextureRenderTarget2D* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Gamma;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ClearColor;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Height;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Width;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CreateTextureRenderTarget2D_Parms, ReturnValue), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_Gamma = { "Gamma", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CreateTextureRenderTarget2D_Parms, Gamma), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_ClearColor = { "ClearColor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CreateTextureRenderTarget2D_Parms, ClearColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CreateTextureRenderTarget2D_Parms, Height), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CreateTextureRenderTarget2D_Parms, Width), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_Gamma,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_ClearColor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_Height,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::NewProp_Width,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "CPP_Default_ClearColor", "(R=1.000000,G=1.000000,B=1.000000,A=1.000000)" },
		{ "CPP_Default_Gamma", "1.000000" },
		{ "CPP_Default_Height", "256" },
		{ "CPP_Default_Width", "256" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_CreateTextureRenderTarget2D", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_CreateTextureRenderTarget2D_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms
		{
			FString pZVR_CameraName;
			int32 pZVR_Frame;
			bool IsValid;
			int32 OutWidth;
			int32 OutHeight;
			UTexture2D* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OutHeight;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OutWidth;
		static void NewProp_IsValid_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsValid;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_pZVR_Frame;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_pZVR_CameraName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_OutHeight = { "OutHeight", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms, OutHeight), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_OutWidth = { "OutWidth", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms, OutWidth), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_IsValid_SetBit(void* Obj)
	{
		((ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms*)Obj)->IsValid = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_IsValid = { "IsValid", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms), &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_IsValid_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_pZVR_Frame = { "pZVR_Frame", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms, pZVR_Frame), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_pZVR_CameraName = { "pZVR_CameraName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms, pZVR_CameraName), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_OutHeight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_OutWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_IsValid,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_pZVR_Frame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::NewProp_pZVR_CameraName,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_CVLoadFrame", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_CVLoadFrame_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_GetAppRepository_Parms
		{
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_GetAppRepository_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_GetAppRepository", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_GetAppRepository_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms
		{
			FString pZVR_CameraName;
			int32 pZVR_Frame;
			bool IsValid;
			int32 OutWidth;
			int32 OutHeight;
			UTexture2D* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OutHeight;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OutWidth;
		static void NewProp_IsValid_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsValid;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_pZVR_Frame;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_pZVR_CameraName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_OutHeight = { "OutHeight", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms, OutHeight), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_OutWidth = { "OutWidth", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms, OutWidth), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_IsValid_SetBit(void* Obj)
	{
		((ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms*)Obj)->IsValid = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_IsValid = { "IsValid", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms), &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_IsValid_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_pZVR_Frame = { "pZVR_Frame", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms, pZVR_Frame), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_pZVR_CameraName = { "pZVR_CameraName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms, pZVR_CameraName), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_OutHeight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_OutWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_IsValid,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_pZVR_Frame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::NewProp_pZVR_CameraName,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_LoadFrame", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_LoadFrame_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_LoadTexture_Parms
		{
			FString ImagePath;
			bool IsValid;
			int32 OutWidth;
			int32 OutHeight;
			UTexture2D* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OutHeight;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OutWidth;
		static void NewProp_IsValid_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsValid;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ImagePath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ImagePath;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadTexture_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_OutHeight = { "OutHeight", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadTexture_Parms, OutHeight), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_OutWidth = { "OutWidth", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadTexture_Parms, OutWidth), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_IsValid_SetBit(void* Obj)
	{
		((ZVR_FunctionLibrary_eventZVR_LoadTexture_Parms*)Obj)->IsValid = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_IsValid = { "IsValid", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ZVR_FunctionLibrary_eventZVR_LoadTexture_Parms), &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_IsValid_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_ImagePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_ImagePath = { "ImagePath", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_LoadTexture_Parms, ImagePath), METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_ImagePath_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_ImagePath_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_OutHeight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_OutWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_IsValid,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::NewProp_ImagePath,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_LoadTexture", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_LoadTexture_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_SetAppRepository_Parms
		{
			FString pZVR_AppPath;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_pZVR_AppPath;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::NewProp_pZVR_AppPath = { "pZVR_AppPath", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_SetAppRepository_Parms, pZVR_AppPath), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::NewProp_pZVR_AppPath,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_SetAppRepository", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_SetAppRepository_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_SingleShotRecordingMessage_Parms
		{
			int32 pZVR_State;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_pZVR_State;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::NewProp_pZVR_State = { "pZVR_State", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_SingleShotRecordingMessage_Parms, pZVR_State), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::NewProp_pZVR_State,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_SingleShotRecordingMessage", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_SingleShotRecordingMessage_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_SingleShotVideoRecording_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((ZVR_FunctionLibrary_eventZVR_SingleShotVideoRecording_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ZVR_FunctionLibrary_eventZVR_SingleShotVideoRecording_Parms), &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "Comment", "//This function will get all the camera frames and record their respective Videos\n" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
		{ "ToolTip", "This function will get all the camera frames and record their respective Videos" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_SingleShotVideoRecording", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_SingleShotVideoRecording_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_TakeSnapshot_Parms
		{
			USceneCaptureComponent2D* Target;
			FString ImagePath;
			FLinearColor ClearColour;
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ClearColour_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ClearColour;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ImagePath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ImagePath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Target_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Target;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((ZVR_FunctionLibrary_eventZVR_TakeSnapshot_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ZVR_FunctionLibrary_eventZVR_TakeSnapshot_Parms), &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ClearColour_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ClearColour = { "ClearColour", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_TakeSnapshot_Parms, ClearColour), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ClearColour_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ClearColour_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ImagePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ImagePath = { "ImagePath", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_TakeSnapshot_Parms, ImagePath), METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ImagePath_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ImagePath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_Target_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_TakeSnapshot_Parms, Target), Z_Construct_UClass_USceneCaptureComponent2D_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_Target_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_Target_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ClearColour,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_ImagePath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::NewProp_Target,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_TakeSnapshot", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_TakeSnapshot_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_UpdCamera_Parms
		{
			FZVR_CameraStruct pZVR_Camera;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_pZVR_Camera;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::NewProp_pZVR_Camera = { "pZVR_Camera", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_UpdCamera_Parms, pZVR_Camera), Z_Construct_UScriptStruct_FZVR_CameraStruct, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::NewProp_pZVR_Camera,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_UpdCamera", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_UpdCamera_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics
	{
		struct ZVR_FunctionLibrary_eventZVR_UpdCameraFrames_Parms
		{
			FZVR_CameraStruct pZVR_Camera;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_pZVR_Camera;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::NewProp_pZVR_Camera = { "pZVR_Camera", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZVR_FunctionLibrary_eventZVR_UpdCameraFrames_Parms, pZVR_Camera), Z_Construct_UScriptStruct_FZVR_CameraStruct, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::NewProp_pZVR_Camera,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::Function_MetaDataParams[] = {
		{ "Category", "ZOAN|Video|Functions" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UZVR_FunctionLibrary, nullptr, "ZVR_UpdCameraFrames", nullptr, nullptr, sizeof(ZVR_FunctionLibrary_eventZVR_UpdCameraFrames_Parms), Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UZVR_FunctionLibrary_NoRegister()
	{
		return UZVR_FunctionLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UZVR_FunctionLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UZVR_FunctionLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_ZOANVideo,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UZVR_FunctionLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AddCamera, "ZVR_AddCamera" }, // 2919378654
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_AsyncRecordFrame, "ZVR_AsyncRecordFrame" }, // 3431412079
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CheckRecordingState, "ZVR_CheckRecordingState" }, // 2380997157
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CreateTextureRenderTarget2D, "ZVR_CreateTextureRenderTarget2D" }, // 689820858
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_CVLoadFrame, "ZVR_CVLoadFrame" }, // 3992578859
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_GetAppRepository, "ZVR_GetAppRepository" }, // 1200632268
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadFrame, "ZVR_LoadFrame" }, // 102861078
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_LoadTexture, "ZVR_LoadTexture" }, // 2245359305
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SetAppRepository, "ZVR_SetAppRepository" }, // 3150009156
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotRecordingMessage, "ZVR_SingleShotRecordingMessage" }, // 1226814499
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_SingleShotVideoRecording, "ZVR_SingleShotVideoRecording" }, // 1427178686
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_TakeSnapshot, "ZVR_TakeSnapshot" }, // 3531832910
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCamera, "ZVR_UpdCamera" }, // 1520627251
		{ &Z_Construct_UFunction_UZVR_FunctionLibrary_ZVR_UpdCameraFrames, "ZVR_UpdCameraFrames" }, // 2231501744
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UZVR_FunctionLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "ZVR_FunctionLibrary.h" },
		{ "ModuleRelativePath", "Public/ZVR_FunctionLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UZVR_FunctionLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UZVR_FunctionLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UZVR_FunctionLibrary_Statics::ClassParams = {
		&UZVR_FunctionLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UZVR_FunctionLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UZVR_FunctionLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UZVR_FunctionLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UZVR_FunctionLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UZVR_FunctionLibrary, 421900663);
	template<> ZOANVIDEO_API UClass* StaticClass<UZVR_FunctionLibrary>()
	{
		return UZVR_FunctionLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UZVR_FunctionLibrary(Z_Construct_UClass_UZVR_FunctionLibrary, &UZVR_FunctionLibrary::StaticClass, TEXT("/Script/ZOANVideo"), TEXT("UZVR_FunctionLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UZVR_FunctionLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
