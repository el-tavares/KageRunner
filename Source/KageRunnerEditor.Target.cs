// Vox Dei. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class KageRunnerEditorTarget : TargetRules
{
	public KageRunnerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "KageRunner" } );
	}
}
