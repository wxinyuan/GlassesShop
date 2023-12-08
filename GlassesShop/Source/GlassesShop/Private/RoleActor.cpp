// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleActor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARoleActor::ARoleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoleMesh"));
	RoleMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARoleActor::BeginPlay()
{
	Super::BeginPlay();
	
	//
	UMaterialInstance* MtlInstance = LoadObject<UMaterialInstance>(nullptr, TEXT("/game/Material/RoleMaterial_Inst.RoleMaterial_Inst"));
	if (MtlInstance != nullptr)
	{
		MID = UMaterialInstanceDynamic::Create(MtlInstance, this);
	}

	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		//UE_LOG(LogTemp, Log, TEXT("Name:%s"), *It->GetName());
		if (It->IsA<ACameraActor>())
		{
			Camera = Cast<ACameraActor>(*It);
			break;
		}
	}

	SetGlass(TEXT("Glass02"));
}

// Called every frame
void ARoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//
void ARoleActor::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &ARoleActor::OnTouchBegin);
	InputComponent->BindTouch(IE_Released, this, &ARoleActor::OnTouchEnd);
	InputComponent->BindTouch(IE_Repeat, this, &ARoleActor::OnFingerMove);
}

void ARoleActor::LoadRole(const FString& Name)
{
	if (CurrentRoleName == Name)
	{
		return;
	}

	UPackage* Package = LoadPackage(nullptr, *Name, LOAD_None);
	if (Package != nullptr)
	{
		UStaticMesh* Mesh = FindObject<UStaticMesh>(Package, TEXT("head3d"));
		if (Mesh != nullptr)
		{
			RoleMesh->SetStaticMesh(Mesh);
			//RoleMesh->AddLocalOffset(FVector(0.f, 0.f, 100.f));
		}
	}

	CurrentRoleName = Name;
}

void ARoleActor::SetGlass(const FString& GlassName)
{
	if (CurrentGlassName == GlassName)
	{
		return;
	}

	if (Glass != nullptr)
	{
		GetWorld()->DestroyActor(Glass);
	}

	FString GlassPath = TEXT("/Game/Glasses/Combine/");
	GlassPath += GlassName + TEXT(".") + GlassName + TEXT("_C");
	UClass* AClass = LoadClass<AActor>(nullptr, *GlassPath);
	if (AClass != nullptr)
	{
		//FTransform SpwanTransform = FTransform();
		FVector SpawnLocation(7.f, 0.f, 118.f);
		FRotator SpawnRotation(0.f, 180.f, 0.f);
		Glass = GetWorld()->SpawnActor<AActor>(AClass, SpawnLocation, SpawnRotation);
	}
	CurrentGlassName = GlassName;
}

void ARoleActor::OnTouchBegin(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		LastTouchDragLocation = FVector2D(Location);
	}
}

void ARoleActor::OnTouchEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		LastTouchDragLocation = FVector2D::ZeroVector;
	}
}

static const float TouchDragRotationScale = 0.1f;

void ARoleActor::OnFingerMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	if ((FingerIndex == ETouchIndex::Touch1) && (!LastTouchDragLocation.IsZero()))
	{
		FVector2D const DragDelta = (FVector2D(Location) - LastTouchDragLocation) * TouchDragRotationScale;

		AddYawInput(DragDelta.X);
		//AddPitchInput(DragDelta.Y);

		LastTouchDragLocation = FVector2D(Location);
	}
}

void ARoleActor::AddYawInput(float DeltaYaw)
{
	//UE_LOG(LogTemp, Log, TEXT("AddYawInput:%f"), DeltaYaw);

	//FRotator Rotator(DeltaYaw, 0.f, 0.f);
	//AddActorLocalRotation(Rotator);
	FRotator Rotator(0.f, DeltaYaw, 0.f);
	if (Camera != nullptr)
	{
		Camera->AddActorWorldRotation(Rotator);
		//UKismetMathLibrary::RotatorFromAxisAndAngle();
		//Camera->AddActorWorldOffset(FVector(DeltaYaw, 0.f, 0.f));
	}
	//APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//if (CameraManager != nullptr)
	//{
	//	CameraManager->AddActorWorldRotation(Rotator);
	//}
}