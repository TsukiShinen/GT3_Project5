// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GT3_Project5_Gr1 : ModuleRules
{
	public GT3_Project5_Gr1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
