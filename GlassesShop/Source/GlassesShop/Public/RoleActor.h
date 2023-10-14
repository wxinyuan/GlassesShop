// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RoleActor.generated.h"

UCLASS()
class GLASSESSHOP_API ARoleActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoleActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RoleMesh;

	UPROPERTY(VisibleAnywhere)
	AActor* Glass;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* MID;

public:
	void LoadRole(const FString& Name);

	void SetGlass(const FString& GlassName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnTouchBegin(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchEnd(ETouchIndex::Type FingerIndex, FVector Location);
	void OnFingerMove(ETouchIndex::Type FingerIndex, FVector Location);

	void AddYawInput(float DeltaYaw);

private:
	ACameraActor* Camera;

	/** The normalized screen location when a drag starts */
	FVector2D LastTouchDragLocation;

	FString CurrentRoleName;
	FString CurrentGlassName;
};
