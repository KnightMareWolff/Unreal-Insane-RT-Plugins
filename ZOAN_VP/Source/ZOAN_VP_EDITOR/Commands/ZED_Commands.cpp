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
#include "ZED_Commands.h"
#include "../ZOAN_VP_EDITOR.h"
#include "Framework/Commands/Commands.h"

#define LOCTEXT_NAMESPACE "FZOAN_VP_EDITORModule"

void FZEDCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ZOAN_ED", "Bring up ZOAN_ED window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE