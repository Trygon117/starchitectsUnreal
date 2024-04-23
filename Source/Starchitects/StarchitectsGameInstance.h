// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EngineUtils.h"
#include "Misc/DefaultValueHelper.h"
#include "IWebSocket.h"
#include "Json.h"
#include "StarData.h"
#include "StarObj.h"
#include "StarBase.h"
#include "Engine/EngineTypes.h"
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

	void CreateStar(FStarData data, FString ID);
	void LoadStars(TArray<TSharedPtr<FJsonValue>> starsJSON);
	void AddStar(TSharedPtr<FJsonObject> starJSON);
	void AddStarDebug();
	void TrackNewStar();
	void TrackStar();

	void CallSparkleAnimation(FString starID);
	void CallTwirlAnimation(FString starID);
	void CallSupernovaAnimation(FString starID);

	FTimerHandle trackStarHandle; // the handle of the timer to track stars
	FTimerHandle trackNewStarHandle; // the handle of the timer to track stars
	int32 trackingIndex = -1; // the index of the currently tracked star
	double trackingDelta = 0;

	//TMap<int32, FStarData> stars;
	TMap<int32, AStarObj> stars;

	TSharedPtr<IWebSocket> WebSocket;

	UPROPERTY(VisibleAnywhere)
	TArray<AStarObj*> starClass;

	UPROPERTY(VisibleAnywhere)
	AStarBase* starBase; //This is where the rotation of all of the stars will be happening

private:
	TSharedPtr<FJsonObject> ParseJSON(FString json);

};
