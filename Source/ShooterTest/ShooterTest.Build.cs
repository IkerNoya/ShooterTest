// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShooterTest : ModuleRules
{
	public ShooterTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", 
			"Engine", "InputCore", "HeadMountedDisplay" , "Niagara", "NiagaraCore",
			"AIModule", "GameplayTasks"});
		
		PrivateDependencyModuleNames.AddRange(new string[]{"Niagara"});
	}
}
