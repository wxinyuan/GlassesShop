// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GlassesShop : ModuleRules
{
	public GlassesShop(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		OptimizeCode = CodeOptimization.Never;

		PublicDependencyModuleNames.AddRange(
			new string[] 
			{ 
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"InterchangeEngine", 
				"InterchangeImport",
				"InterchangeNodes",
				"InterchangeCommonParser",
				"InterchangeMessages",
				"Json",
				"RenderCore",
				"RHI",
				"TextureUtilitiesCommon",
				"VariantManagerContent",
				"GLTFCore",
				"IESFile",
				"ImageCore",
				"ImageWrapper",
				"AssetRegistry",
				"CinematicCamera",
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
