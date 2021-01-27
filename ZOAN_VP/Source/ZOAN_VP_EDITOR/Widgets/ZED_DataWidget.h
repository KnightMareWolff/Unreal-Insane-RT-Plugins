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

#include "ZED_ListRow.h"
#include "../Screens/ZED_ConfigurationData.h"
#include "../Style/ZED_Style.h"
#include "../ZED_WidgetBuilder.h"

#define LOCTEXT_NAMESPACE "ZED_DataWidget"

/**
This class will be refactored to a more significant object(Maybe ZED_DataGrid) responsible to store the main Grid of the Screen
Since the entire Unreal Engine uses an Data Driven Design, all the fields will follow the same design with an additional
feature: Core Independent Data Processing.
The fact of use a little "Deflection" using the Unreal Reflection System, give to us a good flexibility to design our own field Widgets
and Slate Widget structures without make use of the Detail Screen Customizations and many heavilly templatized objects(Extremelly hard to understand in a 
undocumented software... :(.
The main target of this class will be receive a realtime object, and parse all the data to be used in the Tool Tab during the ZOAN RealTime Production Plug-In
*--------------------------------------------------------------------------------------------------------------------------------------------------------------*
09/25/2020 - We try but not work yet...we still need use the detail screen customization, since we not make yet the structs data be returned as expected...
But now we are using this customizations in a new object called WidgetBuilder where we can just request the Widget Property and stor it in the Field. we will try
store the property handle and see if its possible use it instead of store Object Property Pointers.
*/
class ZED_DataWidget : public SCompoundWidget
{
public:

	/* This Macros are used to define parameters being sent to the Construct Function */
	SLATE_BEGIN_ARGS(ZED_DataWidget) {}
	SLATE_ARGUMENT(UObject * , Item)
	SLATE_END_ARGS()

	/*******************************************************/
	/*WIDGET METHODS:                                      */
	/*The methods bellow are used by Slate to make possible*/
	/*The componets work properly                          */
	/*******************************************************/
	/* Default method used by Slate to build the UI Object */
	void Construct(const FArguments& Args);
	
	/* this method will be used to handle button interactions with the UI */
	FReply             ButtonPressed();
	const FSlateBrush* GetImageBrush() const;

	/* this method are called internally by the SListView/STreeView Widget for each Field Extracted by the Reflection (FieldList)*/
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<ZED_AssetField> Item, const   TSharedRef<STableViewBase  >& OwnerTable);
	void                  OnGetChildrenForList(TSharedPtr<ZED_AssetField> Item, TArray< TSharedPtr<ZED_AssetField> >& OutChildren);
	
	/*******************************************************/
	/*VALUES METHODS:                                      */
	/*The methods bellow are used stract the property value*/
	/*of a specific type data                              */
	/*Probably will be refactored to be inside of other obj*/
	/*they are here just for the initial versions          */
	/*******************************************************/
	void  ExtractFieldHeaders(TSharedPtr<ZED_AssetField> pAssetField, int pFieldOrder, FProperty* pOwnerProperty, UObject* pFieldOwner,UClass* pFieldStaticClass , void* pFieldContainer);
	void  ExtractNumericValue(TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractAlphaNmValue(TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractIntValue    (TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractFloatValue  (TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractDoubleValue (TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractLongValue   (TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractFStringValue(TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractFTextValue  (TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractBoolValue   (TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractEnumValues  (TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractStructValues(TSharedPtr<ZED_AssetField> Item, bool isStrObj);
	void  ExtractObjectValues(TSharedPtr<ZED_AssetField> Item, bool isStrObj);

	/*******************************************************/
	/*CUSTOM METHODS:                                      */
	/*The methods bellow are custom methods used by the    */
	/*custom widget itself                                 */
	/*******************************************************/
	/*Parse all the UObject Fields in a Custom Reflection Table used to build the Widget*/
	void ReadAsset ();
	
	/********************************************************/
	/*WIDGET ATTRIBUTES                                     */
	/*All the attributes bein used in fact are a little Tree*/
	/*Component.                                            */
	/*We use it since we need show the arrows used by the   */
	/*Struct Widgets                                        */
	/********************************************************/
	/* The STreeView Widget Used to Draw the Field Grid */
    TSharedPtr< STreeView< TSharedPtr<ZED_AssetField> > > ListViewWidget;

	//The actual reflection Table (Used to parse the properties and Values Comming from an UObject)
	TArray<TSharedPtr<ZED_AssetField> > FieldList;
	TArray<TSharedPtr<ZED_AssetField> > ChildrenList;

	//The Header Row being used to draw elements
	TSharedPtr < SHeaderRow > HeaderRowDefinitions;

	//The Object received on the system Init to be included
	UObject * Item;
	UClass  * ItemStaticClass;

	//The Widget Builder used to Render Standard Controls
	FZED_WidgetBuilder pWidgetBuilder;

	//Indicates to Use Default Unreal Controls , or not.
	bool  UseCustomControls;
	
};

#undef LOCTEXT_NAMESPACE