// Copyright Epic Games, Inc. All Rights Reserved.

#include "CityBuilderPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "CityBuilderCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "CityBuilder/Buildings/BuildingBase.h"
#define TerrainOverlap ECollisionChannel::ECC_GameTraceChannel1

ACityBuilderPlayerController::ACityBuilderPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
}

void ACityBuilderPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	TArray<AActor*> ActorGridManager;
	ResourceManager = GetWorld()->SpawnActor<AResourceManager>(FVector::ZeroVector, FRotator::ZeroRotator);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridManager::StaticClass(), ActorGridManager);
	if (ActorGridManager.Num() > 0)
	{
		GridManager = Cast<AGridManager>(ActorGridManager[0]);
	}
}
void ACityBuilderPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	bool Hit = GetHitResultUnderCursor(TerrainOverlap, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		WorldMousePos = HitResult.ImpactPoint;
	}
	FVector2D ViewportSize;

	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	GetMousePosition(LocationX, LocationY);
	//dont know why its reversed
	if ((LocationX / ViewportSize.X) >= 0.975)
	{
		_Location.Y += 10;
	}
	if ((LocationX / ViewportSize.X) <= 0.025)
	{
		_Location.Y -= 10;
	}
	if ((LocationY / ViewportSize.Y) >= 0.975)
	{
		_Location.X -= 10;
	}
	if ((LocationY / ViewportSize.Y) <= 0.025)
	{
		_Location.X += 10;
	}
	if (Character)
	{
		Character->SetActorLocation(_Location);
	}
	else
	{
		Character = Cast<ACityBuilderCharacter>(GetPawn());
	}

}
void ACityBuilderPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ACityBuilderPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ACityBuilderPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ACityBuilderPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ACityBuilderPlayerController::OnSetDestinationReleased);

		
	}
}

void ACityBuilderPlayerController::OnInputStarted()
{
	LeftMouseClicked = true;

}

// Triggered every frame when the input is held down
void ACityBuilderPlayerController::OnSetDestinationTriggered()
{
	
}

void ACityBuilderPlayerController::OnSetDestinationReleased()
{
	LeftMouseClicked = false;
}

void ACityBuilderPlayerController::SpawnBuilding(TSubclassOf<ABuildingBase> Building)
{
	ABuildingBase* SpawnedBuilding = GetWorld()->SpawnActor<ABuildingBase>(Building, WorldMousePos, FRotator::ZeroRotator);
}



