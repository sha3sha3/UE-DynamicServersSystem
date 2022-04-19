// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DSSLiteV2GameMode.generated.h"

UCLASS(minimalapi)
class ADSSLiteV2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADSSLiteV2GameMode();
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
	
};



