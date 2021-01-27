/******************************************************************************/
/*Project: ZOAN Editor Extensions                                             */
/*Description:                                                                */
/*The Zoan Editor Extensions is a plug-In responsible to handle the runtime   */
/*Object Customizations and Parameterization for the Zoan Runtime Production  */
/*Plug-In                                                                     */
/******************************************************************************/
/*Object Description:                                                         */
/******************************************************************************/
/*Copyright Zoan Oy, Inc. All Rights Reserved.                                */
/*Author: William D. Wolff                                                    */
/******************************************************************************/
#pragma once

#include "SlateBasics.h"
#include "PropertyCustomizationHelpers.h"
#include "ISinglePropertyView.h"
#include "IStructureDetailsView.h"
#include "KismetWidgets.h"
#include "ZED_ComboBox.h"
#include "ZED_EditBox.h"
#include "ZED_SpinBox.h"
#include "ZED_IntBox.h"
#include "ZED_FloatBox.h"
#include "ZED_ExpanderArrow.h"
#include "ZED_PointerBox.h"

#define LOCTEXT_NAMESPACE "ZED_AssetField"

/**
This class will be used by the entire ZED plug-in to design User Interfaces based in a simple
UObject object declaration.
With this Object will make possible do a better programming workflow when we start develop and
add more tools on the ZOAN VP PLUG-IN (The programmer will only need create an UObject and pass
it to the Widget... the rest of the job will be taken by the Grid Control Widget.
*/
class ZED_AssetField
{
public:
	//Field Control Attributes
	int                                  FieldOrder      ;
	FString                              FieldName       ;
	FProperty                       *    FieldProperty   ;
	UObject                         *    FieldOwner      ;
	UClass                          *    FieldStaticClass;
	UStruct                         *    FieldStruct     ;
	UScriptStruct                   *    FieldScrStruct  ;
	void                            *    FieldContainer  ; //FObjectProperty | FSoftObjectProperty | FClassProperty
	TSharedPtr<ISinglePropertyView>      FieldView       ; //Original Property Unreal Widget for the Field
	TSharedPtr<IStructureDetailsView>    FieldViewStruct ; //Original Struct Property to get Struct Wigets 

	//Field Typing Attributes
	FString                     FieldType;
	bool                        IsNative;
	bool                        IsNumber;
	bool                        IsConditional;
	bool                        IsStruct;
	bool                        IsEnum;
	bool                        IsObject;
	bool                        IsChild;
	bool                        IsCustom;

	//Field Values Attibutes
	bool                                 FieldBoolValue;
	TArray<TSharedPtr<FString> >         FieldEnumValues;
	int                                  FieldIntValue;
	long                                 FieldLongValue;
	float                                FieldFloatValue;
	double                               FieldDoubleValue;
	TArray<TSharedPtr<ZED_AssetField> >  FieldStructValues;
	FText                                FieldTextValue;
	FString                              FieldStringValue;
	UObject*                             FieldObjectValue;
    
	ZED_AssetField() {}
   ~ZED_AssetField() {}
};

#undef LOCTEXT_NAMESPACE