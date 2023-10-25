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
	/// <param name="n">나이아가라이름</param>
	/// <param name="s">생성시간</param>
	/// <param name="d">죽는시간</param>
	/// <param name="lx">X좌표</param>
	/// <param name="ly">Y좌표</param>
	/// <param name="lz">Z좌표</param>
	/// <param name="sc">스케일</param>
	/// <param name="t">적용텍스쳐인덱스</param>
	FORCEINLINE void Set(FString n, float s, float d, float lx, float ly, float lz, float sc , int t)
	{ name = n; spawnTime = s, dieTime = d , locationX = lx, locationY = ly, locationZ = lz, scale = sc, texture = t;};
};
