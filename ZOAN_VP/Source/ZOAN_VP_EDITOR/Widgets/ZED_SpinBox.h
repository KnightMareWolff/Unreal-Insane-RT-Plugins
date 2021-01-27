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

#define LOCTEXT_NAMESPACE "ZED_SpinBox"

class ZED_SpinBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ZED_SpinBox) {}
	SLATE_ARGUMENT(int, Item)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		Item = InArgs._Item;

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
				           SNew(SEditableTextBox).Text(FText::FromString(FString::FromInt(Item)))
			            ]
			        ]
		            //+ SVerticalBox::Slot()
					//.HAlign(HAlign_Fill)
					//.VAlign(VAlign_Top)
					//[
						//SAssignNew(SearchBox, SSearchBox).OnTextChanged_Lambda([this](const FText& InText) { FilterText = InText; RefreshFilter(); })
					//]
				 ]
		         + SHorizontalBox::Slot()
					 .HAlign(HAlign_Fill)
					 [
						 SNew(SVerticalBox)
						 + SVerticalBox::Slot()
					     .HAlign(HAlign_Fill)
					     .VAlign(VAlign_Center)
						 [
					        SNew(SBox)
						    .HAlign(HAlign_Fill)
					        .VAlign(VAlign_Center)
					        .Content()
					        [
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot()
					            + SHorizontalBox::Slot()
					            + SHorizontalBox::Slot()
					            [
						            SNew(SButton).OnClicked(this, &ZED_SpinBox::ButtonPressed)
						            .DesiredSizeScale(FVector2D(1.0,1.0))
					              //.ContentPadding(FMargin(4.0, 2.0))
						            [
							           SNew(SImage).Image(this, &ZED_SpinBox::GetImageBrush)
						            ]
								]
					        ]
						 ]
				         + SVerticalBox::Slot()
							 .HAlign(HAlign_Fill)
							 .VAlign(VAlign_Center)
							 [
								 SNew(SBox).HAlign(HAlign_Fill)
							               .VAlign(VAlign_Center)
							     [SNew(STextBlock).Text(FText::FromString("Description"))]
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
	int Item;
	TSharedPtr<SSearchBox> SearchBox;

};

#undef LOCTEXT_NAMESPACE