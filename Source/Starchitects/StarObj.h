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
	UMaterial* Material;
	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Asset;
	UPROPERTY(BlueprintReadWrite)
	bool hasChangedMesh;
	UPROPERTY(BlueprintReadWrite)
	UTimelineComponent* TwirlTimeline;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* ChessMesh;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* BalloonMesh;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* ApplianceMesh;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* BonsaiMesh;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* GeodeMesh;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* DuckMesh;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* PlaneMesh;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* RadioMesh;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* ChessMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* BalloonMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* ApplianceMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* BonsaiWoodMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* BonsaiLeavesMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* BonsaiGrassMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* GeodeMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* DuckDuckMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* DuckSwanMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* DuckBowlMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* PlaneMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* RadioMaterial;


	// float RotateValue;
	// float CurveFloatValue;
	// float TimelineValue;

	UPROPERTY(BlueprintReadWrite)
	bool startRotation;
	UPROPERTY(BlueprintReadWrite)
	bool halfwayRotation;
	UPROPERTY(BlueprintReadWrite)
	bool startsHalfway;
	UPROPERTY(BlueprintReadWrite)
	float RotateValueX;
	UPROPERTY(BlueprintReadWrite)
	float RotateValueY;
	UPROPERTY(BlueprintReadWrite)
	float RotateValueZ;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotateSpeedX;
	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// float RotateSpeedY;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotateSpeedZ;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float rotateLimit;
	UPROPERTY(BlueprintReadWrite)
	float z;

	//UPROPERTY(BlueprintReadWrite)
	//int32 hue;

	//UFUNCTION(BlueprintCallable, Category="StarObj")
	//void hueToRGB(float hue, TArray<float> &color);

	//void RGBToHex(float color, float shade);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool trackCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float orbitSpeed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float angleAxis;
	UPROPERTY(EditAnywhere)
	float distance;

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
