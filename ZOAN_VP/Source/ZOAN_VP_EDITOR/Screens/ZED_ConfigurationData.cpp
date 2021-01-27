// Fill out your copyright notice in the Description page of Project Settings.


#include "ZED_ConfigurationData.h"


// Sets default values
AZED_ConfigurationData::AZED_ConfigurationData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Plugin config folder location
	ZED_ConfigFilesFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / "Config" / "ZOAN_VP");

	ZED_SessionConfig.ZED_MachineName = FString("UE1");

	//	SessionConfig.CameraInputSoftPtr        = NewObject<UObject>(GetTransientPackage(), UObject::StaticClass());
	//	SessionConfig.CameraOutputSoftPtr       = NewObject<UObject>(GetTransientPackage(), UObject::StaticClass());

	//	ProjectConfig.EventListenerClassSoftPtr = NewObject<UObject>(GetTransientPackage(), UObject::StaticClass());
	//	ProjectConfig.EventManagerClassSoftPtr  = NewObject<UObject>(GetTransientPackage(), UObject::StaticClass());
	//	ProjectConfig.LevelsDataTableSoftPtr    = NewObject<UDataTable>(GetTransientPackage(), UDataTable::StaticClass());
	//	ProjectConfig.SongsDataTableSoftPtr     = NewObject<UDataTable>(GetTransientPackage(), UDataTable::StaticClass());

	ZED_ProjectConfig.ZED_UDPPort = 8888;

}

// Called when the game starts or when spawned
void AZED_ConfigurationData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZED_ConfigurationData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void* AZED_ConfigurationData::GetStructContainer(FName pPropertyName)
{
	FString tCheckedName = pPropertyName.ToString();
	void* StructPtr;

	if (tCheckedName.Contains("ZED_"))
	{
		// get a pointer to the struct instance
		FProperty* StructProp = StaticClass()->FindPropertyByName(pPropertyName);

		StructPtr = StructProp->ContainerPtrToValuePtr<void>(this);
	}
	else
	{
		StructPtr = NULL;
	}

	return StructPtr;
}

UObject * AZED_ConfigurationData::GetStructObject(FName pPropertyName)
{
	FString  tCheckedName = pPropertyName.ToString();
	UObject* ObjectPtr;

	if (tCheckedName.Contains("ZED_"))
	{
		// get a pointer to the struct instance
		FProperty* StructProp = StaticClass()->FindPropertyByName(pPropertyName);

		ObjectPtr = StructProp->ContainerPtrToValuePtr<UObject>(this);
	}
	else
	{
		ObjectPtr = NULL;
	}

	return ObjectPtr;
}