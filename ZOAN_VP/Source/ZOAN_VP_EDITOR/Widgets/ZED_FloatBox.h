/******************************************************************************/
/*Project: ZOAN Editor Extensions                                             */
/*Description:                                                                */
/*The Zoan Editor Extensions is a plug-In responsible to handle the runtime   */
/*Object Customizations and Parameterization for the Zoan Runtime Production  */
/*Plug-In                                                                     */
/******************************************************************************/
/*Object Description:                                                         */
/*The SpinBox object will handle numeric values that can be increase/decrease */
/*values.                                                                     */
/*Actually all the SpinBoxes of Unreal take account a 3D Modelling Use Cases  */
/*But in some situations this controls fall in making the operator changes    */
/*the value manually since the mouse increase/decrease increase the values too*/
/*fast.                                                                       */
/*The purpose of a Cuistom SpinBox takes in consideration a Virtual Production*/
/*Operator changing this values and the functionality will be designed to fit */
/*with the workflow of this type of professional , not a 3D Modeller          */
/******************************************************************************/
/*Copyright Zoan Oy, Inc. All Rights Reserved.                                */
/*Author: William D. Wolff                                                    */
/******************************************************************************/
#pragma once

#include "SlateBasics.h"
#include "../Style/ZED_Style.h"

#define LOCTEXT_NAMESPACE "ZED_FloatBox"

class ZED_FloatBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ZED_FloatBox) {}
	SLATE_ARGUMENT(float, Item)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		Item = InArgs._Item;

		ChildSlot
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			    .AutoWidth()
			    [
				   SNew(SEditableTextBox).Text(FText::FromString(FString::SanitizeFloat(Item)))
			    ]
		        + SHorizontalBox::Slot()
			    .HAlign(HAlign_Center)
			    [
					SNew(SButton).Text(FText::FromString(TEXT("+"))).OnClicked(this, &ZED_FloatBox::ButtonPressed)
					.DesiredSizeScale(FVector2D(0.5, 0.3))
					.ContentPadding(2.1f)
					[
						SNew(SImage).Image(this, &ZED_FloatBox::GetImageBrush)
					]
			    ]
		        + SHorizontalBox::Slot()
			    + SHorizontalBox::Slot()
			    + SHorizontalBox::Slot()
			    + SHorizontalBox::Slot()
				+ SHorizontalBox::Slot()
				+ SHorizontalBox::Slot()
				+ SHorizontalBox::Slot()
				+ SHorizontalBox::Slot()
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
	float Item;
	TSharedPtr<SSearchBox> SearchBox;

};

#undef LOCTEXT_NAMESPACE