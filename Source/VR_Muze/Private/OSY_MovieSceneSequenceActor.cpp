// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_MovieSceneSequenceActor.h"
/*#include "MovieScene.h"
#include "Runtime/MovieScene/Public/Tracks/MovieSceneSpawnTrack.h"
#include "Runtime/MovieScene/Public/Sections/MovieSceneSpawnSection.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
*/

// Sets default values
AOSY_MovieSceneSequenceActor::AOSY_MovieSceneSequenceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSY_MovieSceneSequenceActor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AOSY_MovieSceneSequenceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOSY_MovieSceneSequenceActor::CreateSequence()
{
    /*// 레벨 시퀀스 생성
    ULevelSequence* MySequence = NewObject<ULevelSequence>();

    // 액터 스폰 트랙 생성
    UMovieSceneSpawnTrack* SpawnTrack = MySequence->MovieScene->AddTrack<UMovieSceneSpawnTrack>(FGuid::NewGuid());

    // 액터 스폰 섹션 생성
    UMovieSceneSpawnSection* SpawnSection = Cast<UMovieSceneSpawnSection>(SpawnTrack->CreateNewSection());

    // 트랙에 섹션 추가
    SpawnTrack->AddSection(*SpawnSection);

    // 타임라인 설정
    SpawnSection->SetRange(TRange<FFrameNumber>(0, 1000));

    // 액터 스폰 섹션에 액터 설정
    SpawnSection->SetObjectBindingID(FMovieSceneObjectBindingID(MyActor->GetUniqueID(), MovieSceneSequenceID::Root));

    // 시퀀스 플레이어 생성
    FMovieSceneSequencePlaybackSettings Settings;
    ULevelSequencePlayer* Player = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MySequence, Settings);

    // 시퀀스 재생
    Player->Play();

    */
}

void AOSY_MovieSceneSequenceActor::PlaySequence()
{

}

