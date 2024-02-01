// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CityBuilder/StructsandEnums.h"
#include "ResourceManager.generated.h"



UCLASS()
class CITYBUILDER_API AResourceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceManager();
	UPROPERTY(EditAnywhere)
	FPlayerResources PlayerResources;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FPlayerResources GetPlayerResources()
	{
		return PlayerResources;
	}

	void SetComponentValue(int value)
	{
		PlayerResources.Components = value;
	}
	void SetMetalValue(int value)
	{
		PlayerResources.Metal = value;
	}
	void AddComponentsValue(int value)
	{
		PlayerResources.Components += value;
	}
	void AddMetalValue(int value)
	{
		PlayerResources.Metal += value;
	}
	void RemoveComponentsValue(int value)
	{
		PlayerResources.Components -= value;
	}
	void RemoveMetalValue(int value)
	{
		PlayerResources.Metal -= value;
	}
};
