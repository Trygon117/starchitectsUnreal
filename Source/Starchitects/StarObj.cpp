// Fill out your copyright notice in the Description page of Project Settings.

#include "StarObj.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponentPoolMethodEnum.h"
#include "Math/Vector.h"
#include "StarchitectsGameInstance.h"
#include "Misc/DateTime.h"

// Sets default values
AStarObj::AStarObj()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	this->SetRootComponent(mesh);

	// load Niagara particle systems
	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> DefaultParticleSystem(TEXT("/Game/Particles/NS_Default"));
	DefaultNiagaraSystem = DefaultParticleSystem.Object;
	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> SparkleParticleSystem(TEXT("/Game/Particles/NS_Sparkle"));
	SparkleNiagaraSystem = SparkleParticleSystem.Object;
	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> SuperNovaParticleSystem(TEXT("/Game/Particles/NS_SuperNova"));
	SuperNovaNiagaraSystem = SuperNovaParticleSystem.Object;
	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> TwirlParticleSystem(TEXT("/Game/Particles/NS_Twirl"));
	TwirlNiagaraSystem = TwirlParticleSystem.Object;


	// load meshes
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
	const ConstructorHelpers::FObjectFinder<UStaticMesh> GeodeMe(TEXT("/Game/Models/GeodeUnreal/Geometries/GeodeStar"));
	GeodeMesh = GeodeMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> DuckMe(TEXT("/Game/Models/DuckUnreal/Geometries/Duck"));
	DuckMesh = DuckMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> JetMe(TEXT("/Game/Models/PlaneUnreal/Geometries/Plane"));
	PlaneMesh = JetMe.Object;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> RadioMe(TEXT("/Game/Models/RadioUnreal/Geometries/Speaker"));
	RadioMesh = RadioMe.Object;

	// load materials
	const ConstructorHelpers::FObjectFinder<UMaterial> GlowMa(TEXT("/Game/Models/Glow"));
	GlowMaterial = GlowMa.Object;
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
	const ConstructorHelpers::FObjectFinder<UMaterial> GeodeMa(TEXT("/Game/Models/GeodeUnreal/Materials/CrystalColor"));
	GeodeMaterial = GeodeMa.Object;
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

	// load particle materials
	const ConstructorHelpers::FObjectFinder<UMaterial> CloverMa(TEXT("/Game/Particles/Materials/cloverMaterial"));
	CloverMaterial = CloverMa.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> Star4Ma(TEXT("/Game/Particles/Materials/star4Material"));
	Star4Material = Star4Ma.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> Star5Ma(TEXT("/Game/Particles/Materials/star5Material"));
	Star5Material = Star5Ma.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> SwirlMa(TEXT("/Game/Particles/Materials/swirlMaterial"));
	SwirlMaterial = SwirlMa.Object;

	rotateLimit = 2;


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

	// StarCurve = NewObject<UCurveFloat>(this);
	// FKeyHandle KeyHandle = StarCurve->FloatCurve.UpdateOrAddKey(0.f, 0.f);
	// StarCurve->FloatCurve.UpdateOrAddKey(1.f, 1.f);
	// StarCurve->FloatCurve.SetKeyInterpMode(KeyHandle, ERichCurveInterpMode::RCIM_Cubic, true);

	// TwirlTimeline = NewObject<UTimelineComponent>(this);
	// SuperNovaTimeline = NewObject<UTimelineComponent>(this);
	// SparkleTimeline = NewObject<UTimelineComponent>(this);

	// // if (StarCurve)
	// // {
	// 	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Timeline loaded");
	// 	// FOnTimelineFloat TimelineCallback;

	// FOnTimelineEventStatic TwirlTimelineFinishedCallback;
	// // TwirlTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TwirlControls") });
	// TwirlTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("FinishTwirlAnimation") });
	// TwirlTimeline->SetTimelineLength(5.f);
	// // TwirlTimeline->AddInterpFloat(StarCurve, TimelineCallback);
	// TwirlTimeline->SetTimelineFinishedFunc(TwirlTimelineFinishedCallback);

	// FOnTimelineEventStatic SuperNovaTimelineFinishedCallback;
	// SuperNovaTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("FinishSuperNovaAnimation") });
	// SuperNovaTimeline->SetTimelineLength(5.f);
	// SuperNovaTimeline->SetTimelineFinishedFunc(SuperNovaTimelineFinishedCallback);

	// FOnTimelineEventStatic SparkleTimelineFinishedCallback;
	// SparkleTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("FinishSparkleAnimation") });
	// SparkleTimeline->SetTimelineLength(5.f);
	// SparkleTimeline->SetTimelineFinishedFunc(SparkleTimelineFinishedCallback);

	//TwirlTimeline->PlayFromStart();
