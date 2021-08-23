// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARollABallPlayer::ARollABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);

	Mesh->OnComponentHit.AddDynamic(this, &ARollABallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ARollABallPlayer::BeginPlay()
{
	Super::BeginPlay();

	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called to bind functionality to input
void ARollABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ARollABallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollABallPlayer::MoveRight);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollABallPlayer::Jump);
}

void ARollABallPlayer::MoveRight(float Value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollABallPlayer::MoveForward(float Value)
{
	const FVector l_Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(l_Forward);
}

void ARollABallPlayer::Jump()
{
	if (JumpCount >= MaxJumpCount) { return; }

	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));
	JumpCount++;
}

void ARollABallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const float HitDirection = Hit.Normal.Z;
	if (HitDirection > 0) 
	{
		JumpCount = 0;
	}
}

