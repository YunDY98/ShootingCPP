// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    //박스 콜라이더 컴포넌트를 생성한다
    boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
    //CreateDefaultSubbobject는 액터에게 컴포넌트를 추가할때 쓰는 함수 <클래스 이름>템플릿 (TEXT(컴포넌트 별명))
    
    //생성한 박스 콜라이더 컴포넌트를 최상단 컴포넌트로 설정한다
    SetRootComponent(boxComp);
    
    //스태틱 메시 컴포넌트를 생성한다.
    meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
    
    //박스 콜라이더 컴포넌트의 자식 컴포넌트로 설정한다.
    meshComp->SetupAttachment(boxComp);
    
    //박스 콜라이더의 크기를 50x50x50으로 설정
    FVector boxSize = FVector(50.0f,50.0f,50.0f);
    boxComp->SetBoxExtent(boxSize);
    
    //총구 표시 컴포넌트를 생성하고 박스 컴포넌트의 자식 컴포넌트로 설정한다.
    firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
    firePosition->SetupAttachment(boxComp);
    
    
    //오버랩 이벤트를 켠다
    boxComp -> SetGenerateOverlapEvents(true);
    
    //충돌 응답을 Query And Physics로 설정한다
    boxComp -> SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    
    //Object Type을 1번 채널(Player)로 설정한다
    boxComp -> SetCollisionObjectType(ECC_GameTraceChannel1);
    
    //모든 채널을 충돌 응답 없음으로 설정한다
    boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    
    //적과 충돌 이벤트 체크(Quary)를 한다
    boxComp -> SetCollisionResponseToChannel(ECC_GameTraceChannel2,ECR_Overlap);
    boxComp -> SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    //사용자의 입력 키를 이용해서
    //1. 상하 입력 값과 좌우 입력 값을 이용해서 방향 벡터를 만든다.
    FVector dir = FVector(0,h,v);
    
    //2. 방향 벡터의 길이가 1이 되도록 벡터를 정규화한다.
    dir.Normalize();
    
    //3. 이동할 위치 좌표를 구한다(p = p0 + vt)
    FVector newLocation = GetActorLocation() + dir* moveSpeed * DeltaTime;
    
    //4. 현재 액터의 위치 좌표를 앞에서 구한 새 좌표로 갱신한다.
    SetActorLocation(newLocation,true);
}

// Called to bind functionality to input
//기능을 입력에 연결하기 위해 호출됨
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    //Axis 바인딩 된 값을 함수에 연결한다.
    PlayerInputComponent->BindAxis("Horizontal",this,&APlayerPawn::MoveHorizontal);
    PlayerInputComponent->BindAxis("Vertical",this,&APlayerPawn::MoveVertical);
    //BindAxis("연결할 Axis이름",연결할 함수가 있는 클래스,연결할 함수의 주소 값);
    
    //Action 바인딩 된 값을 함수에 연결한다.
    PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APlayerPawn::Fire);
    //BindAction(Action 이름,입력 이벤트 타입, 연결할 함수가 있는 클래스, 연결할 함수의 주소값);
    //IE_Pressed 키를눌렀을때 반대 IE_Relessed

}

//좌우 입력 처리 함수
void APlayerPawn::MoveHorizontal(float value){
    //사용자 입력 값(Axis)을 h변수에 넣는다
    h = value;
}
//상하 입력 처리 함수
void APlayerPawn::MoveVertical(float value){
    //사용자 입력 값(Axis)을 v변수에 넣는다.
    v = value;
}

//왼쪽 마우스 입력 처리 함수 
void APlayerPawn::Fire(){
    //총알 블루프린트 파일을 firePosition 위치에 생성한다
    ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());
    //SpawnActor<생성하려는 액터 클래스> (파일을 나타내는 변수, 생성할 위치, 생성할 회전 값);
    
    
    //fireSound 변수에 할당된 음원 파일을 실행한다
    UGameplayStatics::PlaySound2D(GetWorld(),fireSound);
}
