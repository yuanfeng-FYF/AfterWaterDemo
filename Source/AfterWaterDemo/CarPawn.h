// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CarPawn.generated.h"

UCLASS()
class AFTERWATERDEMO_API ACarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACarPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateCannon(FVector LookAtTarget);
	
private:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Compoent", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "component")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCameraComponent* Camera;

	void Move(float Value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	void Turn(float Value);
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 200.f;

	class APlayerController* PlayerControllerRef;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
