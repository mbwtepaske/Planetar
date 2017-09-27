using UnrealBuildTool;

public class DotNetCoreHost : ModuleRules
{
  public DotNetCoreHost(ReadOnlyTargetRules Target) : base(Target)
  {
    PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
    
    DynamicallyLoadedModuleNames.AddRange(
      new string[]
      {
				// Dynamic loaded modules
			});

    PublicDependencyModuleNames.AddRange(
      new string[]
      {
        "Core"
			});

    PublicIncludePaths.AddRange(
      new string[]
      {
        "DotNetCoreHost/Public"
			});

    PrivateDependencyModuleNames.AddRange(
      new string[]
      {
				// Statically link dependencies
			});

    PrivateIncludePaths.AddRange(
      new string[]
      {
        "DotNetCoreHost/Private",
			});
  }
}