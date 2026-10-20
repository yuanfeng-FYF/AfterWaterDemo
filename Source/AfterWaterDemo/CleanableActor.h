// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CleanableActor.generated.h"

UCLASS()
class AFTERWATERDEMO_API ACleanableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACleanableActor();

	void ReceiveWater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Victory")
	void ShowWinScreen();

private:
	UPROPERTY(VisibleAnywhere, Category = "Cleaning")
	class UStaticMeshComponent* CleanableMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Cleaning")
	//class UMaterialInstanceDynamic* DynamicMaterial = nullptr;
	class UMaterialInterface* CleanMaterial = nullptr;//添加一个CleanMaterial

	bool bIsClean = false;

	void CheckWinCondition();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
