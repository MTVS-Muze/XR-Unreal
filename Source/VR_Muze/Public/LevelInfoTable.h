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
	FString job;
	UPROPERTY(EditAnywhere)
	int32 hp;
	UPROPERTY(EditAnywhere)
	int32 mp;

	/// <summary>
	/// ����ü ������ Set �Լ�
	/// </summary>
	/// <param name="n">�̸�</param>
	/// <param name="j">����</param>
	/// <param name="h">ü��</param>
	/// <param name="m">����</param>
	FORCEINLINE void Set(FString n, FString j, int32 h, int32 m){ name = n; job = j ; hp =h; mp=m;};
};