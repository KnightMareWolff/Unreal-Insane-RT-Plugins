// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System.IO;

public class ZOAN_VP_EDITOR : ModuleRules
{
	public ZOAN_VP_EDITOR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {"Core",
                                                           "CoreUObject", 
                                                           "Engine", 
                                                           "InputCore", "RHI","RenderCore","MainFrame", "AssetTools","AppFramework","EditorSubsystem",
                                                           "PropertyPath","ZOAN_VP", "EditorWidgets", "PropertyEditor", "KismetWidgets", "MediaAssets","BlackmagicMedia",
                                                           "MediaIOCore"});

        PrivateDependencyModuleNames.AddRange(new string[] {"UnrealEd", "Slate", "SlateCore", "EditorStyle","GraphEditor", "BlueprintGraph" , "Projects", "ToolMenus", "PropertyEditor", "KismetWidgets" });

        PrivateIncludePaths.AddRange(
                new string[]
                {
                    "BlackmagicMediaOutput/Private","ZOAN_VP/Private"
                }
            );

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory , "ZOAN_VP/Public"));
        
    }
}
