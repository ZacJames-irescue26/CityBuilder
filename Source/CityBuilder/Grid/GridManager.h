// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "GridManager.generated.h"

UENUM(BlueprintType)
enum class  ESizeType : uint8 {
	Size1X1,
	Size2X1,
	Size2X2,
	Size2X3,
	Size2X4,
	Size4X1,
	Size4X2
};

UCLASS()
class CITYBUILDER_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();
	UPROPERTY(EditAnywhere)
	int GridWidth;
	UPROPERTY(EditAnywhere)
	int GridHeight;
	UPROPERTY(EditAnywhere)
	float TileSize;
	TArray<TArray<ATile*>> GridVector;


	UPROPERTY(EditAnywhere)
	TSubclassOf<ATile> TileToSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float AlignToGrid(float value, float size);
	FVector2D WorldToGridIndex(FVector2D Pos);
	bool CheckGridIndex(FVector2D Pos);
	bool IsOccupied(FVector2D Pos);
	FVector2D WorldToGrid(FVector position);
};
