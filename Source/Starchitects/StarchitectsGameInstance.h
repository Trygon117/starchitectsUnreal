// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "Json.h"
#include "StarData.h"
#include "StarObj.h"
#include "StarchitectsGameInstance.generated.h"

/**
 *
 */
UCLASS()
class STARCHITECTS_API UStarchitectsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	void CreateStar();
	void LoadStars(TArray<TSharedPtr<FJsonValue>> starsJSON);
	void AddStar(TSharedPtr<FJsonObject> starJSON);
	void AddStarDebug();

	void CallSparkleAnimation(FString starID);
	void CallTwirlAnimation(FString starID);
	void CallSupernovaAnimation(FString starID);

	TMap<int32, FStarData> stars;

	TSharedPtr<IWebSocket> WebSocket;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<AActor> StarClass;

private:
	TSharedPtr<FJsonObject> ParseJSON(FString json);
};
