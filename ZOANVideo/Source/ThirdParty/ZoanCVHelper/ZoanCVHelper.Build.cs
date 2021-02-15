// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ZoanCVHelper: ModuleRules
{
	public ZoanCVHelper(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicIncludePaths.AddRange(
			new string[] {
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"ZoanCVHelper/Private"
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[] {
            }
        );

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
                "Projects",
                "ZoanOpenCV"
            }
        );
	}
}
