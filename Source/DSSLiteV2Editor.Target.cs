// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DSSLiteV2EditorTarget : TargetRules
{
	public DSSLiteV2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        ExtraModuleNames.Add("DSSLiteV2");
#if UE_5_4_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
#else
	DefaultBuildSettings = BuildSettingsVersion.V2;
#endif

    }
}
