// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidget.h"
#include "Components/SizeBox.h"
#include "BuildingUIBaseWidget.h"

UUIWidget::UUIWidget(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BuildingBPClass(TEXT("/Game/TopDown/Blueprints/UI/BP_BuildingBaseWidget"));
	if (!ensure(BuildingBPClass.Class != nullptr)) return;

	BuildingUIClass = BuildingBPClass.Class;
}

bool UUIWidget::Initialize()
{
	bool success = Super::Initialize();
	BuildingUI = CreateWidget<UBuildingUIBaseWidget>(this, BuildingUIClass);
	if (Ground && BuildingUI)
	{
		Ground->AddChild(BuildingUI);
	}
	return true;
}
