// Vox Dei. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class KageRunnerTarget : TargetRules
{
	public KageRunnerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "KageRunner" } );
	}
}
