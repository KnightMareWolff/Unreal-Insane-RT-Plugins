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

#include "ZED_AssetField.h"

#define LOCTEXT_NAMESPACE "ZED_ListRow"

class ZED_ListRow : public SMultiColumnTableRow<TSharedPtr<FString>>
{
public:

	SLATE_BEGIN_ARGS(ZED_ListRow) {}
	SLATE_ARGUMENT(TSharedPtr<ZED_AssetField>, Item)
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
	{
		Item = InArgs._Item;
		SMultiColumnTableRow<TSharedPtr<FString> >::Construct(FSuperRowType::FArguments(), InOwnerTableView);
	}

	/**
	 * Generate a widget for the column name.
	 */
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override
	{
		
		if (ColumnName == "FieldName")
		{

			if (Item.Get()->IsStruct == true)
			{
				return SNew(SBox)
					       .Padding(FMargin(4.0f, 0.0f))
					       .HAlign(HAlign_Left)
					       [
							   SNew(SHorizontalBox)
							   + SHorizontalBox::Slot()
					           .HAlign(HAlign_Left)
					           .AutoWidth()
					           [
								  SNew(SExpanderArrow, SharedThis(this))
							   ]
				               + SHorizontalBox::Slot()
							   .HAlign(HAlign_Left)
							   .AutoWidth()
							   [
								  SNew(STextBlock).Text(FText::FromString(Item.Get()->FieldName))
							   ]
						   ];
			}
			else
			{
				return SNew(SBox)
					.Padding(FMargin(4.0f, 0.0f))
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock).Text(FText::FromString(Item.Get()->FieldName))
					];
			}
		}

		if (ColumnName == "Widget")
		{
			if (Item.Get()->IsEnum == true)
			{
				if (Item.Get()->IsCustom)
				{
					return SNew(ZED_ComboBox).Item(Item.Get()->FieldEnumValues);
				}
				else
				{
					return SNew(SProperty , Item.Get()->FieldView.Get()->GetPropertyHandle());
				}
			}
			else if(Item.Get()->IsStruct == true)
			{
				//Nothing on de second column for a Struct Field...
				//return SNew(SBox)
				//	.Padding(FMargin(4.0f, 0.0f))
				//	.VAlign(VAlign_Center)
				//	[
				//		SNew(STextBlock).Text(FText::FromString(" "))
				//	];

					return SNew(SStructPropertyEntryBox).SelectedStruct(Item.Get()->FieldScrStruct).OnSetStruct(this, &ZED_ListRow::OnSetStruct);
			}
			else if (Item.Get()->IsObject == true)
			{
				if (Item.Get()->IsCustom)
				{
					return SNew(ZED_PointerBox);
				}
				else
				{
					return SNew(SObjectPropertyEntryBox).PropertyHandle(Item.Get()->FieldView.Get()->GetPropertyHandle());
				}
			}
			else if (Item.Get()->IsNative == true)
			{
				if (Item.Get()->FieldType == "int32")
				{
					if (Item.Get()->IsCustom)
					{
						return SNew(ZED_IntBox).Item(Item.Get()->FieldIntValue);
					}
					else
					{
						return SNew(SProperty, Item.Get()->FieldView.Get()->GetPropertyHandle());
					}
				}
				if (Item.Get()->FieldType == "float")
				{
					if (Item.Get()->IsCustom)
					{
						return SNew(ZED_FloatBox).Item(Item.Get()->FieldFloatValue);
					}
					else
					{
						return SNew(SProperty, Item.Get()->FieldView.Get()->GetPropertyHandle());
					}
				}
			}
			else if (Item.Get()->IsNative == false)
			{
				if (Item.Get()->FieldType == "FString")
				{
					if (Item.Get()->IsCustom)
					{
						return SNew(ZED_EditBox).Item(Item.Get()->FieldStringValue);
					}
					else
					{
						return SNew(SProperty, Item.Get()->FieldView.Get()->GetPropertyHandle());
					}
				}
			}
		}

		return SNew(SBox)
			.Padding(FMargin(4.0f, 0.0f))
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock).Text(FText::FromString(ColumnName.GetPlainNameString()))
			];
	}

	const FSlateBrush* GetExpanderImage() const
	{
		FName BrushName;

		BrushName = TEXT("button_small");

		return FZED_Style::Get().GetBrush(BrushName);
	}

	void OnSetStruct(const UScriptStruct*)
	{

	}


protected:
	TSharedPtr<ZED_AssetField>    Item;
	
};

#undef LOCTEXT_NAMESPACE