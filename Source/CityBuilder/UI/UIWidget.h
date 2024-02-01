// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API UUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UUIWidget(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* BuildingSizeBox;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* Ground;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* Air;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* Sea;
	UPROPERTY(EditAnywhere, meta = (BindWidgetOptional))
	class UWidgetSwitcher* BuildingSwitcher;
	
	virtual bool Initialize() override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBuildingUIBaseWidget> BuildingUIClass;
	UBuildingUIBaseWidget* BuildingUI;


};
