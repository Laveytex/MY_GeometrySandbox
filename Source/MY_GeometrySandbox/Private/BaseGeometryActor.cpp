// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include  "Engine/Engine.h"
#include "Math/TransformCalculus3D.h"
#include "TimerManager.h"
//#include "Materials/MaterialInstanceDynamic.h";

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All);


// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();

	
	
	//PrintTransform();
	//PrintType();
	//PrintStringTipes();
	SetColor(GeometryData.Color);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired,GeometryData.TimerRate, true);
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogBaseGeometry,Warning,TEXT("Actor Destriy"));
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
	
	
	
}

void ABaseGeometryActor::PrintType()
{	
	UE_LOG(LogBaseGeometry,Warning, TEXT("ActorName: %s"),*GetName());
	UE_LOG(LogBaseGeometry, Warning,TEXT("Wapons num: %d, kills num: %i"), WeaponNum, KillsNum);
	UE_LOG(LogBaseGeometry, Warning,TEXT("Heals: %f"), Health);
	UE_LOG(LogBaseGeometry, Warning,TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogBaseGeometry, Warning,TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry,Warning, TEXT("ActorName: %s"),*GetName());
	UE_LOG(LogBaseGeometry,Warning, TEXT("Transform: %s"),*Transform.ToString());
	UE_LOG(LogBaseGeometry,Warning, TEXT("Location: %s"),*Location.ToString());
	UE_LOG(LogBaseGeometry,Warning, TEXT("Rotation: %s"),*Rotation.ToString());
	UE_LOG(LogBaseGeometry,Warning, TEXT("Scale: %s"),*Scale.ToString());

	
	UE_LOG(LogBaseGeometry,Error, TEXT("Transfotm: %s"),*Transform.ToHumanReadableString());
}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
		{
			FVector CurrentLocation = GetActorLocation();
			if(GetWorld())
			{
				float Time = GetWorld()->GetTimeSeconds();
				CurrentLocation.Z=InitialLocation.Z + GeometryData.Amplitude* FMath::Sin(GeometryData.Frequence*Time);
				SetActorLocation(CurrentLocation);
			}
		} break;
	case EMovementType::Static:
		{
			
		} break;
	default:break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor&Color)
{
	if(!BaseMesh) return;
	
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if(DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if(++TimerCount<MaxTimerCunt)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Display,TEXT("Color to set up: %s"),*NewColor.ToString());
		SetColor(NewColor);
		OnColorChanged.Broadcast(NewColor,GetName());
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimeFinished.Broadcast(this);
	}
}

void ABaseGeometryActor::PrintStringTipes()
{
	FString Name = "John Connor";
	
	UE_LOG(LogBaseGeometry,Display,TEXT("Name: %s"),*Name);

	int WeaponNum1 = 4;
	float Health1 = 34.2312;
	bool IsDead1 = false;

	FString WeaponsNumStr = "Wapons num = " + FString::FromInt(WeaponNum1);
	FString HealthStr = "Heals num = " + FString::SanitizeFloat(Health1);
	FString IsDeadStr = "IsDead num = " + FString(IsDead1 ? "true" : "false");

	FString Stats = FString::Printf(TEXT(" \n == All Stats == \n %s \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"),*Stats);
	if(GEngine)
		{	
			GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red, Name);
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green, Stats, true, FVector2D(1.5f,1.5f));
		}
	
}

