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

	const ConstructorHelpers::FObjectFinder<UMaterial> MaterialObj(TEXT("/Engine/BasicShapes/BasicShapeMaterial")); 
	mesh->SetMaterial(0, MaterialObj.Object);

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
	
}

// Called every frame
void AStarObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set actor to position
	//FVector relativePosition = GetTransform().InverseTransformPosition(GetAttachParentActor()->GetActorLocation());
	//FVector relativePosition = GetTransform().InverseTransformPosition(this->GetActorLocation());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Position: " + relativePosition.ToString()));
	this->SetActorRelativeLocation(FMath::Lerp(GetActorLocation(), starData.position, DeltaTime));
	//mesh->SetStaticMesh(Asset);
	//this->SetActorRelativeLocation(starData.position);

	if(!hasChangedMesh)
	{
		if(starData.shape == 0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("A Rook"));
			SetActorRelativeScale3D(FVector::OneVector);
			mesh->SetStaticMesh(Asset);
			hasChangedMesh = true;
		}
		else if(starData.shape == 1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("A Rook"));
			SetActorRelativeScale3D(FVector::OneVector * 25);
			mesh->SetStaticMesh(Rook);
			hasChangedMesh = true;
		}
		else if(starData.shape == 2)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("A Rock"));
			SetActorRelativeScale3D(FVector::OneVector * 25);
			mesh->SetStaticMesh(Rock);
			hasChangedMesh = true;
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
			// SetActorRelativeScale3D(FVector::OneVector * 25);
			// SetActorRelativeScale3D(FVector::OneVector * 25);

	//Test for shape
}

