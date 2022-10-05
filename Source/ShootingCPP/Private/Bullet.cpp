// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"

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
    
    //박스 컴포넌트의 콜리전 프리셋을 Bullet으로 설정한다
    boxComp -> SetCollisionProfileName(TEXT("Bullet"));
    
  

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
    
    //박스 컴포넌트의 충돌 오버랩 이벤트에 BulletOverlap 함수를 연결한다
    boxComp -> OnComponentBeginOverlap.AddDynamic(this,&ABullet::OnBulletOverlap);
 
	
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

//충돌 이벤트가 발생할 때 실행할 함수
void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
    //충돌할 액터를 AEnemyActor클래스로 변환해본다.
    AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
    
    //만일, 캐스팅이 정상적으로 되어서 AEnemyActor 포인터 변수에 값이 있다면..
    if(enemy != nullptr)
    {
        //충돌한 액터를 제거한다.
        OtherActor -> Destroy();
        
        //폭발 이펙트를 생성한다
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),explosionFX,GetActorLocation(),
                                                 GetActorRotation());
    }
    
    //자기 자신을 제거한다
    Destroy();
}

