// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    //박스 충돌체 컴포넌트
    UPROPERTY(EditAnywhere)
    class UBoxComponent* boxComp;
    
    //스태틱 메시 컴포넌트
    UPROPERTY(EditAnywhere)
    class UStaticMeshComponent* meshComp;
    
    //속력 변수
    UPROPERTY(EditAnywhere)
    float moveSpeed = 500;
    
    //총구 위치
    UPROPERTY(EditAnywhere)
    class UArrowComponent* firePosition;
    
    //총알 블루프린트
    UPROPERTY(EditAnywhere)
    TSubclassOf<class ABullet> bulletFactory;
    //TSubclassOf<T> 월드에 배치하지 않은 원본 파일을 변수에 할당하려고 사용하는 특수한 자료형
    //템플릿<T>안에 할당하려는 블루프린트 파일이 상속한 택터 클래스를 넣어주면 됩니다.
    //BP_Bullet 블루프린트는 ABullet 클래스를 상속하고 있으므로 class ABullet으로 자료형을 선언하면 된다.
    
    //총알 발사 효과음 파일
    UPROPERTY(EditAnywhere)
    class USoundBase* fireSound;
    
private:
    //삿용자의 키 입력 값을 받을 변수
    float h;
    float v;
    
    //사용자 입력 처리 함수
    void MoveHorizontal(float value);
    void MoveVertical(float value);
    
    void Fire();

};
