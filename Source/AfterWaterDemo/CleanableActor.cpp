// Fill out your copyright notice in the Description page of Project Settings.


#include "CleanableActor.h"
#include "Components/StaticMeshComponent.h"
//#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/GameplayStatics.h" // 用于查找当前场景中的所有可清洁物体

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

	// DynamicMaterial = CleanableMesh->CreateDynamicMaterialInstance(0);
	// if(!DynamicMaterial)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Failed to create dynamic material : %s"), *GetName());
	// }
	
}

// Called every frame
void ACleanableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACleanableActor::ReceiveWater()
{

	//CleanableMesh->SetMaterial(0, CleanMaterial);
	CleanableMesh->SetVisibility(false);

	bIsClean = true;
	UE_LOG(LogTemp, Warning, TEXT("Cleaned: %s"), *GetName());
	CheckWinCondition();
}

void ACleanableActor::CheckWinCondition()
{
	TArray<AActor*>CleanableActors;//创建数组，存放所有的可清洁体
	UGameplayStatics::GetAllActorsOfClass(this, ACleanableActor::StaticClass(), CleanableActors);

	int32 CleanedCount = 0;

	for(AActor* Actor : CleanableActors)
	{
		ACleanableActor* CleanableActor = Cast<ACleanableActor>(Actor);

		if(CleanableActor && CleanableActor->bIsClean)
		{
			CleanedCount++;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Cleaning progress: %d / %d"), CleanedCount, CleanableActors.Num());
	
	if(CleanableActors.Num() > 0 && CleanedCount == CleanableActors.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("You win!"));

		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("YOU WIN!"));
		ShowWinScreen();
	}


}




