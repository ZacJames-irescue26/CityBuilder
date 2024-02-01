// Fill out your copyright notice in the Description page of Project Settings.


#include "CityBuilderHUD.h"
#include "UObject/ConstructorHelpers.h"

ACityBuilderHUD::ACityBuilderHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UserInterfaceBPClass(TEXT("/Game/TopDown/Blueprints/UI/BP_UIWidget"));
	if (!ensure(UserInterfaceBPClass.Class != nullptr)) return;

	UserInterfaceClass = UserInterfaceBPClass.Class;

}

void ACityBuilderHUD::DrawHUD()
{

}

void ACityBuilderHUD::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(UserInterfaceClass != nullptr)) return;
	UserInterface = CreateWidget<UUIWidget>(GetWorld(), UserInterfaceClass);
	if (!ensure(UserInterface != nullptr)) return;
	UserInterface->AddToViewport();
}
