// Fill out your copyright notice in the Description page of Project Settings.


#include "TrajectoryActor.h"

// Sets default values
ATrajectoryActor::ATrajectoryActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Size = FVector(1, 1, 1);
	Color = FLinearColor(1, 1, 0, 1);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	InstancedStaticMesh = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("InstacedStaticMeshComponent"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	UStaticMesh* Mesh = MeshAsset.Object;
	InstancedStaticMesh->SetStaticMesh(Mesh);

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor'"));
	UMaterial* Material = MaterialAsset.Object;
	InstancedStaticMesh->SetMaterial(0, Material);

	InstancedStaticMesh->SetupAttachment(GetRootComponent());
}

	

// Called when the game starts or when spawned
void ATrajectoryActor::BeginPlay()
{
	Super::BeginPlay();

	material = UMaterialInstanceDynamic::Create(InstancedStaticMesh->GetMaterial(0), NULL);
	material->SetVectorParameterValue(FName("Color"), Color);
	InstancedStaticMesh->SetMaterial(0, material);

	// Init dummy position array 
	TArray<FTransform> PosArray;

	for (int i = 0; i < 10; i++)
	{
		PosArray.Add(FTransform(FRotator(0, 0, 0), FVector(i * 300, 0, 0), Size));
	}

	for (int i = 0; i < PosArray.Num(); i++)
	{
		InstancedStaticMesh->AddInstance(PosArray[i]);
	}



}
	

// Called every frame
void ATrajectoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

