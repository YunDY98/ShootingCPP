// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingTestActor.h"

// Sets default values
ACodingTestActor::ACodingTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingTestActor::BeginPlay()
{
	Super::BeginPlay();
	
    //Hello World print
    //UE_LOG(LogTemp,Warning,TEXT("Hello Wolrd!"));
    UE_LOG(LogTemp,Warning,TEXT("%d"),number1);
    UE_LOG(LogTemp,Warning,TEXT("%.2f"),number2);
    UE_LOG(LogTemp,Warning,TEXT("%s"),*name);
}

// Called every frame
void ACodingTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