// }

}

// Called every frame
void AStarObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set the correct mesh
	if (!hasChangedMesh)
	{
		SetActorRelativeScale3D(FVector::OneVector * 10);
		mesh->SetStaticMesh(Asset);
		hasChangedMesh = true;
	}

	// Set a new location for the star
	FVector NewLocation = FVector::ZeroVector;

	// Increase distance from 0, 0, 0 based on deltaTime and current distance
	if (distance < 10000) {
		distance += DeltaTime * 1000;
	}
	else if (distance < 20000) {
		distance += DeltaTime * 100;
	}
	else if (distance < 50000) {
		distance += DeltaTime * 10;
	}
	else if (distance <= 100000) {
		distance += DeltaTime;
	}
	else {
		distance = 100000;
	}

	// update orbitSpeed based on distance (clamp so min speed is 5 & max speed is 25)
	orbitSpeed = FMath::Clamp(baseSpeed / (distance / 50000), 5.f, 25.f);

	// calculate the direction relative to 0,0,0 by normalizing the position of the star
	FVector direction = starData.position;
	direction.Normalize();


	// increase the current rotation angle based on deltaTime
	angleAxis += (DeltaTime * orbitSpeed); // (distance / 250000);
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
	// if (startRotation)
	// {
	// 	RotateValueY += 5.0f;
	// 	FQuat NewRotation = FQuat(FRotator(RotateValueX, RotateValueY, RotateValueZ));

	// 	// set the new actor rotation
	// 	SetActorRelativeRotation(NewRotation);

	// 	// check to see if it's halfway there (if it starts at 0, halfway is 180 and vice versa)
	// 	if ((!startsHalfway && GetActorRotation().Yaw < 0) || (startsHalfway && GetActorRotation().Yaw >= 0))
	// 	{
	// 		halfwayRotation = true;
	// 	}

	// 	// end the twirl animation
	// 	if (halfwayRotation && ((!startsHalfway && GetActorRotation().Yaw >= 0) || (startsHalfway && GetActorRotation().Yaw < 0)))
	// 	{
	// 		halfwayRotation = false;
	// 		z++;

	// 		if (z >= rotateLimit)
	// 		{
	// 			startRotation = false;
	// 			FQuat ResetRotation = FQuat(FRotator(RotateValueX, 0, RotateValueZ));

	// 			// set the new actor rotation
	// 			SetActorRelativeRotation(ResetRotation);
	// 			z = 0;
	// 		}

	// 	}
	// }
	// else
	// {
	// 	//Set the default rotate y value to 0
	// 	RotateValueY = 0;

	// 	FQuat NewRotation = FQuat(FRotator(RotateValueX, RotateValueY, RotateValueZ));
	// 	SetActorRelativeRotation(NewRotation);
	// }

	FQuat NewRotation = FQuat(FRotator(RotateValueX, RotateValueY, RotateValueZ));

	// set the new actor rotation
	SetActorRelativeRotation(NewRotation);

	if (playingAnimation && (FDateTime::Now().ToUnixTimestamp() - animationStart) > 2) { // 2 seconds
		FinishAnimation();
	}
}

