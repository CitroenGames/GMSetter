// CitroenGames 2023

#include "LevelGMSetterBPLibrary.h"
#include "LevelGMSetter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ULevelGMSetterBPLibrary::ULevelGMSetterBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {}

void ULevelGMSetterBPLibrary::ExecuteServerTravel(UObject* WorldContextObject, TSoftObjectPtr<UWorld> LevelReference, TSubclassOf<AGameModeBase> GameMode, bool bListen)
{
    FString LevelPath = LevelReference.ToString();

    if (LevelPath.IsEmpty())
    {
        // You can optionally log an error or warning here.
        UE_LOG(LogTemp, Warning, TEXT("Invalid Level Reference provided."));
        return;
    }

    // levelpath will return something like /Game/Maps/MyMap.MyMap and we need to remove the .MyMap
    LevelPath = LevelPath.Left(LevelPath.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd));

    FString ServerTravelCommand = "servertravel ";
    ServerTravelCommand += LevelPath;

    if (GameMode != nullptr)
    {
        // Get the full path of the GameMode class
        FString GameModePath = GameMode->GetPathName();

        // Append the game mode parameter to the command
        ServerTravelCommand += FString::Printf(TEXT("?game=%s"), *GameModePath);
    }

    if (bListen)
    {
        ServerTravelCommand += TEXT("?listen");
    }

    // Execute the server travel command
    GEngine->Exec(WorldContextObject->GetWorld(), *ServerTravelCommand);
}

void ULevelGMSetterBPLibrary::OpenLevelWithGameMode(UObject* WorldContextObject, TSoftObjectPtr<UWorld> LevelReference, TSubclassOf<AGameModeBase> GameMode)
{
    FString LevelPath = LevelReference.ToString();

    if (LevelPath.IsEmpty())
    {
        // You can optionally log an error or warning here.
        UE_LOG(LogTemp, Warning, TEXT("Invalid Level Reference provided."));
        return;
    }

    // levelpath will return something like /Game/Maps/MyMap.MyMap and we need to remove the .MyMap
    LevelPath = LevelPath.Left(LevelPath.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd));

    FString OpenLevelCommand = LevelPath;

    if (GameMode != nullptr)
    {
        // Get the full path of the GameMode class
        FString GameModePath = GameMode->GetPathName();

        // Append the game mode parameter to the command
        OpenLevelCommand += FString::Printf(TEXT("?game=%s"), *GameModePath);
    }

    // Open the level with the specified game mode (if provided)
    UGameplayStatics::OpenLevel(WorldContextObject, *OpenLevelCommand, true);
}