// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelInfoTable.generated.h"



USTRUCT(BlueprintType)
struct VR_MUZE_API FLevelInfoTable : public FTableRowBase
{
	GENERATED_BODY()

	
public :
	UPROPERTY(EditAnywhere)
	FString name;
	
	UPROPERTY(EditAnywhere)
	float spawnTime;
	UPROPERTY(EditAnywhere)
	float dieTime;
	UPROPERTY(EditAnywhere)
	float locationX;
	UPROPERTY(EditAnywhere)
	float locationY;
	UPROPERTY(EditAnywhere)
	float locationZ;
	UPROPERTY(EditAnywhere)
	float scale;
	UPROPERTY(EditAnywhere)
	int texture ;



	/// <summary>
	/// 
	/// </summary>
	/// <param name="n">���̾ư����̸�</param>
	/// <param name="s">�����ð�</param>
	/// <param name="d">�״½ð�</param>
	/// <param name="lx">X��ǥ</param>
	/// <param name="ly">Y��ǥ</param>
	/// <param name="lz">Z��ǥ</param>
	/// <param name="sc">������</param>
	/// <param name="t">�����ؽ����ε���</param>
	FORCEINLINE void Set(FString n, float s, float d, float lx, float ly, float lz, float sc , int t)
	{ name = n; spawnTime = s, dieTime = d , locationX = lx, locationY = ly, locationZ = lz, scale = sc, texture = t;};
};
