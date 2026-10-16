// Fill out your copyright notice in the Description page of Project Settings.


#include "CleanableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ACleanableActor::ACleanableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CleanableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cleanable Mesh"));
	RootComponent = CleanableMesh;

}

// Called when the game starts or when spawned
void ACleanableActor::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterial = CleanableMesh->CreateDynamicMaterialInstance(0);
	if(!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create dynamic material : %s"), *GetName());
	}
	
}

// Called every frame
void ACleanableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACleanableActor::ReceiveWater()
{
	UE_LOG(LogTemp, Warning, TEXT("Receive water : %s"), *GetName());

	if(!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicMaterial is null : %s"),*GetName());
		return;
	}
	DynamicMaterial->SetVectorParameterValue(TEXT("SurfaceColor"), FLinearColor(0.165147f, 0.187506f, 0.206597f, 0.0f));
}


