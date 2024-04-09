// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarData.h"
#include "Math/Vector.h"
#include "Math/Color.h"
#include "Math/TransformNonVectorized.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "StarObj.generated.h"

UCLASS()
class STARCHITECTS_API AStarObj : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStarObj();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStarData starData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float rotationSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isGlowing;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* stardust;
	//UParticleSystemComponent* stardust;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* StarCurve;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor color;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor particleColor;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* mesh;
	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Asset;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Rook;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Rock;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* ChessPiece;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* BalloonDog;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* KitchenAppliance;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* BonsaiTree;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Geode;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* RubberDuck;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* JetPlane;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Radio;
	UPROPERTY(BlueprintReadWrite)
	bool hasChangedMesh;
	UPROPERTY(BlueprintReadWrite)
	UTimelineComponent* TwirlTimeline;

	float RotateValue;
	float CurveFloatValue;
	float TimelineValue;

	UPROPERTY(BlueprintReadWrite)
	bool startRotation;
	UPROPERTY(BlueprintReadWrite)
	bool halfwayRotation;

	//UPROPERTY(BlueprintReadWrite)
	//int32 hue;

	//UFUNCTION(BlueprintCallable, Category="StarObj")
	//void hueToRGB(float hue, TArray<float> &color);

	//void RGBToHex(float color, float shade);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float angleAxis;
	UPROPERTY(EditAnywhere)
	FVector dimensions;
	UPROPERTY(EditAnywhere)
	FVector axisVector;
	UPROPERTY(EditAnywhere)
	float multiplier;

	float RunningTime;

	//void hueToRGB(float hue, TArray<float> &color);

	//Create a function to add in all of the data
	void SetUpData(FStarData data);

	void SparkleAnimation();
	void TwirlAnimation();
	void SupernovaAnimation();

	UFUNCTION()
	void TwirlControls();
	UFUNCTION()
	void FinishTwirlAnimation();
};
