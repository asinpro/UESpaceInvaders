// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UESpaceInvaders : ModuleRules
{
	public UESpaceInvaders(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"AIModule"
		});

		//PrivateDependencyModuleNames.AddRange(new string[]
		//{
		//	"Slate",
		//})
	}
}
