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

#include "AssetTypeActions_Base.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"

class ZOAN_VP_EDITOR_API FZED_AssetActions : public	FAssetTypeActions_Base
{
public:

	virtual bool    HasActions       (const TArray<UObject*>& InObjects                           ) const override;
	virtual void    GetActions       (const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	virtual FText   GetName          (                                                            ) const override;
	virtual UClass* GetSupportedClass(                                                            ) const override;
	virtual FColor  GetTypeColor     (                                                            ) const override;
	virtual uint32  GetCategories    (                                                            ) override;
	
	void OnAssetClicked()
	{
		TSharedRef<SWindow> ZoanToolsWindow = SNew(SWindow)
			.Title(FText::FromString(TEXT("ZED Tools Window")))
			.ClientSize(FVector2D(800, 400))
			.SupportsMaximize(false)
			.SupportsMinimize(false);

		IMainFrameModule& MainFrameModule =	FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
		if (MainFrameModule.GetParentWindow().IsValid())
		{
			FSlateApplication::Get().AddWindowAsNativeChild(ZoanToolsWindow,	MainFrameModule.GetParentWindow().ToSharedRef());
		}
		else
		{
			FSlateApplication::Get().AddWindow(ZoanToolsWindow);
		}
	};
};