#include "GlassesShopSubSystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "RoleActor.h"
#include "InterchangeManager.h"
#include "Misc/Paths.h"

#include "Fbx/InterchangeFbxTranslator.h"
#include "Gltf/InterchangeGltfTranslator.h"
//#include "InterchangeImportLog.h"
#include "InterchangeManager.h"
#include "Material/InterchangeMaterialFactory.h"
#include "MaterialX/InterchangeMaterialXTranslator.h"
#include "Mesh/InterchangeOBJTranslator.h"
#include "Mesh/InterchangePhysicsAssetFactory.h"
#include "Mesh/InterchangeSkeletalMeshFactory.h"
#include "Mesh/InterchangeSkeletonFactory.h"
#include "Mesh/InterchangeStaticMeshFactory.h"
#include "Misc/CoreDelegates.h"
#include "Modules/ModuleManager.h"
#include "Scene/InterchangeActorFactory.h"
#include "Scene/InterchangeCameraActorFactory.h"
#include "Scene/InterchangeSceneImportAssetFactory.h"
#include "Scene/InterchangeLightActorFactory.h"
#include "Scene/InterchangeSceneVariantSetsFactory.h"
#include "Scene/InterchangeStaticMeshActorFactory.h"
#include "Scene/InterchangeSkeletalMeshActorFactory.h"
#include "Texture/InterchangeImageWrapperTranslator.h"
#include "Texture/InterchangeDDSTranslator.h"
#include "Texture/InterchangeIESTranslator.h"
#include "Texture/InterchangeJPGTranslator.h"
#include "Texture/InterchangePCXTranslator.h"
#include "Texture/InterchangePSDTranslator.h"
#include "Texture/InterchangeTextureFactory.h"
#include "StaticMeshCompiler.h"

UE_DISABLE_OPTIMIZATION
UGlassesShopSubsystem* UGlassesShopSubsystem::Get(const UWorld* World)
{
	if (World)
	{
		return UGameInstance::GetSubsystem<UGlassesShopSubsystem>(World->GetGameInstance());
	}

	return nullptr;
}

void UGlassesShopSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//UInterchangeManager::SetInterchangeImportEnabled(true);

	//FInterchangeImportMaterialAsyncHelper& InterchangeMaterialAsyncHelper = FInterchangeImportMaterialAsyncHelper::GetInstance();

	auto RegisterItems = []()
		{
			UInterchangeManager& InterchangeManager = UInterchangeManager::GetInterchangeManager();

			//Register the translators
			//Scenes
			InterchangeManager.RegisterTranslator(UInterchangeFbxTranslator::StaticClass());
			//InterchangeManager.RegisterTranslator(UInterchangeGLTFTranslator::StaticClass());
			InterchangeManager.RegisterTranslator(UInterchangeOBJTranslator::StaticClass());

			//Materials
			InterchangeManager.RegisterTranslator(UInterchangeMaterialXTranslator::StaticClass());

			//Textures
			InterchangeManager.RegisterTranslator(UInterchangeImageWrapperTranslator::StaticClass());
			InterchangeManager.RegisterTranslator(UInterchangeDDSTranslator::StaticClass());
			InterchangeManager.RegisterTranslator(UInterchangeJPGTranslator::StaticClass());
			InterchangeManager.RegisterTranslator(UInterchangePCXTranslator::StaticClass());
			InterchangeManager.RegisterTranslator(UInterchangePSDTranslator::StaticClass());
			InterchangeManager.RegisterTranslator(UInterchangeIESTranslator::StaticClass());

			//Register the factories
			InterchangeManager.RegisterFactory(UInterchangeTextureFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeMaterialFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeMaterialFunctionFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeSkeletonFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeSkeletalMeshFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeStaticMeshFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangePhysicsAssetFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeActorFactory::StaticClass());
			//InterchangeManager.RegisterFactory(UInterchangeAnimationTrackSetFactory::StaticClass());
			//InterchangeManager.RegisterFactory(UInterchangeAnimSequenceFactory::StaticClass());
			//InterchangeManager.RegisterFactory(UInterchangeCineCameraActorFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeCameraActorFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeStaticMeshActorFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeSkeletalMeshActorFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeSceneVariantSetsFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeLightActorFactory::StaticClass());
			InterchangeManager.RegisterFactory(UInterchangeSceneImportAssetFactory::StaticClass());
		};

	if (GEngine)
	{
		RegisterItems();
	}
	else
	{
		FCoreDelegates::OnPostEngineInit.AddLambda(RegisterItems);
	}

	UInterchangeManager::SetInterchangeImportEnabled(true);

	OnCreateDelegate = FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UGlassesShopSubsystem::OnCreate);
}

void UGlassesShopSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FWorldDelegates::OnPostWorldInitialization.Remove(OnCreateDelegate);
}

void UGlassesShopSubsystem::Tick(float DeltaTime)
{
	
}

void UGlassesShopSubsystem::OnCreate(UWorld* World, const UWorld::InitializationValues IVS)
{
	FVector SpawnLocation(0.f, 0.f, 90.f);
	FRotator SpawnRotation(0.f, 90.f, 90.f);

	RoleActor = World->SpawnActor<ARoleActor>(SpawnLocation, SpawnRotation);
	if (RoleActor != nullptr)
	{
		RoleActor->LoadRole(TEXT("/Game/Role/head3d"));
	}
}

void UGlassesShopSubsystem::SetGlass(const FString& GlassName)
{
	if (RoleActor == nullptr)
	{
		return;
	}

	RoleActor->SetGlass(GlassName);
}

bool UGlassesShopSubsystem::LoadObj(const FString& ObjFilePath)
{
	if (RoleActor == nullptr || ObjFilePath.IsEmpty())
	{
		return false;
	}

	//FString SaveDir = FPaths::ProjectSavedDir();
	FString SaveDir = TEXT("/game/Test");
	//FString Path = FPaths::ProjectSavedDir() + TEXT("head3d.obj");
	FString Path = TEXT("/storage/emulated/0/Role/head3d.obj");
	UInterchangeSourceData* SourceData = UInterchangeManager::CreateSourceData(Path);
	if (SourceData == nullptr)
	{
		return false;
	}

	FImportAssetParameters Param;
	Param.bIsAutomated = true;

	bool bSuccess = UInterchangeManager::GetInterchangeManager().ImportAsset(SaveDir, SourceData, Param);

	if (bSuccess)
	{
#if WITH_EDITOR
		FStaticMeshCompilingManager::Get().FinishAllCompilation();
#endif // WITH_EDITOR

		UPackage* TexPackage = LoadPackage(nullptr, TEXT("/Game/Test/TEX_head3d"), LOAD_None);
		if (TexPackage != nullptr)
		{
			UTexture2D* Texture = FindObject<UTexture2D>(TexPackage, TEXT("TEX_head3d"));
			if (Texture != nullptr)
			{
				Texture->NeverStream = 1;
				RoleActor->MID->SetTextureParameterValue(FName(TEXT("diffuse")), Texture);
			}
		}

		UPackage* Package = LoadPackage(nullptr, TEXT("/Game/Test/head3d"), LOAD_None);
		if (Package != nullptr)
		{
			UStaticMesh* Mesh = FindObject<UStaticMesh>(Package, TEXT("head3d"));
			if (Mesh != nullptr)
			{
				RoleActor->RoleMesh->SetStaticMesh(Mesh);
				RoleActor->RoleMesh->SetMaterial(0, RoleActor->MID);
			}
		}
	}
	return bSuccess;
}
UE_ENABLE_OPTIMIZATION