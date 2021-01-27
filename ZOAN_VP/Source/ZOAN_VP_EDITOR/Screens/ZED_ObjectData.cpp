// Fill out your copyright notice in the Description page of Project Settings.


#include "ZED_ObjectData.h"

void* UZED_ObjectData::GetStructContainer(FName pPropertyName)
{
	FString tCheckedName = pPropertyName.ToString();
	void* StructPtr;

	// get a pointer to the struct instance
	FProperty* StructProp = StaticClass()->FindPropertyByName(pPropertyName);

	StructPtr = StructProp->ContainerPtrToValuePtr<void>(this);

	return StructPtr;
}

UObject* UZED_ObjectData::GetStructObject(FName pPropertyName)
{
	FString  tCheckedName = pPropertyName.ToString();
	UObject* ObjectPtr;

	// get a pointer to the struct instance
	FProperty* StructProp = StaticClass()->FindPropertyByName(pPropertyName);

	ObjectPtr = StructProp->ContainerPtrToValuePtr<UObject>(this);

	return ObjectPtr;
}

