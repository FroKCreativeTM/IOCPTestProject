// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IOCPTestProject : ModuleRules
{
	public IOCPTestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
		string IncludePath = ThirdPartyPath + "MyLib/Include/";
		string LibraryPath = ThirdPartyPath;

		LibraryPath += "MyLib/Bin_x64/";

		// PublicLibraryPaths.Add(LibraryPath);
		PublicIncludePaths.Add(IncludePath);
		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "ServerCore.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "libprotobuf.lib"));
	}
}
