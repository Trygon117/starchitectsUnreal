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

	const ConstructorHelpers::FObjectFinder<UMaterial> MaterialObj(TEXT("/Engine/BasicShapes/BasicShapeMaterial")); 
	mesh->SetMaterial(0, MaterialObj.Object);

	//Load every shape possible

}

// Called when the game starts or when spawned
void AStarObj::BeginPlay()
{
	Super::BeginPlay();

	isGlowing = false;

	mesh->SetStaticMesh(Asset);

	//Based off of the int in the star data, set the static mesh to that

	//mesh::GetMaterial(0) - get/change the properties of the material

	//FString pos = this->GetActorLocation().ToString();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Position: " + pos));
	
}

// Called every frame
void AStarObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set actor to position
	this->SetActorRelativeLocation(FMath::Lerp(this->GetActorLocation(), starData.position, DeltaTime));
	//Lerp - Linear
	//SmoothStep - Hermite
	//InterpEaseInOut - Ease In/Out

}

//Sets everything up because for some reason I can't make it an argument
void AStarObj::SetUpData(FStarData data)
{
	starData = data;
}

