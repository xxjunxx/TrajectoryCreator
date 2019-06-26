// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TrajectoryActor.generated.h"

UCLASS()
class TRAJECTORYCREATOR_API ATrajectoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrajectoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();

	void CreateTrajectory();
	
	void SetupMeshesAndMaterial();

	void SetupComponents();

	void SetupTrajectoryPath();

	void UpdateTrajectoryPath(int32 Path);

	void ChangeTrajectoryPath();

	void ChangeColor();
	
	void ChangeSize();

	void ChangeMesh();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	//UStaticMesh * StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	FLinearColor Color = FLinearColor(0, 1, 0, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	FVector Size = FVector(0.1, 0.1, 0.1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	UHierarchicalInstancedStaticMeshComponent * InstancedStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	UMaterialInstanceDynamic* DynamicMaterial;

	TArray<UStaticMesh*> Meshes;
	UMaterial* Material;

private:
	UPROPERTY(EditAnywhere)
	int32 NrOfMeshes;

	int32 currentPath = 1;
	TArray<FTransform> PosArray1;
	TArray<FTransform> PosArray2;
	TArray<FTransform> PosArray3;

	
};
