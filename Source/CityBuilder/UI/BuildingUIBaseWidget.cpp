// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingUIBaseWidget.h"
#include "Components/Button.h"

bool UBuildingUIBaseWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (BuildingButton == nullptr) return false;
	BuildingButton->OnClicked.AddDynamic(this, &UBuildingUIBaseWidget::SpawnBuilding);

	return true;
}

void UBuildingUIBaseWidget::SpawnBuilding()
{
	ACityBuilderPlayerController* PlayerController = Cast<ACityBuilderPlayerController>(GetOwningPlayer());
	if (PlayerController)
	{

		PlayerController->SpawnBuilding(BuildingToSpawn);
	}
}
