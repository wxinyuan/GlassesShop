#include "GlassesShopBlueprintLibrary.h"
#include "GlassesShopSubSystem.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void UGlassesShopBlueprintLibrary::SetGlass(UObject* WorldContextObject, const FString& GlassName)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World == nullptr)
	{
		return;
	}

	UGlassesShopSubsystem::Get(World)->SetGlass(GlassName);
}