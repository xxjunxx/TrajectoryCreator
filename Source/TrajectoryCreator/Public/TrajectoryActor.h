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

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	//UStaticMesh * StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	FVector Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	UHierarchicalInstancedStaticMeshComponent * InstancedStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory Setting")
	UMaterialInstanceDynamic* material;

};
