// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType:uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	//GENERATED_BODY()
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movevment")
	EMovementType MoveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movevment")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movevment")
	float Frequence = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Disign")
	float TimerRate = 3.0f;

};

UCLASS()
class MY_GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *BaseMesh;

	
	void SetGeometryData(const FGeometryData&Data){GeometryData=Data;}

	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const {return GeometryData;}

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;
	
	FOnTimeFinished OnTimeFinished;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponNum = 4;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;
	
	UPROPERTY(EditInstanceOnly, Category = "Helth")
	float Health = 34.2312;
	
	UPROPERTY(EditAnywhere, Category = "Helth")
	bool IsDead = false;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	
	FVector InitialLocation;
	FTimerHandle TimerHandle;

	const int32 MaxTimerCunt= 5;
	int32 TimerCount = 0;
	
	void PrintType();
	void PrintStringTipes();
	void PrintTransform();
	void HandleMovement();
	void SetColor(const FLinearColor&Color);
	void OnTimerFired();
};
