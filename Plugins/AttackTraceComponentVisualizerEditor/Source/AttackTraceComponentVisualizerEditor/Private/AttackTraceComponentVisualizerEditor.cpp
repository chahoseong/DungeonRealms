#include "AttackTraceComponentVisualizerEditor.h"
#include "AttackTraceComponentVisualizer.h"
#include "DungeonRealms/CombatSystem/DungeonRealmsAttackTraceComponent.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"

#define LOCTEXT_NAMESPACE "FAttackTraceComponentVisualizerEditorModule"

void FAttackTraceComponentVisualizerEditorModule::StartupModule()
{
	if (GUnrealEd)
	{
		TSharedPtr<FComponentVisualizer> AttackTraceVisualizer = MakeShareable(new FAttackTraceComponentVisualizer);
		GUnrealEd->RegisterComponentVisualizer(UDungeonRealmsAttackTraceComponent::StaticClass()->GetFName(), AttackTraceVisualizer);
	}
}

void FAttackTraceComponentVisualizerEditorModule::ShutdownModule()
{
	if (GUnrealEd)
	{
		GUnrealEd->UnregisterComponentVisualizer(UDungeonRealmsAttackTraceComponent::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAttackTraceComponentVisualizerEditorModule, AttackTraceComponentVisualizerEditor)