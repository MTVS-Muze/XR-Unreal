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
    /*// ���� ������ ����
    ULevelSequence* MySequence = NewObject<ULevelSequence>();

    // ���� ���� Ʈ�� ����
    UMovieSceneSpawnTrack* SpawnTrack = MySequence->MovieScene->AddTrack<UMovieSceneSpawnTrack>(FGuid::NewGuid());

    // ���� ���� ���� ����
    UMovieSceneSpawnSection* SpawnSection = Cast<UMovieSceneSpawnSection>(SpawnTrack->CreateNewSection());

    // Ʈ���� ���� �߰�
    SpawnTrack->AddSection(*SpawnSection);

    // Ÿ�Ӷ��� ����
    SpawnSection->SetRange(TRange<FFrameNumber>(0, 1000));

    // ���� ���� ���ǿ� ���� ����
    SpawnSection->SetObjectBindingID(FMovieSceneObjectBindingID(MyActor->GetUniqueID(), MovieSceneSequenceID::Root));

    // ������ �÷��̾� ����
    FMovieSceneSequencePlaybackSettings Settings;
    ULevelSequencePlayer* Player = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MySequence, Settings);

    // ������ ���
    Player->Play();

    */
}

void AOSY_MovieSceneSequenceActor::PlaySequence()
{

}

