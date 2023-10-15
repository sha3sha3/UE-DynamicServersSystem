// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DSSLiteV2GameMode.h"
#include "DSSLiteV2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"

ADSSLiteV2GameMode::ADSSLiteV2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
FString ADSSLiteV2GameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{ 
	check(NewPlayerController);


	// The player needs a PlayerState to register successfully
	if (NewPlayerController->PlayerState == nullptr)
	{
		return FString(TEXT("PlayerState is null"));
	} 

	FString ErrorMessage;

	// Register the player with the session
	GameSession->RegisterPlayer(NewPlayerController, FUniqueNetIdRepl(UniqueId.GetUniqueNetId()), UGameplayStatics::HasOption(Options, TEXT("bIsFromInvite")));

	// Find a starting spot
	FString TravelingOptions = UGameplayStatics::ParseOption(Options, TEXT("mode"));
	if (FCString::IsNumeric(*TravelingOptions)) 
	{
		switch (FCString::Atoi(*TravelingOptions))
		{
		case 2:
		{
			FString LocationString = UGameplayStatics::ParseOption(Options, TEXT("Location"));
			FVector Location;
			Location.InitFromString(*LocationString);
			UE_LOG(LogGameMode, Warning, TEXT("Location: %s"), *Location.ToString());
			float Yaw = FCString::IsNumeric(*UGameplayStatics::ParseOption(Options, TEXT("Rotation"))) ? FCString::Atof(*UGameplayStatics::ParseOption(Options, TEXT("Rotation"))) : 0.f;
			UE_LOG(LogGameMode, Warning, TEXT("Rotation: %s"), *FRotator(0.f, Yaw, 0.f).ToString());
			APlayerStart* const StartSpot =  GetWorld()->SpawnActor<APlayerStart>( Location, FRotator(0.f, Yaw,0.f));
			FRotator InitialControllerRot = StartSpot->GetActorRotation();
			InitialControllerRot.Roll = 0.f;
			NewPlayerController->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), InitialControllerRot);
			NewPlayerController->StartSpot = StartSpot;
		}
			break;
		default:
		{
			UE_LOG(LogGameMode, Warning, TEXT("Portal: %s"), *Portal);
			AActor* const StartSpot = FindPlayerStart(NewPlayerController, Portal);
			if (StartSpot != nullptr)
			{
				// Set the player controller / camera in this new location
				FRotator InitialControllerRot = StartSpot->GetActorRotation();
				InitialControllerRot.Roll = 0.f;
				NewPlayerController->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), InitialControllerRot);
				NewPlayerController->StartSpot = StartSpot;
			}
			else
			{
				ErrorMessage = FString::Printf(TEXT("Failed to find PlayerStart"));
			}
		}
			break;
		}
	}
	// Set up spectating
	bool bSpectator = FCString::Stricmp(*UGameplayStatics::ParseOption(Options, TEXT("SpectatorOnly")), TEXT("1")) == 0;
	if (bSpectator || MustSpectate(NewPlayerController))
	{
		NewPlayerController->StartSpectatingOnly();
	}

	// Init player's name
	FString InName = UGameplayStatics::ParseOption(Options, TEXT("PlayerName")).Left(20);
	if (InName.IsEmpty())
	{
		InName = FString::Printf(TEXT("%s%i"), *DefaultPlayerName.ToString(), NewPlayerController->PlayerState->GetPlayerId());
	}

	ChangeName(NewPlayerController, InName, true);

	return ErrorMessage;
}
