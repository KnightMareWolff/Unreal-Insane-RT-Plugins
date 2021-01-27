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

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "../Style/ZED_Style.h"

class FZEDCommands : public TCommands<FZEDCommands>
{
public:
	FZEDCommands()
		: TCommands<FZEDCommands>(TEXT("ZOAN_VP_EDITOR"), NSLOCTEXT("Contexts", "ZOAN_VP_EDITOR", "ZOAN_VP Editor Extension"), NAME_None, FZED_Style::GetStyleSetName())
	{
	};

	virtual void RegisterCommands() override;
	
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
