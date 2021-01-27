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
#include "ZED_AssetActions.h"
#include "../ZOAN_VP_EDITOR.h"
#include "../Screens/ZED_ConfigurationData.h"

bool FZED_AssetActions::HasActions(const TArray<UObject*>&	InObjects) const
{
	return true;
}

void FZED_AssetActions::GetActions(const TArray<UObject*>&	InObjects, FMenuBuilder& MenuBuilder)
{
	//MenuBuilder.AddMenuEntry(FText::FromString("Configuration Asset Action"),
	//	                     FText::FromString("Action for the Configuration Details"),
	//	                     FSlateIcon(FEditorStyle::GetStyleSetName(),"LevelEditor.ViewOptions"),
	//	                     FUIAction(FExecuteAction::CreateRaw(this,	&FZED_AssetActions::OnAssetClicked),FCanExecuteAction()));
}

uint32 FZED_AssetActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FText FZED_AssetActions::GetName() const
{
	return FText::FromString(TEXT("ZED Configuration Asset"));
}

UClass* FZED_AssetActions::GetSupportedClass() const
{
	return AZED_ConfigurationData::StaticClass();
}

FColor FZED_AssetActions::GetTypeColor() const
{
	return FColor::Orange;
}