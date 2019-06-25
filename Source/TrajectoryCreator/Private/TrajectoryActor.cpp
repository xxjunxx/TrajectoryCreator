// Fill out your copyright notice in the Description page of Project Settings.
#include "TrajectoryActor.h"

// Sets default values
ATrajectoryActor::ATrajectoryActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupMeshesAndMaterial();

	SetupTrajectoryPath();

	SetupComponents();
	

	for (int i = 0; i < PosArray1.Num(); i++)
	{
		InstancedStaticMesh->AddInstance(PosArray1[i]);	
	}

}



// Called when the game starts or when spawned
void ATrajectoryActor::BeginPlay()
{
	Super::BeginPlay();

}
	
// Called every frame
void ATrajectoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrajectoryActor::SetupMeshesAndMaterial() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset1(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset2(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset3(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Stairs.SM_Stairs'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset4(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Statue.SM_Statue'"));
	Meshes.Add(MeshAsset1.Object);
	Meshes.Add(MeshAsset2.Object);
	Meshes.Add(MeshAsset3.Object);
	Meshes.Add(MeshAsset4.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor'"));
	Material = MaterialAsset.Object;
}

void ATrajectoryActor::UpdateTrajectoryPath(int32 currentPath) {
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

void ATrajectoryActor::ChangeTrajectoryPath() {
	currentPath = FMath::RandRange(1, 3);
	UpdateTrajectoryPath(currentPath);
}

void ATrajectoryActor::SetupTrajectoryPath() {
	
	for (int i = 0; i < 10; i++)
	{
		PosArray1.Add(FTransform(FRotator(0, 0, 0), FVector(i * 5, 0, 0), Size));
		PosArray2.Add(FTransform(FRotator(0, 0, 0), FVector(0, i * 5, 0), Size));
		PosArray3.Add(FTransform(FRotator(0, 0, 0), FVector(0, 0, i * 5), Size));
	}
}

void ATrajectoryActor::ChangeColor() {
	Color = FLinearColor(FMath::RandRange(0, 1), FMath::RandRange(0, 1), FMath::RandRange(0, 1), 1);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	DynamicMaterial->SetVectorParameterValue(FName("Color"), Color);
	InstancedStaticMesh->SetMaterial(0, DynamicMaterial);
}

void ATrajectoryActor::ChangeSize() {
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

void ATrajectoryActor::ChangeMesh() {
	int32 MeshType = FMath::RandRange(1, 4);
	switch (MeshType)
	{
	case 1:
		InstancedStaticMesh->SetStaticMesh(Meshes[0]);
		InstancedStaticMesh->SetMaterial(0, Material);
		break;
	case 2:
		InstancedStaticMesh->SetStaticMesh(Meshes[1]);
		InstancedStaticMesh->SetMaterial(0, Material);
		break;
	case 3:
		InstancedStaticMesh->SetStaticMesh(Meshes[2]);
		InstancedStaticMesh->SetMaterial(0, Material);
		break;
	case 4:
		InstancedStaticMesh->SetStaticMesh(Meshes[3]);
		InstancedStaticMesh->SetMaterial(0, Material);
		break;
	default:
		break;
	}
}



void ATrajectoryActor::SetupComponents() {
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	InstancedStaticMesh = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("InstacedStaticMeshComponent"));

	InstancedStaticMesh->SetStaticMesh(Meshes[1]);

	
	InstancedStaticMesh->SetMaterial(0, Material);

	InstancedStaticMesh->SetupAttachment(GetRootComponent());
}