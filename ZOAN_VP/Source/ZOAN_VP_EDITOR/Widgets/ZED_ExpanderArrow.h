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
#include "../Style/ZED_Style.h"

#define LOCTEXT_NAMESPACE "ZED_ExpanderArrow"

class ZED_ExpanderArrow : public SExpanderArrow
{
public:

	SLATE_BEGIN_ARGS(ZED_ExpanderArrow) {}
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs, const TSharedPtr<class ITableRow>& TableRow)
	{
		
	}

	void teste()
	{
		a = 0;
	}

	const FSlateBrush* GetExpanderImage() const
	{
		FName BrushName;

		BrushName = TEXT("ButtonIcon_custom");

		return FZED_Style::Get().GetBrush(BrushName);
	}

protected:

	

	int a;
};

#undef LOCTEXT_NAMESPACE