// Sets everything up because for some reason I can't make it an argument
void AStarObj::SetUpData(FStarData data)
{
	starData = data;

	float hue = starData.color * 6;
	TArray<float> hueToRGB = { FMath::Clamp(abs(hue - 3) - 1, 0, 1), FMath::Clamp(2 - abs(hue - 2), 0, 1), FMath::Clamp(2 - abs(hue - 4), 0, 1) };


	float particleHue = starData.particleColor * 6;
	TArray<float> particleHueToRGB = { FMath::Clamp(abs(particleHue - 3) - 1, 0, 1), FMath::Clamp(2 - abs(particleHue - 2), 0, 1), FMath::Clamp(2 - abs(particleHue - 4), 0, 1) };

	distance = starData.distance;

	baseSpeed = FMath::RandRange(7, 14);
	angleAxis = 0;
	RotateSpeedX = FMath::RandRange(0.1, 0.5);
	RotateSpeedZ = FMath::RandRange(0.1, 0.5);

	TArray<float> particleColorArray = {};

	for (int i = 0; i < 3; i++)
	{
		particleColorArray.Add(FMath::Lerp(particleHueToRGB[i], starData.particleShade, 0.5));
	}

	particleColor = FLinearColor(particleColorArray[0], particleColorArray[1], particleColorArray[2]);

	switch (starData.particleType)
	{
	case 0:
		// clover
		ParticleMaterial = CloverMaterial;
		break;
	case 1:
		// star 5
		ParticleMaterial = Star5Material;
		break;
	case 2:
		// swirl
		ParticleMaterial = SwirlMaterial;
		break;
	default:
		// 
		break;
	}

	// NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, starData.position, FRotator(1.f), FVector(10.f), true, true, ENCPoolMethod::AutoRelease, true);
	DefaultNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(DefaultNiagaraSystem, this->RootComponent, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
	DynamicMaterial = UMaterialInstanceDynamic::Create(ParticleMaterial, DefaultNiagaraComponent);
	DynamicMaterial->SetVectorParameterValue("ParticleColor", particleColor);
	DefaultNiagaraComponent->SetVariableMaterial(FName("particle material"), DynamicMaterial);
	DefaultNiagaraComponent->Activate();

	TArray<float> colorArray = {};

	for (int i = 0; i < 3; i++)
	{
		colorArray.Add(FMath::Lerp(hueToRGB[i], starData.shade, 0.5));
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
		DynamicMaterial = UMaterialInstanceDynamic::Create(GlowMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(0, DynamicMaterial);
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
		DynamicMaterial = UMaterialInstanceDynamic::Create(GlowMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(16, DynamicMaterial);
		mesh->SetMaterial(29, DynamicMaterial);
		mesh->SetMaterial(30, DynamicMaterial);

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
		DynamicMaterial = UMaterialInstanceDynamic::Create(GlowMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(1, DynamicMaterial);
		mesh->SetMaterial(11, DynamicMaterial);

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
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(GlowMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(1, DynamicMaterial);
		mesh->SetMaterial(5, DynamicMaterial);
		mesh->SetMaterial(6, DynamicMaterial);

		DynamicMaterial = UMaterialInstanceDynamic::Create(GeodeMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(0, DynamicMaterial);
		break;
	case 5:
		// Duck
		// Load static mesh models
		Asset = DuckMesh;
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(GlowMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(8, DynamicMaterial);

		DynamicMaterial = UMaterialInstanceDynamic::Create(DuckDuckMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(0, DynamicMaterial);
		mesh->SetMaterial(11, DynamicMaterial);

		DynamicMaterial = UMaterialInstanceDynamic::Create(DuckSwanMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(9, DynamicMaterial);

		DynamicMaterial = UMaterialInstanceDynamic::Create(DuckBowlMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(1, DynamicMaterial);
		break;
	case 6:
		// Plane
		// Load static mesh models
		Asset = PlaneMesh;
		// Set mesh
		DynamicMaterial = UMaterialInstanceDynamic::Create(GlowMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(6, DynamicMaterial);

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
		DynamicMaterial = UMaterialInstanceDynamic::Create(GlowMaterial, mesh);
		DynamicMaterial->SetVectorParameterValue("StarColor", color);
		mesh->SetMaterial(5, DynamicMaterial);
		mesh->SetMaterial(17, DynamicMaterial);

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
	if (SuperNovaNiagaraComponent) {
		SuperNovaNiagaraComponent->Deactivate();
	}
	if (TwirlNiagaraComponent) {
		TwirlNiagaraComponent->Deactivate();
	}
	if (DefaultNiagaraComponent) {
		DefaultNiagaraComponent->Deactivate();
	}
	SparkleNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(SparkleNiagaraSystem, this->RootComponent, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
	DynamicMaterial = UMaterialInstanceDynamic::Create(ParticleMaterial, SparkleNiagaraComponent);
	DynamicMaterial->SetVectorParameterValue("ParticleColor", particleColor);
	SparkleNiagaraComponent->SetVariableMaterial(FName("particle material"), DynamicMaterial);
	SparkleNiagaraComponent->Activate();

	playingAnimation = true;
	animationStart = FDateTime::Now().ToUnixTimestamp();
}

void AStarObj::TwirlAnimation()
{
	if (SuperNovaNiagaraComponent) {
		SuperNovaNiagaraComponent->Deactivate();
	}
	if (SparkleNiagaraComponent) {
		SparkleNiagaraComponent->Deactivate();
	}
	if (DefaultNiagaraComponent) {
		DefaultNiagaraComponent->Deactivate();
	}
	TwirlNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TwirlNiagaraSystem, this->RootComponent, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
	DynamicMaterial = UMaterialInstanceDynamic::Create(ParticleMaterial, TwirlNiagaraComponent);
	DynamicMaterial->SetVectorParameterValue("ParticleColor", particleColor);
	TwirlNiagaraComponent->SetVariableMaterial(FName("particle material"), DynamicMaterial);
	TwirlNiagaraComponent->Activate();

	playingAnimation = true;
	animationStart = FDateTime::Now().ToUnixTimestamp();
}

void AStarObj::SupernovaAnimation()
{
	if (TwirlNiagaraComponent) {
		TwirlNiagaraComponent->Deactivate();
	}
	if (SparkleNiagaraComponent) {
		SparkleNiagaraComponent->Deactivate();
	}
	if (DefaultNiagaraComponent) {
		DefaultNiagaraComponent->Deactivate();
	}
	SuperNovaNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(SuperNovaNiagaraSystem, this->RootComponent, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
	DynamicMaterial = UMaterialInstanceDynamic::Create(ParticleMaterial, SuperNovaNiagaraComponent);
	DynamicMaterial->SetVectorParameterValue("ParticleColor", particleColor);
	SuperNovaNiagaraComponent->SetVariableMaterial(FName("particle material"), DynamicMaterial);
	SuperNovaNiagaraComponent->Activate();

	playingAnimation = true;
	animationStart = FDateTime::Now().ToUnixTimestamp();
}

void AStarObj::FinishAnimation()
{
	// animationStart = 0;
	playingAnimation = false;

	if (SuperNovaNiagaraComponent) {
		SuperNovaNiagaraComponent->Deactivate();
	}
	if (TwirlNiagaraComponent) {
		TwirlNiagaraComponent->Deactivate();
	}
	if (SparkleNiagaraComponent) {
		SparkleNiagaraComponent->Deactivate();
	}

	DefaultNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(DefaultNiagaraSystem, this->RootComponent, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
	DynamicMaterial = UMaterialInstanceDynamic::Create(ParticleMaterial, DefaultNiagaraComponent);
	DynamicMaterial->SetVectorParameterValue("ParticleColor", particleColor);
	DefaultNiagaraComponent->SetVariableMaterial(FName("particle material"), DynamicMaterial);

	DefaultNiagaraComponent->Activate();

	UStarchitectsGameInstance* GameInstance = Cast<UStarchitectsGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance) {
		GameInstance->EndAnimations(ID);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("didn't end animations."));
	}
}