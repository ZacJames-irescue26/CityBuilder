// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructsandEnums.generated.h"
USTRUCT(BlueprintType)
struct FResourceStats
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int CostComponents = 0;
	UPROPERTY(EditAnywhere)
	int CostMetal = 0;
	
	UPROPERTY(EditAnywhere)
	int ProductionComponents = 0;
	UPROPERTY(EditAnywhere)
	int ProductionMetal = 0;
	
};

USTRUCT(BlueprintType)
struct FPlayerResources
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int Components = 0;
	UPROPERTY(EditAnywhere)
	int Metal = 0;
	bool operator >= (FResourceStats res)
	{
		if (Components >= res.CostComponents && Metal >= res.CostMetal)
		{
			return true;
		}
		return false;
	}
	FPlayerResources operator -(FResourceStats res)
	{
		return {Components - res.CostComponents && Metal - res.CostMetal};
	}
};
UCLASS()
class CITYBUILDER_API UStructsandEnums : public UObject
{
	GENERATED_BODY()
public:
	UStructsandEnums();
	~UStructsandEnums();
};
