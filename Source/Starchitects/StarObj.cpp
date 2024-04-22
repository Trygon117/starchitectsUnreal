// Fill out your copyright notice in the Description page of Project Settings.

#include "StarObj.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

// Sets default values
AStarObj::AStarObj()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	this->SetRootComponent(mesh);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> SquareMesh(TEXT("/Engine/BasicShapes/Sphere"));
	Asset = SquareMesh.Object;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> ChessMe(TEXT("/Game/Models/ChessUnreal/Geometries/Chess"));
	ChessMesh = ChessMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> BalloonMe(TEXT("/Game/Models/BalloonUnreal/Geometries/Balloon"));
	BalloonMesh = BalloonMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> ApplianceMe(TEXT("/Game/Models/ApplianceUnreal/Geometries/ApplianceStar"));
	ApplianceMesh = ApplianceMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> BonsaiMe(TEXT("/Game/Models/BonsaiUnreal/Geometries/Bonsai"));
	BonsaiMesh = BonsaiMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> GeodeMe(TEXT("/Engine/BasicShapes/Sphere"));
	GeodeMesh = GeodeMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> DuckMe(TEXT("/Game/Models/DuckUnreal/Geometries/Duck"));
	DuckMesh = DuckMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> JetMe(TEXT("/Game/Models/PlaneUnreal/Geometries/Plane"));
	PlaneMesh = JetMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> RadioMe(TEXT("/Game/Models/RadioUnreal/Geometries/Speaker"));
	RadioMesh = RadioMe.Object;

	const ConstructorHelpers::FObjectFinder<UMaterial> ChessMa(TEXT("/Game/Models/ChessUnreal/Materials/ChessColor"));
	ChessMaterial = ChessMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> BalloonMa(TEXT("/Game/Models/BalloonUnreal/Materials/BalloonUnreal"));
	BalloonMaterial = BalloonMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> ApplianceMa(TEXT("/Game/Models/ApplianceUnreal/Materials/ApplianceColor"));
	ApplianceMaterial = ApplianceMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> BonsaiWoodMa(TEXT("/Game/Models/BonsaiUnreal/Materials/WoodColor"));
	BonsaiWoodMaterial = BonsaiWoodMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> BonsaiLeavesWoodMa(TEXT("/Game/Models/BonsaiUnreal/Materials/LeavesColor"));
	BonsaiLeavesMaterial = BonsaiLeavesWoodMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> BonsaiGrassMa(TEXT("/Game/Models/BonsaiUnreal/Materials/GrassColor"));
	BonsaiGrassMaterial = BonsaiGrassMa.Object;
	// const ConstructorHelpers::FObjectFinder<UMaterial> GeodeMa(TEXT("/Game/Models/"));
	// GeodeMaterial = GeodeMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> DuckDuckMa(TEXT("/Game/Models/DuckUnreal/Materials/DuckColor"));
	DuckDuckMaterial = DuckDuckMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> DuckSwanMa(TEXT("/Game/Models/DuckUnreal/Materials/SwanColor"));
	DuckSwanMaterial = DuckSwanMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> DuckBowlMa(TEXT("/Game/Models/DuckUnreal/Materials/BowlColor"));
	DuckBowlMaterial = DuckBowlMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> PlaneMa(TEXT("/Game/Models/PlaneUnreal/Materials/PlaneColor"));
	PlaneMaterial = PlaneMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> RadioMa(TEXT("/Game/Models/RadioUnreal/Materials/RadioColor"));
	RadioMaterial = RadioMa.Object;




	//const ConstructorHelpers::FObjectFinder<UMaterial> MaterialObj(TEXT("/Engine/BasicShapes/BasicShapeMaterial")); 

	//const ConstructorHelpers::FObjectFinder<UMaterial> MaterialObj(TEXT("/Game/Star_Material"));
	//mesh->SetMaterial(0, MaterialObj.Object);

	// DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialObj.Object, mesh);

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
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Timeline loaded");
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName{ TEXT("TwirlControls") });
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

	// Set the correct mesh
	if (!hasChangedMesh)
	{
		SetActorRelativeScale3D(FVector::OneVector * 50);
		mesh->SetStaticMesh(Asset);
		hasChangedMesh = true;
	}

	// Set a new location for the star
	FVector NewLocation = FVector::ZeroVector;

	// Increase distance from 0, 0, 0 based on deltaTime and current distance
	if (distance < 50000) {
		distance += DeltaTime * 10000;
	}
	else if (distance >= 50000) {
		distance += DeltaTime * 500;
	}
	else if (distance >= 10000) {
		distance += DeltaTime * 100;
	}
	else if (distance >= 100000) {
		distance += DeltaTime * 10;
	}
	else if (distance >= 150000) {
		distance += DeltaTime * 1;
	}
	else if (distance >= 200000) {
		distance += DeltaTime * .1;
	}
	else {
		distance = distance;
	}

	// calculate the direction relative to 0,0,0 by normalizing the position of the star
	FVector direction = starData.position;
	direction.Normalize();


	// increase the current rotation angle based on deltaTime and distance from 0,0,0
	angleAxis += (DeltaTime * orbitSpeed) / (distance / 1000000);
	if (angleAxis >= 360)
	{
		angleAxis = 0;
	}

	// Rotate the direction of the rotation angle around 0, 0, 0
	FVector RotationValue = direction.RotateAngleAxis(angleAxis, FVector(0, 0, 1));
	RotationValue.Normalize();

	// Set the actor rotation to the new location
	NewLocation = distance * RotationValue;

	// set the new actor location
	SetActorLocation(NewLocation, false, 0, ETeleportType::None);

	// rotate the star in place
	RotateValueX += RotateSpeedX;
	RotateValueZ += RotateSpeedZ;

	//if the user hits the twirl button, this will start the twirl
	if (startRotation)
	{
		RotateValueY += 5.0f;
		FQuat NewRotation = FQuat(FRotator(RotateValueX, RotateValueY, RotateValueZ));

		// set the new actor rotation
		SetActorRelativeRotation(NewRotation);

		// check to see if it's halfway there (if it starts at 0, halfway is 180 and vice versa)
		if ((!startsHalfway && GetActorRotation().Yaw < 0) || (startsHalfway && GetActorRotation().Yaw >= 0))
		{
			halfwayRotation = true;
		}

		// end the twirl animation
		if (halfwayRotation && ((!startsHalfway && GetActorRotation().Yaw >= 0) || (startsHalfway && GetActorRotation().Yaw < 0)))
		{
			halfwayRotation = false;
			startRotation = false;
			FQuat ResetRotation = FQuat(FRotator(RotateValueX, 0, RotateValueZ));

			// set the new actor rotation
			SetActorRelativeRotation(ResetRotation);
		}
	}
	else
	{
		RotateValueY = 0;

		FQuat NewRotation = FQuat(FRotator(RotateValueX, RotateValueY, RotateValueZ));
		SetActorRelativeRotation(NewRotation);
	}

	FQuat NewRotation = FQuat(FRotator(RotateValueX, RotateValueY, RotateValueZ));

	// set the new actor rotation
	SetActorRelativeRotation(NewRotation);

	// Make the Camera Track this star if it is being tracked (if more than one is being tracked, it will track whichever one does this last)
	if (trackCamera) {
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FRotator currentRotation = playerController->GetControlRotation();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, GetActorLocation());

		playerController->RotationInput = targetRotation - currentRotation;
		playerController->UpdateRotation(DeltaTime);
	}
}

