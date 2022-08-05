// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimpleRTS : ModuleRules
{
	public SimpleRTS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			// DEFAULTS
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			// END OF DEFAULTS
			"Landscape", 
			// "LandscapeEditor"
			"Slate",
			"SlateCore",
			"UMG",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
