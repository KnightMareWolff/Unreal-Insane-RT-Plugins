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

#define LOCTEXT_NAMESPACE "ZED_EditBox"

class ZED_EditBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ZED_EditBox){}
	SLATE_ARGUMENT(FString, Item)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		ChildSlot
			[
				SNew(SEditableTextBox).Text(FText::FromString(InArgs._Item))
			];
	}

protected:
	FString Item;

};

#undef LOCTEXT_NAMESPACE
