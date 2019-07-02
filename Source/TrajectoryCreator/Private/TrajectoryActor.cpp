// Fill out your copyright notice in the Description page of Project Settings.
#include "TrajectoryActor.h"

// Sets default values
ATrajectoryActor::ATrajectoryActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NrOfMeshes = 5000;

	SetupMeshesAndMaterial();

	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstacedStaticMeshComponent"));

	InstancedStaticMesh->SetStaticMesh(Mesh);

	InstancedStaticMesh->SetMaterial(0, Material);

	InstancedStaticMesh->SetupAttachment(GetRootComponent());

	InstancedStaticMesh->SetCullDistances(50, 1000);



}


// Called when the game starts or when spawned
void ATrajectoryActor::BeginPlay()
{
	Super::BeginPlay();

	SetupTrajectoryPath();

	CreateTrajectory();
}
	
// Called every frame
void ATrajectoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}



void ATrajectoryActor::SetupMeshesAndMaterial()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/TrajectoryCreator/SM_Box1cm.SM_Box1cm'"));

	Mesh = MeshAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/TrajectoryCreator/M_TrajectoryDynamicMaterial.M_TrajectoryDynamicMaterial'"));
	Material = MaterialAsset.Object;
}

void ATrajectoryActor::SetupTrajectoryPath()
{

	for (int i = 0; i < NrOfMeshes; i++)
	{
		PosArray1.Add(FTransform(FRotator(0, 0, 0), FVector(i * 3, 0, 0), Size));
		PosArray2.Add(FTransform(FRotator(0, 0, 0), FVector(0, i * 3, 0), Size));
		PosArray3.Add(FTransform(FRotator(0, 0, 0), FVector(0, 0, i * 3), Size));
	}
}

void ATrajectoryActor::CreateTrajectory()
{
	for (int i = 0; i < PosArray1.Num(); i++)
	{
		InstancedStaticMesh->AddInstance(PosArray1[i]);
	}
}



void ATrajectoryActor::UpdateTrajectoryPath(int32 currentPath)
{
	switch (currentPath)
	{
	case 1:
		for (int i = 0; i < PosArray1.Num(); i++)
		{
			InstancedStaticMesh->UpdateInstanceTransform(i, PosArray1[i], false, true);
		}
		break;
	case 2:
		for (int i = 0; i < PosArray2.Num(); i++)
		{
			InstancedStaticMesh->UpdateInstanceTransform(i, PosArray2[i], false, true);
		}
		break;
	case 3:
		for (int i = 0; i < PosArray3.Num(); i++)
		{
			InstancedStaticMesh->UpdateInstanceTransform(i, PosArray3[i], false, true);
		}
		break;
	default:
		break;
	}
}

void ATrajectoryActor::ChangeTrajectoryPath() 
{
	currentPath = FMath::RandRange(1, 3);
	UpdateTrajectoryPath(currentPath);
}



void ATrajectoryActor::ChangeColor() {
	Color = FLinearColor(FMath::RandRange(0, 1), FMath::RandRange(0, 1), FMath::RandRange(0, 1), 1);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	DynamicMaterial->SetVectorParameterValue(FName("Color"), Color);
	InstancedStaticMesh->SetMaterial(0, DynamicMaterial);
}

void ATrajectoryActor::ChangeSize() 
{
	int32 Scale = FMath::RandRange(1, 6);
	Size = FVector(0.2 *  Scale, 0.2 * Scale, 0.2 * Scale);
	
	for (auto& Pos : PosArray1)
	{
		Pos.SetScale3D(Size);
	}
	for (auto& Pos : PosArray2)
	{
		Pos.SetScale3D(Size);
	}
	for (auto& Pos : PosArray3)
	{
		Pos.SetScale3D(Size);
	}
	UpdateTrajectoryPath(currentPath);
}

void ATrajectoryActor::ChangeMesh() 
{
	//int32 MeshType = FMath::RandRange(1, 4);
	//switch (MeshType)
	//{
	//case 1:
	//	InstancedStaticMesh->SetStaticMesh(Meshes[0]);
	//	InstancedStaticMesh->SetMaterial(0, Material);
	//	break;
	//case 2:
	//	InstancedStaticMesh->SetStaticMesh(Meshes[1]);
	//	InstancedStaticMesh->SetMaterial(0, Material);
	//	break;
	//case 3:
	//	InstancedStaticMesh->SetStaticMesh(Meshes[2]);
	//	InstancedStaticMesh->SetMaterial(0, Material);
	//	break;
	//case 4:
	//	InstancedStaticMesh->SetStaticMesh(Meshes[3]);
	//	InstancedStaticMesh->SetMaterial(0, Material);
	//	break;
	//default:
	//	break;
	//}
}


