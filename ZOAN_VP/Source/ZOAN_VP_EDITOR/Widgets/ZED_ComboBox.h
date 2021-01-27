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
#include "SSearchableComboBox.h"

#define LOCTEXT_NAMESPACE "ZED_ComboBox"

class ZED_ComboBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ZED_ComboBox){}
	SLATE_ARGUMENT(TArray<TSharedPtr<FString> >, Item)
	SLATE_END_ARGS()

	typedef TSharedPtr<FString> FComboItemType;

	void Construct(const FArguments& InArgs)
	{
		for (int i = 0; i < InArgs._Item.Num(); i++)
		{
			Options.Add(InArgs._Item[i]);
		}

		CurrentItem = Options[0];

		ChildSlot
			[
				SNew(SComboBox<FComboItemType>)
				.OptionsSource(&Options)
			    .OnSelectionChanged(this, &ZED_ComboBox::OnSelectionChanged)
			    .OnGenerateWidget  (this, &ZED_ComboBox::MakeWidgetForOption)
			    .InitiallySelectedItem(CurrentItem)
			    [
				   SNew(STextBlock).Text(this, &ZED_ComboBox::GetCurrentItemLabel)
			    ]
			];
	}

	TSharedRef<SWidget> MakeWidgetForOption(FComboItemType InOption)
	{
		return SNew(STextBlock).Text(FText::FromString(*InOption));
	}

	void OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
	{
		CurrentItem = NewValue;
	}

	FText GetCurrentItemLabel() const
	{
		if (CurrentItem.IsValid())
		{
			return FText::FromString(*CurrentItem);
		}

		return LOCTEXT("InvalidComboEntryText", "<<Invalid option>>");
	}

	FComboItemType         CurrentItem;
	TArray<FComboItemType> Options;
};

#undef LOCTEXT_NAMESPACE
