// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StarData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct STARCHITECTS_API FStarData
{
public:
	GENERATED_BODY();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int shape;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float color;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float size;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float shade;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector position;


	FStarData();
	~FStarData();
};
