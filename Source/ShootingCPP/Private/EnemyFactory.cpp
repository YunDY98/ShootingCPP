// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "EnemyActor.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    //경과된 시간이 생성할 시간을 초과했다면
    if (currentTime >  delayTime)
    {
        currentTime = 0;
        
        //enemy 변수에 할당된 블루프린트를 자신의 위치에 생성한다.
        AEnemyActor* spawnActor = GetWorld() -> SpawnActor<AEnemyActor>(enemy, GetActorLocation(),GetActorRotation());
    }
    else
    {
        //현재 프레임의 경과 시간을 누적시킨다
        currentTime += DeltaTime;
    }
}

