// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"
#include "Kismet/GameplayStatics.h"
#include "../CityBuilderPlayerController.h"

// Sets default values
ABuildingBase::ABuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	GridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridManager::StaticClass()));
	PlayerController = Cast<ACityBuilderPlayerController>(GetWorld()->GetFirstPlayerController());
	
}

// Called every frame
void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsPlaced)
	{
		if (PlayerController)
		{
			FVector mPos = PlayerController->GetWorldMousePos();
			FVector GridPosition;

			GridPosition.X = GridManager->AlignToGrid(mPos.X, GridManager->TileSize);
			GridPosition.Y = GridManager->AlignToGrid(mPos.Y, GridManager->TileSize);
			GridPosition.Z = mPos.Z;

			if (GridPosition.X / GridManager->TileSize >= 0 && GridPosition.X / GridManager->TileSize >= 0
				&& GridPosition.X / GridManager->TileSize < GridManager->GridWidth && GridPosition.Y / GridManager->TileSize < GridManager->GridHeight)
			{
				this->SetActorLocation(GridPosition);
			}
			FPlayerResources playerResources;
			if (PlayerController->GetResourceManager())
			{
				playerResources = PlayerController->GetResourceManager()->PlayerResources;
			}
			// overloaded function building cost < current player resources
			if (PlayerController->LeftMouseClicked && playerResources >= stats)
			{
				// from tutorial
				// Get the AABB in Local space (aka Object space: such as in the Blueprint viewer). You might want to cache this result as this may be costly. 
				//const FBox Box = this->GetComponentsBoundingBox(true,true);
				const FBox Box = this->CalculateComponentsBoundingBoxInLocalSpace(true, true);
				const auto Transform = this->GetTransform();
				// Get World space Location.
				const FVector Center = Transform.TransformPosition(Box.GetCenter());

				// And World space extent
				const FVector Extent = Box.GetExtent();
				const FVector Forward = Transform.TransformVector(FVector::ForwardVector * Extent.X);
				const FVector Right = Transform.TransformVector(FVector::RightVector * Extent.Y);
				const FVector Up = Transform.TransformVector(FVector::UpVector * Extent.Z);

				// Now you have an oriented bounding box represented by a `Center` and three extent vectors.

				const FVector ExtentsX = Right;
				const FVector ExtentsY = Up;
				const FVector ExtentsZ = Forward;

				/*Corner2 = Center + ExtentsX + ExtentsY - ExtentsZ;
				Corner3 = Center + ExtentsX - ExtentsY - ExtentsZ;
				Corner6 = Center - ExtentsX - ExtentsY - ExtentsZ;
				Corner7 = Center - ExtentsX + ExtentsY - ExtentsZ;*/

				Corner1 = Center + ExtentsX + ExtentsY + ExtentsZ;
				Corner2 = Center + ExtentsX - ExtentsY + ExtentsZ;
				Corner3 = Center - ExtentsX - ExtentsY + ExtentsZ;
				Corner4 = Center - ExtentsX + ExtentsY + ExtentsZ;
				Corner5 = Center + ExtentsX + ExtentsY - ExtentsZ;
				Corner6 = Center + ExtentsX - ExtentsY - ExtentsZ;
				Corner7 = Center - ExtentsX - ExtentsY - ExtentsZ;
				Corner8 = Center - ExtentsX + ExtentsY - ExtentsZ;
				UE_LOG(LogTemp, Warning, TEXT("1X: %f, Y: %f, Z: %f"), Corner1.X, Corner1.Y, Corner1.Z);
				UE_LOG(LogTemp, Warning, TEXT("2X: %f, Y: %f, Z: %f"), Corner2.X, Corner2.Y, Corner2.Z);
				UE_LOG(LogTemp, Warning, TEXT("3X: %f, Y: %f, Z: %f"), Corner3.X, Corner3.Y, Corner3.Z);
				UE_LOG(LogTemp, Warning, TEXT("4: %f, Y: %f, Z: %f"), Corner4.X, Corner4.Y, Corner4.Z);
				UE_LOG(LogTemp, Warning, TEXT("5X: %f, Y: %f, Z: %f"), Corner5.X, Corner5.Y, Corner5.Z);
				UE_LOG(LogTemp, Warning, TEXT("6X: %f, Y: %f, Z: %f"), Corner6.X, Corner6.Y, Corner6.Z);
				UE_LOG(LogTemp, Warning, TEXT("7X: %f, Y: %f, Z: %f"), Corner7.X, Corner7.Y, Corner7.Z);
				UE_LOG(LogTemp, Warning, TEXT("8X: %f, Y: %f, Z: %f"), Corner8.X, Corner8.Y, Corner8.Z);
				DrawDebugLine(GetWorld(), Corner2, Corner3, FColor::Red, false, 1.0f);
				DrawDebugLine(GetWorld(), Corner3, Corner7, FColor::Red, false, 1.0f);
				DrawDebugLine(GetWorld(), Corner7, Corner6, FColor::Red, false, 1.0f);
				DrawDebugLine(GetWorld(), Corner6, Corner2, FColor::Red, false, 1.0f);
				/*LogTemp: Warning: 2X : 250.000000, Y : 250.000000, Z : -50.000000
				LogTemp : Warning : 3X : 250.000000, Y : -250.000000, Z : -50.000000
				LogTemp : Warning : 6X : -250.000000, Y : 250.000000, Z : -50.000000
				LogTemp : Warning : 7X : -250.000000, Y : -250.000000, Z : -50.000000*/

				FVector2D Coner1Grid = FVector2D(GridManager->AlignToGrid(Corner1.X, GridManager->TileSize),
					GridManager->AlignToGrid(Corner1.Y, GridManager->TileSize));
				FVector2D Coner2Grid = FVector2D(GridManager->AlignToGrid(Corner2.X, GridManager->TileSize),
					GridManager->AlignToGrid(Corner2.Y, GridManager->TileSize));
				FVector2D Coner3Grid = FVector2D(GridManager->AlignToGrid(Corner3.X, GridManager->TileSize),
					GridManager->AlignToGrid(Corner3.Y, GridManager->TileSize));
				FVector2D Coner4Grid = FVector2D(GridManager->AlignToGrid(Corner4.X, GridManager->TileSize),
					GridManager->AlignToGrid(Corner4.Y, GridManager->TileSize));
				FVector2D Coner5Grid = FVector2D(GridManager->AlignToGrid(Corner5.X, GridManager->TileSize),
					GridManager->AlignToGrid(Corner5.Y, GridManager->TileSize));
				FVector2D Coner6Grid = FVector2D(GridManager->AlignToGrid(Corner6.X, GridManager->TileSize),
					GridManager->AlignToGrid(Corner6.Y, GridManager->TileSize));
				FVector2D Coner7Grid = FVector2D(GridManager->AlignToGrid(Corner7.X, GridManager->TileSize),
					GridManager->AlignToGrid(Corner7.Y, GridManager->TileSize));
				FVector2D Coner8Grid = FVector2D(GridManager->AlignToGrid(Corner8.X, GridManager->TileSize),
					GridManager->AlignToGrid(Corner8.Y, GridManager->TileSize));
				UE_LOG(LogTemp, Warning, TEXT("%f, %f"),Coner1Grid.X, Coner1Grid.Y);
				FVector2D GridCorner1 = GridManager->WorldToGridIndex(FVector2D(Coner1Grid.X, Coner1Grid.Y));
				FVector2D GridCorner2 = GridManager->WorldToGridIndex(FVector2D(Coner2Grid.X, Coner2Grid.Y));
				FVector2D GridCorner3 = GridManager->WorldToGridIndex(FVector2D(Coner3Grid.X, Coner3Grid.Y));
				FVector2D GridCorner4 = GridManager->WorldToGridIndex(FVector2D(Coner4Grid.X, Coner4Grid.Y));
				FVector2D GridCorner5 = GridManager->WorldToGridIndex(FVector2D(Coner5Grid.X, Coner5Grid.Y));
				FVector2D GridCorner6 = GridManager->WorldToGridIndex(FVector2D(Coner6Grid.X, Coner6Grid.Y));
				FVector2D GridCorner7 = GridManager->WorldToGridIndex(FVector2D(Coner7Grid.X, Coner7Grid.Y));
				FVector2D GridCorner8 = GridManager->WorldToGridIndex(FVector2D(Coner8Grid.X, Coner8Grid.Y));
				/*LogTemp: Warning: 2X : 250.000000, Y : 250.000000, Z : -50.000000
				LogTemp : Warning : 3X : 250.000000, Y : -250.000000, Z : -50.000000
				LogTemp : Warning : 6X : -250.000000, Y : 250.000000, Z : -50.000000
				LogTemp : Warning : 7X : -250.000000, Y : -250.000000, Z : -50.000000*/
				if (!GridManager->CheckGridIndex(GridCorner2) || !GridManager->CheckGridIndex(GridCorner7) || !GridManager->CheckGridIndex(GridCorner3) || !GridManager->CheckGridIndex(GridCorner6))
				{
					//UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GetActorLocation().X, GetActorLocation().Y);
					UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner2.X, GridCorner2.Y);
					UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner3.X, GridCorner3.Y);
					UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner6.X, GridCorner6.Y);
					UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner7.X, GridCorner7.Y);


					UE_LOG(LogTemp, Warning, TEXT("Corner out of bounds"));
					return;
				}
				/*if ((GridCorner6.X + GridCorner2.X) == 0 && (GridCorner7.Y + GridCorner2.Y) == 0 )
				{
					if (GridManager->IsOccupied(FVector2D((int)(GridCorner6.X / GridManager->TileSize), (int)(GridCorner6.Y / GridManager->TileSize))))
					{
						UE_LOG(LogTemp, Warning, TEXT("Grid is occupied"));
						return;
					}
				}*/
				UE_LOG(LogTemp, Warning, TEXT("ActorLocation X: %f, Y: %f"), GetActorLocation().X, GetActorLocation().Y);
				UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner2.X, GridCorner2.Y);
				UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner3.X, GridCorner3.Y);
				UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner6.X, GridCorner6.Y);
				UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner7.X, GridCorner7.Y);
				double MaxX = FMath::Max(GridCorner6.X, GridCorner2.X);
				double MinX = FMath::Min(GridCorner6.X, GridCorner2.X);
				double MaxY = FMath::Max(GridCorner7.Y, GridCorner2.Y);
				double MinY = FMath::Min(GridCorner7.Y, GridCorner2.Y);
				UE_LOG(LogTemp, Warning, TEXT("MinX: %f, MinY: %f"), MinX, MinY);
				UE_LOG(LogTemp, Warning, TEXT("MaxX: %f, MaxY: %f"), MaxX, MaxY);
				
				for (int i = MinX; i < MaxX; i++)
				{
					for (int j = MinY; j < MaxY; j++)
					{
						if (GridManager->IsOccupied(FVector2D(i, j)))
						{
							UE_LOG(LogTemp, Warning, TEXT("Grid is occupied"));
							return;
						}
					}
				}
				
				for (int i = MinX; i < MaxX; i++)
				{
					for (int j = MinY; j < MaxY; j++)
					{
						GridManager->GridVector[i][j]->IsOccupied = true;
					}
				}
				UE_LOG(LogTemp, Warning, TEXT("1X: %f, Y: %f"), GridCorner1.X, GridCorner1.Y);
				UE_LOG(LogTemp, Warning, TEXT("2X: %f, Y: %f"), GridCorner2.X, GridCorner2.Y);
				UE_LOG(LogTemp, Warning, TEXT("3X: %f, Y: %f"), GridCorner3.X, GridCorner3.Y);
				UE_LOG(LogTemp, Warning, TEXT("4X: %f, Y: %f"), GridCorner4.X, GridCorner4.Y);
				UE_LOG(LogTemp, Warning, TEXT("5X: %f, Y: %f"), GridCorner5.X, GridCorner5.Y);
				UE_LOG(LogTemp, Warning, TEXT("6X: %f, Y: %f"), GridCorner6.X, GridCorner6.Y);
				UE_LOG(LogTemp, Warning, TEXT("7X: %f, Y: %f"), GridCorner7.X, GridCorner7.Y);
				UE_LOG(LogTemp, Warning, TEXT("8X: %f, Y: %f"), GridCorner8.X, GridCorner8.Y);
				playerResources = playerResources - stats;
				IsPlaced = true;

			}
			
		}
	}
}
