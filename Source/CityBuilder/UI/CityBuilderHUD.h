// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CityBuilder/UI/UIWidget.h"
#include "CityBuilderHUD.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API ACityBuilderHUD : public AHUD
{
	GENERATED_BODY()
public:
	ACityBuilderHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> UserInterfaceClass;
	class UUIWidget* UserInterface;
};
