// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CityBuilder/Grid/GridManager.h"
#include "CityBuilderCharacter.h"
#include "CityBuilder/Managers/ResourceManager.h"
#include "CityBuilderPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class ACityBuilderPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACityBuilderPlayerController();
	void SpawnBuilding(TSubclassOf<class ABuildingBase> Building);
	FVector GetWorldMousePos()
	{
		return WorldMousePos;
	}
	AResourceManager* GetResourceManager()
	{
		return ResourceManager;
	}
	bool LeftMouseClicked = false;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

protected:

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void PlayerTick(float DeltaTime) override;
	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

private:
	FHitResult HitResult;
	AGridManager* GridManager;
	FVector WorldMousePos;
	ACityBuilderCharacter* Character;
	double LocationX;
	double LocationY;
	FVector _Location;
	AResourceManager* ResourceManager;
};


