// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"
#include "Components/BoxComponent.h"

// Sets default values
AKillZone::AKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    //박스 컴포넌트를 생성하고 루트로 설정
    boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
    SetRootComponent(boxComp);
    
    //박스 컴포넌트를 static으로
    boxComp -> SetMobility(EComponentMobility::Static);
    
    //박스의 크기를 설정
    boxComp -> SetBoxExtent(FVector(50,2000,50));
    
    //박스 컴포넌트의 콜리전 프리셋을 KillZone으로 설정한다
    boxComp -> SetCollisionProfileName(TEXT("KillZone"));
    
    //스태틱 메시 컴포넌트를 생성한다.
    meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
    
    //박스 콜라이더 컴포넌트의 자식 컴포넌트로 설정한다.
    meshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

