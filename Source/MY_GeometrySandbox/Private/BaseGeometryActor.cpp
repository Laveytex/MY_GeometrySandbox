// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include  "Engine/Engine.h"
DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All,All);


// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	
	
	
	//printType();
	//printStringTipes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGeometryActor::printType()
{
	int WeaponNum = 4;
	int KillsNum = 7;
	float Health = 34.2312;
	bool IsDead = false;
	bool HasWeapon = true;

	UE_LOG(LogBaseGeometry, Display,TEXT("Wapons num: %d, kills num: %i"), WeaponNum, KillsNum);
	UE_LOG(LogBaseGeometry, Display,TEXT("Heals: %f"), Health);
	UE_LOG(LogBaseGeometry, Display,TEXT("Heals: %.2f"), Health);
	UE_LOG(LogBaseGeometry, Display,TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogBaseGeometry, Display,TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::printStringTipes()
{
	FString Name = "John Connor";
	
	UE_LOG(LogBaseGeometry,Display,TEXT("Name: %s"),*Name);

	int WeaponNum = 4;
	float Health = 34.2312;
	bool IsDead = false;

	FString WeaponsNumStr = "Wapons num = " + FString::FromInt(WeaponNum);
	FString HealthStr = "Heals num = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "IsDead num = " + FString(IsDead ? "true" : "false");

	FString Stats = FString::Printf(TEXT(" \n == All Stats == \n %s \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"),*Stats);

	GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green, Stats, true, FVector2D(1.5f,1.5f));
}

