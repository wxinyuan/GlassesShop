#pragma once
#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "Misc/CoreMisc.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"

#include "GlassesShopSubSystem.generated.h"

class ARoleActor;

UCLASS(MinimalAPI, DisplayName = "GlassesShop SubSystem")
class UGlassesShopSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	GLASSESSHOP_API static UGlassesShopSubsystem* Get(const UWorld* World);
	//GLASSESSHOP_API static UGlassesShopSubsystem* GetTargetingSubsystem(const UObject* WorldContextObject);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "UGlassesShopSubsystem")
	GLASSESSHOP_API void SetGlass(const FString& GlassName);

	UFUNCTION(BlueprintCallable, Category = "UGlassesShopSubsystem")
	GLASSESSHOP_API bool LoadObj(const FString& ObjFilePath);

	//UFUNCTION(BlueprintCallable, Category = "UGlassesShopSubsystem")
	//GLASSESSHOP_API void SetTexture(UTexture2D* Texture);

private:
	// FTickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override { return (HasAnyFlags(RF_ClassDefaultObject) ? ETickableTickType::Never : ETickableTickType::Conditional); }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UGlassesShopSubsystem, STATGROUP_Tickables); }
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	// ~FTickableGameObject interface

	void OnCreate(UWorld* World, const UWorld::InitializationValues IVS);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ARoleActor>	RoleActor;
	
	FDelegateHandle OnCreateDelegate;
};