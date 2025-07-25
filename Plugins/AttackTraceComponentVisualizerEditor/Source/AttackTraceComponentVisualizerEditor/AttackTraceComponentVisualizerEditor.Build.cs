using UnrealBuildTool;

public class AttackTraceComponentVisualizerEditor : ModuleRules
{
    public AttackTraceComponentVisualizerEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange([
        ]);

        PrivateDependencyModuleNames.AddRange([
            "Core",
            "CoreUObject",
            "Engine",
            "UnrealEd",
            "ComponentVisualizers",
            "DungeonRealms"
        ]);
    }
}