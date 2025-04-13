// CitroenGames 2023

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "LevelGMSetterBPLibrary.generated.h"

UCLASS()
class ULevelGMSetterBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Server Travel", Keywords = "LevelGMSetter server travel game mode", WorldContext = "WorldContextObject"), Category = "LevelGMSetter|Travel")
	static void ExecuteServerTravel(UObject* WorldContextObject, TSoftObjectPtr<UWorld> LevelReference, TSubclassOf<AGameModeBase> GameMode, bool bListen);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Level With Game Mode", Keywords = "LevelGMSetter open level game mode", WorldContext = "WorldContextObject"), Category = "LevelGMSetter|Travel")
	static void OpenLevelWithGameMode(UObject* WorldContextObject, TSoftObjectPtr<UWorld> LevelReference, TSubclassOf<AGameModeBase> GameMode);

};