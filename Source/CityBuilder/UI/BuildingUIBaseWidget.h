// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CityBuilder/Buildings/BuildingBase.h"
#include "BuildingUIBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API UBuildingUIBaseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	UFUNCTION()
	virtual void SpawnBuilding();
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* BuildingButton;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuildingBase> BuildingToSpawn;

};
