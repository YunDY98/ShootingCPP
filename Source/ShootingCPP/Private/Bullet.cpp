// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    //박스 콜라이더 컴포넌트를 생성한다
    boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
   
    boxComp->SetBoxExtent(FVector(50.0f,50.0f,50.0f));
    //생성한 박스 콜라이더 컴포넌트를 최상단 컴포넌트로 설정한다
    SetRootComponent(boxComp);
    
   
    
    //박스 컴포넌트의 크기를 변경한다.
    boxComp->SetWorldScale3D(FVector(0.75f,0.25f,1.0f));
    
    //스태틱 메시 컴포넌트를 생성한다.
    meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
    
    //박스 콜라이더 컴포넌트의 자식 컴포넌트로 설정한다.
    meshComp->SetupAttachment(boxComp);
    
  

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    //전방으로 이동될 위치를 계산한다
    FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
    
    // 계산된 위치 좌표를 액터의 새 좌표로 넣는다.
    SetActorLocation(newLocation);
    
    
}