// Sets everything up because for some reason I can't make it an argument
void AStarObj::SetUpData(FStarData data)
{
	starData = data;

	float hue = starData.color * 6;
	TArray<float> hueToRGB = { FMath::Clamp(abs(hue - 3) - 1, 0, 1), FMath::Clamp(2 - abs(hue - 2), 0, 1), FMath::Clamp(2 - abs(hue - 4), 0, 1) };
	// SetActorRelativeLocation(starData.position);

	distance = FMath::Abs(FDateTime::Now().ToUnixTimestamp() - starData.birthDate.ToUnixTimestamp());
	if (distance < 50000) {
		distance = 50000;
	}
	orbitSpeed = FMath::RandRange(0.1, 1.0); //2.0, 8.5
	angleAxis = 0;
	RotateSpeedX = FMath::RandRange(0.1, 0.5);
	RotateSpeedZ = FMath::RandRange(0.1, 0.5);

	// float shadeRadians = starData.shade * 2 * PI;
	// float saturation = 0.75 + 0.25*cos(shadeRadians);
	// float value = 0.75 + 0.25*sin(shadeRadians);

	TArray<float> colorArray = {};

	for (int i = 0; i < 3; i++)
	{
		colorArray.Add(FMath::Lerp(hueToRGB[i], starData.shade, 0.35));
		// 	colorArray.Add(FMath::Lerp(1, hueToRGB[i], saturation) * value);
	}

	color = FLinearColor(colorArray[0], colorArray[1], colorArray[2]);

	// set mesh and materials
	switch (starData.shape)
	{
	case 0:
		// Chess Piece
		// Load static mesh models
		Asset = ChessMesh;
		// Set mesh
		// const ConstructorHelpers::FObjectFinder<UMaterial> ChessColor(TEXT("/Game/Models/ChessUnreal/Materials/ChessColor"));
		DynamicMaterial = UMaterialInstanceDynamic::Create(ChessMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(1, DynamicMaterial);
		break;
	case 1:
		// Balloon
		// Load static mesh models
		Asset = BalloonMesh;
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(BalloonMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(1, DynamicMaterial);
		mesh->SetMaterial(3, DynamicMaterial);
		mesh->SetMaterial(5, DynamicMaterial);
		mesh->SetMaterial(6, DynamicMaterial);
		mesh->SetMaterial(8, DynamicMaterial);
		mesh->SetMaterial(10, DynamicMaterial);
		mesh->SetMaterial(12, DynamicMaterial);
		break;
	case 2:
		// Appliance
		// Load static mesh models
		Asset = ApplianceMesh;
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(ApplianceMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(1, DynamicMaterial);
		mesh->SetMaterial(4, DynamicMaterial);
		mesh->SetMaterial(5, DynamicMaterial);
		mesh->SetMaterial(7, DynamicMaterial);
		mesh->SetMaterial(8, DynamicMaterial);
		mesh->SetMaterial(9, DynamicMaterial);
		mesh->SetMaterial(10, DynamicMaterial);
		mesh->SetMaterial(11, DynamicMaterial);
		mesh->SetMaterial(12, DynamicMaterial);
		break;
	case 3:
		// Bonsai
		// Load static mesh models
		Asset = BonsaiMesh;
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(BonsaiGrassMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(0, DynamicMaterial);

		DynamicMaterial = UMaterialInstanceDynamic::Create(BonsaiWoodMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(4, DynamicMaterial);
		mesh->SetMaterial(12, DynamicMaterial);
		mesh->SetMaterial(13, DynamicMaterial);

		DynamicMaterial = UMaterialInstanceDynamic::Create(BonsaiLeavesMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(10, DynamicMaterial);
		break;
	case 4:
		// Geode
		// Load static mesh models
		Asset = GeodeMesh;
		// const ConstructorHelpers::FObjectFinder<UStaticMesh> GeodeMesh(TEXT("/Game/Models/GeodeUnreal/Geometries/Geode"));
		// Geode = GeodeMesh.Object;
		break;
	case 5:
		// Duck
		// Load static mesh models
		Asset = DuckMesh;
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(DuckDuckMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(6, DynamicMaterial);

		DynamicMaterial = UMaterialInstanceDynamic::Create(DuckSwanMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(4, DynamicMaterial);

		DynamicMaterial = UMaterialInstanceDynamic::Create(DuckBowlMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(2, DynamicMaterial);
		break;
	case 6:
		// Plane
		// Load static mesh models
		Asset = PlaneMesh;
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(PlaneMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(0, DynamicMaterial);
		mesh->SetMaterial(1, DynamicMaterial);
		break;
	case 7:
		// Radio
		// Load static mesh models
		Asset = RadioMesh;
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(RadioMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(0, DynamicMaterial);
		mesh->SetMaterial(3, DynamicMaterial);
		mesh->SetMaterial(12, DynamicMaterial);
		mesh->SetMaterial(13, DynamicMaterial);
		mesh->SetMaterial(15, DynamicMaterial);
		mesh->SetMaterial(18, DynamicMaterial);
		break;
	default:
		break;
	}


	//Test for shape
}

void AStarObj::SparkleAnimation()
{

}

void AStarObj::TwirlAnimation()
{
	//Set the yaw from 0 to 360

	startsHalfway = GetActorRotation().Yaw == 180 || GetActorRotation().Yaw == -180;

	// if(startsHalfway)
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "180!");
	// else
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "0!");

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
