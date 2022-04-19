
using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Desktop)]
public class DSSLiteV2ClientTarget : TargetRules
{ 
	public DSSLiteV2ClientTarget(TargetInfo Target) : base(Target)
    {        
        Type = TargetType.Client;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.Add("DSSLiteV2");
        bUseLoggingInShipping = true;
    }
}