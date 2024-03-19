// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarData.h"
#include "Math/Vector.h"
#include "Math/TransformNonVectorized.h"
#include "StarObj.generated.h"

UCLASS()
class STARCHITECTS_API AStarObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStarObj();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStarData starData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float rotationSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isGlowing;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* mesh;
	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* Rook;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* Rock;
	UPROPERTY(BlueprintReadWrite)
	bool hasChangedMesh;
	UPROPERTY(BlueprintReadWrite)
	int32 hue;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Create a function to add in all of the data
	void SetUpData(FStarData data);

	void SparkleAnimation();
	void TwirlAnimation();
	void SupernovaAnimation();
};
