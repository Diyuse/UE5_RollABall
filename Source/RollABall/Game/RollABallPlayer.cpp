// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallPlayer.h"

// Sets default values
ARollABallPlayer::ARollABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARollABallPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARollABallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARollABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

