
using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Desktop)]
public class DSSLiteV2ClientTarget : TargetRules
{ 
	public DSSLiteV2ClientTarget(TargetInfo Target) : base(Target)
    {        
        Type = TargetType.Client;
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