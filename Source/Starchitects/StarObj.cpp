// Fill out your copyright notice in the Description page of Project Settings.


#include "StarObj.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AStarObj::AStarObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	this->SetRootComponent(mesh);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> SquareMesh(TEXT("/Engine/BasicShapes/Sphere")); 
	Asset = SquareMesh.Object;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> RookMesh(TEXT("/Game/Models/Rook")); 
	Rook = RookMesh.Object;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> RockMesh(TEXT("/Game/Models/Rock")); 
	Rock = RockMesh.Object;

	//const ConstructorHelpers::FObjectFinder<UMaterial> MaterialObj(TEXT("/Engine/BasicShapes/BasicShapeMaterial")); 
	const ConstructorHelpers::FObjectFinder<UMaterial> MaterialObj(TEXT("/Game/Star_Material")); 
	mesh->SetMaterial(0, MaterialObj.Object);

	DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialObj.Object, mesh);
	// DynamicMaterial->SetVectorParameterValue("StarColor", FLinearColor::MakeRandomColor());
	// mesh->SetMaterial(0, DynamicMaterial);

	//HSVToLinearRGB(starData.color, 1, starData.shade);
	//MakeFromHSV8

	//Load every shape possible

}

// Called when the game starts or when spawned
void AStarObj::BeginPlay()
{
	Super::BeginPlay();

	isGlowing = false;

	//mesh->SetStaticMesh(Asset);

	//Based off of the int in the star data, set the static mesh to that

	//mesh::GetMaterial(0) - get/change the properties of the material

	//FString pos = this->GetActorLocation().ToString();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Position: " + pos));

	StarCurve = NewObject<UCurveFloat>(this);
	FKeyHandle KeyHandle = StarCurve->FloatCurve.UpdateOrAddKey(0.f, 0.f);
	StarCurve->FloatCurve.UpdateOrAddKey(1.f, 1.f);
	StarCurve->FloatCurve.SetKeyInterpMode(KeyHandle, ERichCurveInterpMode::RCIM_Cubic, true);

	TwirlTimeline = NewObject<UTimelineComponent>(this);

    if (StarCurve)
    {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Timeline loaded");
	    FOnTimelineFloat TimelineCallback;
        FOnTimelineEventStatic TimelineFinishedCallback;

        TimelineCallback.BindUFunction(this, FName{TEXT ("TwirlControls")});
        TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("FinishTwirlAnimation") });
		TwirlTimeline->SetTimelineLength(5.f);
        TwirlTimeline->AddInterpFloat(StarCurve, TimelineCallback);
        TwirlTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
		//TwirlTimeline->PlayFromStart();
	}
	
}

// Called every frame
void AStarObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set actor to position
	//FVector relativePosition = GetTransform().InverseTransformPosition(this->GetActorLocation());
	//this->SetActorRelativeLocation(FMath::Lerp(GetActorLocation(), starData.position, DeltaTime));

	if(!hasChangedMesh)
	{
		switch(starData.shape)
		{
			case 0:
				SetActorRelativeScale3D(FVector::OneVector);
				mesh->SetStaticMesh(Asset);
				hasChangedMesh = true;
				//SetActorTickEnabled(false);
				break;
			case 1:
				SetActorRelativeScale3D(FVector::OneVector * 25);
				mesh->SetStaticMesh(Rook);
				hasChangedMesh = true;
				//SetActorTickEnabled(false);
				break;
			case 2:
				SetActorRelativeScale3D(FVector::OneVector * 25);
				mesh->SetStaticMesh(Rock);
				hasChangedMesh = true;
				//SetActorTickEnabled(false);
				break;
			default:
				break;
		}
	}

	if(startRotation)
	{
		RotateValue += 10.0f;
		FQuat NewRotation = FQuat(FRotator(0, RotateValue, 0));
		SetActorRelativeRotation(NewRotation);
		if(GetActorRotation().Yaw < 0)
		{
			halfwayRotation = true;
		}

		if(halfwayRotation && GetActorRotation().Yaw >= 0)
		{
			halfwayRotation = false;
			startRotation = false;
			SetActorRelativeRotation(FQuat(FRotator::ZeroRotator));
		}
	}


	//Lerp - Linear
	//SmoothStep - Hermite
	//InterpEaseInOut - Ease In/Out

}

//Sets everything up because for some reason I can't make it an argument
void AStarObj::SetUpData(FStarData data)
{
	starData = data;

	float hue = starData.color * 6;
	TArray<float> hueToRGB = {FMath::Clamp(abs(hue - 3) - 1, 0, 1), FMath::Clamp(2 - abs(hue - 2), 0, 1), FMath::Clamp(2 - abs(hue - 4), 0, 1)};
	SetActorRelativeLocation(starData.position);
	
	// float shadeRadians = starData.shade * 2 * PI;
	// float saturation = 0.75 + 0.25*cos(shadeRadians);
	// float value = 0.75 + 0.25*sin(shadeRadians);

	TArray<float> colorArray = {};

	for(int i = 0; i < 3; i++)
	{
		colorArray.Add(FMath::Lerp(hueToRGB[i], starData.shade, 0.35));
	// 	colorArray.Add(FMath::Lerp(1, hueToRGB[i], saturation) * value);
	}

	color = FLinearColor(colorArray[0], colorArray[1], colorArray[2]);
	DynamicMaterial->SetVectorParameterValue("StarColor", color);
	mesh->SetMaterial(0, DynamicMaterial);

	
			// SetActorRelativeScale3D(FVector::OneVector * 25);
			// SetActorRelativeScale3D(FVector::OneVector * 25);

	//Test for shape
}

void AStarObj::SparkleAnimation()
{

}

void AStarObj::TwirlAnimation()
{
	//Set the yaw from 0 to 360
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Spin!");
	startRotation = true;
	TwirlTimeline->PlayFromStart();
	//FQuat NewRotation = FQuat(FRotator(0.f, 0.f, GetActorRotation().Yaw + 90.0f));
	//SetActorRelativeRotation(NewRotation);
}

void AStarObj::TwirlControls()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Play!");
	
    //SetActorRelativeRotation(NewRotation);
}

void AStarObj::FinishTwirlAnimation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Done!");
}

void AStarObj::SupernovaAnimation()
{
	
}
