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
#include "ZOAN_VP_EDITOR.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Developer/AssetTools/Public/IAssetTools.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"

//ZED
#include "Actions/ZED_AssetActions.h"
#include "ZED_WidgetBuilder.h"
#include "ZED_Subsystem.h"

//Slate
#include "SlateBasics.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "Widgets/Docking/SDockTab.h"

static const FName ZOAN_EDConfigToolName("ZED_ConfigTab");
static const FName ZOAN_EDAvatarToolName("ZED_AvatarTab");

#define LOCTEXT_NAMESPACE "FZOAN_VP_EDITORModule"

static int NumTabs = 0;

void FZOAN_VP_EDITORModule::StartupModule()
{
	FZED_Style::Initialize();
	FZED_Style::ReloadTextures();

	//Register on the system the Commands that will be used
	FZEDCommands::Register();

	//retrieve the resultant command list from the system.
	PluginCommands = MakeShareable(new FUICommandList);
	
	//Bind the Button itself with the action that must be performed
	PluginCommands->MapAction(FZEDCommands::Get().OpenPluginWindow                                        ,	
		                      FExecuteAction::CreateRaw(this, &FZOAN_VP_EDITORModule::PluginButtonClicked),
		                      FCanExecuteAction(), 
		                      FIsActionButtonVisible::CreateRaw(this, &FZOAN_VP_EDITORModule::BtnVisible));
	
	const FUIAction *pAction = PluginCommands->GetActionForCommand(FZEDCommands::Get().OpenPluginWindow);
	
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FZOAN_VP_EDITORModule::RegisterMenus));
	
	//Register on the tab manager all the tabs that must be spawned by the main window
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ZOAN_EDConfigToolName,
		                                              FOnSpawnTab::CreateRaw(this, &FZOAN_VP_EDITORModule::OnSpawnPluginTab))
		                                             .SetDisplayName(LOCTEXT("ZOAN Editor Configuration", "Configuration Tool"))
		                                             .SetMenuType(ETabSpawnerMenuType::Hidden);
	
	
	//Register the Actions for the Configuration Asset(Warning! Only Use This in Development to generate the asset!) - Probably will be excluded too...
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	auto Actions = MakeShareable(new FZED_AssetActions);
	AssetTools.RegisterAssetTypeActions(Actions);
	ZED_AssetTypeActions.Add(Actions);

	
}

bool FZOAN_VP_EDITORModule::BtnVisible()
{
	return false;
}

void FZOAN_VP_EDITORModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FZED_Style::Shutdown();

	FZEDCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ZOAN_EDConfigToolName);
}

TSharedRef<SDockTab> FZOAN_VP_EDITORModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//Initialize The Object Builders for the Configuration Tool
	//Warning!!
	//This declaration are here becouse we need for now a instance inside of the TabSpawning Scope
	//This is the same problem happening at the OnFinishedChangingProperties Function bein used in the
	//FZED_WidgetBuilder class.
	//If you put this at the initialization part , for example you will get empty controls since the internal
	//Object was built inside of the FZED_WidgetBuilder class.
	//This is not a simple change, since will need the code for another tool be integrated on the system and
	//Must be coded during Alpha Development Releases(With Time To test and Fix).
	//Just in Time, since this class are not inside of a Class registered on System the NewObject Function
	//Probably the Garbage Collection are Generating some issues at the Detail View Cleaning Up, things
	//That cannot be clean.
	FZED_WidgetBuilder* ScreenBuilder = new FZED_WidgetBuilder();

	if (!UZED_Subsystem::IsSimulationRunning)
	{
		return SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				ScreenBuilder->GetRef()
			];
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
		    .VAlign(VAlign_Center)
		    .Content()
		    [
				SNew(STextBlock).Text(FText::FromString("The System Configurations can be altered only in Editor Mode. (Simulation Running)."))
		    ]
		];
}


void FZOAN_VP_EDITORModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(ZOAN_EDConfigToolName);
	//FGlobalTabmanager::Get()->InvokeTab(ZOAN_EDAvatarToolName);
}

void FZOAN_VP_EDITORModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FZEDCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FZEDCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FZOAN_VP_EDITORModule, ZOAN_VP_EDITOR)
