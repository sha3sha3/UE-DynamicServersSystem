// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DSSLiteV2ServerTarget : TargetRules
{
	public DSSLiteV2ServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		ExtraModuleNames.Add("DSSLiteV2");
		bUseLoggingInShipping = false;
#if UE_5_4_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
#else
	DefaultBuildSettings = BuildSettingsVersion.V2;
#endif

    }
}
