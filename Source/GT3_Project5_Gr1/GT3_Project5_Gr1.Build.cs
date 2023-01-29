// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GT3_Project5_Gr1 : ModuleRules
{
	public GT3_Project5_Gr1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara", "UMG" });
	}
}