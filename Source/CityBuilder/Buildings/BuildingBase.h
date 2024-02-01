// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CityBuilder/Grid/GridManager.h"
#include "CityBuilder/CityBuilderPlayerController.h"
#include "CityBuilder/StructsandEnums.h"
#include "BuildingBase.generated.h"





UCLASS()
class CITYBUILDER_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	FResourceStats stats;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AGridManager* GridManager;
	bool IsPlaced = false;
	ACityBuilderPlayerController* PlayerController;
	UPROPERTY(EditAnywhere)
	ESizeType Size;


private:
	FVector Corner1;
	FVector Corner2;
	FVector Corner3;
	FVector Corner4;
	FVector Corner5;
	FVector Corner6;
	FVector Corner7;
	FVector Corner8;
};
