// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

// Sets default values
AGridManager::AGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	GridVector.SetNumZeroed(GridWidth);
	for (int i = 0; i < GridVector.Num(); i++)
	{
		GridVector[i].SetNumZeroed(GridHeight);
	}

	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			float xPos = x * TileSize;
			float yPos = y * TileSize;
			ATile* Tile = GetWorld()->SpawnActor<ATile>(TileToSpawn, FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator );
			Tile->TileIndex = FIntPoint(x, y);

			GridVector[x][y] = Tile;
		
		}
	}
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AGridManager::AlignToGrid(float value, float size)
{
	return std::floor(value / size) * size;
}

FVector2D AGridManager::WorldToGridIndex(FVector2D Pos)
{
	int xPos = FMath::RoundToInt((Pos.X / TileSize));
	int yPos = FMath::RoundToInt((Pos.Y / TileSize));
	//Hack for some reason wont divide by 200
	return FVector2D(xPos, yPos);
}
bool AGridManager::CheckGridIndex(FVector2D Pos)
{
	if (Pos.X >= 0 && Pos.X < GridVector.Num() && Pos.Y >= 0 && Pos.Y < GridVector[0].Num())
	{
		return true;
	}
	return false;
}

bool AGridManager::IsOccupied(FVector2D Pos)
{
	if (!CheckGridIndex(Pos))
	{
		UE_LOG(LogTemp, Warning, TEXT("grid index is outside the grid"));
		return false;
	}

	if (GridVector[Pos.X][Pos.Y]->IsOccupied)
	{
		return true;
	}
	return false;
}
