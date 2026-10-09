// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPawn.h"
#include"Components/CapsuleComponent.h"
#include"Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

// Sets default values
ACarPawn::ACarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(CapsuleComp);

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	CannonMesh->SetupAttachment(BodyMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

// Called every frame
void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
		
		RotateCannon(HitResult.ImpactPoint);
	}
}

void ACarPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACarPawn::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACarPawn::Turn);

	PlayerInputComponent->BindAction(TEXT("Water"), IE_Pressed, this, &ACarPawn::Water);
}

void ACarPawn::Move(float Value)
{
	UE_LOG(LogTemp, Display, TEXT("Value: %f"), Value);

	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ACarPawn::Turn(float Value)
{
	UE_LOG(LogTemp, Display, TEXT("Value: %f"), Value);

	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}

void ACarPawn::RotateCannon(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - CannonMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	//CannonMesh->SetWorldRotation(LookAtRotation)；

	CannonMesh->SetWorldRotation(FMath::RInterpTo(CannonMesh->GetComponentRotation(), LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 5.f));
}

void ACarPawn::Water()
{
	UE_LOG(LogTemp, Warning, TEXT("Water Called"));
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	DrawDebugSphere(GetWorld(), ProjectileSpawnPointLocation, 20.f, 12, FColor::Green, false, 2.f);

	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();  
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
}
