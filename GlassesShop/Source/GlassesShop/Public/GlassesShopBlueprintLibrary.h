#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlassesShopBlueprintLibrary.generated.h"

UCLASS(meta = (ScriptName = "GlassesShopLibrary"))
class UGlassesShopBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GlassesShop")
	static void SetGlass(UObject* WorldContextObject, const FString& GlassName);
};