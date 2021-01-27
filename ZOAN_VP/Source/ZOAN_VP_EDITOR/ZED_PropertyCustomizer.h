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

#include "Screens/ZED_ObjectData.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "IPropertyTypeCustomization.h"

/********************************************************************************/
/*The Customizer Field Class will be used to translate the information in the   */
/*Reflection System to a modifyable value during the tool functionality.        */
/*Sadly there is no easy way to do that becouse the data of the fields can be   */
/*managed thru IProperty Handles , but the identifications of the properies are */
/*stored inside of all different Object Properies.                              */
/*To make possible "link" the IProperty Handle with the correct Property we need*/
/*The Customyzer Field...                                                       */
/********************************************************************************/
class ZED_CustomizerField
{
public:
	//Field Control Attributes
	int                                  FieldOrder         ;
	FString                              FieldName          ;
	FProperty                          * FieldProperty      ;
	UObject                            * FieldOwner         ;
	void                               * FieldContainer     ;
	
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

	 ZED_CustomizerField() {}
	~ZED_CustomizerField() {}
};

/********************************************************************************/
/*The Detail Customizer Class will be used to extract all the information in the*/
/*Reflection System to build the Tool Screen.                                   */
/********************************************************************************/
class FZED_DetailCustomizer : public	IDetailCustomization
{
public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static TSharedRef<IDetailCustomization> MakeInstance()
	{
		return MakeShareable(new FZED_DetailCustomizer);
	}

	TWeakObjectPtr<class UZED_ObjectData> ZED_AssetClass;
	
	static TArray<TSharedPtr<ZED_CustomizerField> > ZED_PropertyHandleList;
};

class FZED_PropertyCustomizer : public IPropertyTypeCustomization
{
public:
	
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FZED_PropertyCustomizer);
	}
	
	UZED_ObjectData* ZED_AssetObject;
	
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle>PropertyHandle, IDetailChildrenBuilder& ChildBuilder,	IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeHeader  (TSharedRef<IPropertyHandle>PropertyHandle, FDetailWidgetRow& HeaderRow,IPropertyTypeCustomizationUtils& CustomizationUtils) override;
};