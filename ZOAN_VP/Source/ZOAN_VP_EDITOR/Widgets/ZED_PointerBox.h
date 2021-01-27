/******************************************************************************/
/*Project: ZOAN Editor Extensions                                             */
/*Description:                                                                */
/*The Zoan Editor Extensions is a plug-In responsible to handle the runtime   */
/*Object Customizations and Parameterization for the Zoan Runtime Production  */
/*Plug-In                                                                     */
/******************************************************************************/
/*Object Description:                                                         */
/*The pointer control will take care of the visual representation of Zoan     */
/*Plug-In Objects.                                                            */
/*They are custom objects since is totally unnecessary use the Static Mesh    */
/*Library, just to show an image of a Object already know by the system.      */
/*Simplifying, doesnt matter if the operator know about the soft pointers, obj*/
/*pointers etc... since they are focused on the type of this object and what  */
/*this object will do during the realtime production.                         */
/*This Custom object will know about all the custom objects on the system and */
/*automatically will show to the operator the correct thumbnails and fields to*/
/*Be filled/changed                                                           */
/******************************************************************************/
/*Copyright Zoan Oy, Inc. All Rights Reserved.                                */
/*Author: William D. Wolff                                                    */
/******************************************************************************/
#pragma once

#include "SlateBasics.h"
#include "../Style/ZED_Style.h"

#define LOCTEXT_NAMESPACE "ZED_SpinBox"

class ZED_PointerBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ZED_PointerBox) {}
	SLATE_ARGUMENT(FString, TextItem)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{

		TextItem = InArgs._TextItem;
		
		ChildSlot
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			    [
				    SNew(SVerticalBox)
				    + SVerticalBox::Slot()
			        .HAlign(HAlign_Fill)
			        .VAlign(VAlign_Center)
			        [
				        SNew(SBox)
				        .HAlign(HAlign_Fill)
			            .Content()
			            [
							SNew(SImage).Image(this, &ZED_PointerBox::GetImageBrush)
			            ]
			        ]
		       ]
		       + SHorizontalBox::Slot()
			   .HAlign(HAlign_Fill)
			   [
				    SNew(SVerticalBox)
				    + SVerticalBox::Slot()
			       .HAlign(HAlign_Fill)
			       .VAlign(VAlign_Center)
			       [
				      SNew(SBox).HAlign(HAlign_Fill).VAlign(VAlign_Center).Content()
			          [
						  SNew(SEditableTextBox).Text(FText::FromString(InArgs._TextItem))
			         ]
			       ]
		           + SVerticalBox::Slot()
			       .HAlign(HAlign_Fill)
			       .VAlign(VAlign_Center)
			       [
				      SNew(SBox).HAlign(HAlign_Fill).VAlign(VAlign_Center)
					  [
						  SNew(STextBlock).Text(FText::FromString("Description"))
					  ]
			       ]
			   ]
			];
	}

	const FSlateBrush* GetImageBrush() const
	{
		FName BrushName;

		BrushName = TEXT("button_small");

		return FZED_Style::Get().GetBrush(BrushName);
	}

	FReply ButtonPressed()
	{
		return FReply::Handled();
	}
protected:
	FString TextItem;
};

#undef LOCTEXT_NAMESPACE