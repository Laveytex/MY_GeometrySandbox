// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGeometryActor.h"
#include "GameFramework/Actor.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayLoad
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;
	
	UPROPERTY(EditAnywhere)
	FGeometryData Data;
	
	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
	
};


UCLASS()
class MY_GEOMETRYSANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;
	

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayLoad>  GeometryPayLoad;
	
private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABaseGeometryActor* NonePropertyActor;
	UPROPERTY()
	ABaseGeometryActor* PropertyActor;

	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();
	void DoActorSpawn4();
	

	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);
	
	void OnTimeFinished(AActor* Actor);
};
