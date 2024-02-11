// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Starchitect/MyGameStateBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyGameStateBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameStateBase();
	STARCHITECT_API UClass* Z_Construct_UClass_AMyGameStateBase();
	STARCHITECT_API UClass* Z_Construct_UClass_AMyGameStateBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Starchitect();
// End Cross Module References
	void AMyGameStateBase::StaticRegisterNativesAMyGameStateBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyGameStateBase);
	UClass* Z_Construct_UClass_AMyGameStateBase_NoRegister()
	{
		return AMyGameStateBase::StaticClass();
	}
	struct Z_Construct_UClass_AMyGameStateBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyGameStateBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameStateBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Starchitect,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyGameStateBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyGameStateBase_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "MyGameStateBase.h" },
		{ "ModuleRelativePath", "MyGameStateBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMyGameStateBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyGameStateBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyGameStateBase_Statics::ClassParams = {
		&AMyGameStateBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyGameStateBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyGameStateBase_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AMyGameStateBase()
	{
		if (!Z_Registration_Info_UClass_AMyGameStateBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyGameStateBase.OuterSingleton, Z_Construct_UClass_AMyGameStateBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMyGameStateBase.OuterSingleton;
	}
	template<> STARCHITECT_API UClass* StaticClass<AMyGameStateBase>()
	{
		return AMyGameStateBase::StaticClass();
	}
	AMyGameStateBase::AMyGameStateBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyGameStateBase);
	AMyGameStateBase::~AMyGameStateBase() {}
	struct Z_CompiledInDeferFile_FID_Starchitect_Source_Starchitect_MyGameStateBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Starchitect_Source_Starchitect_MyGameStateBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMyGameStateBase, AMyGameStateBase::StaticClass, TEXT("AMyGameStateBase"), &Z_Registration_Info_UClass_AMyGameStateBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyGameStateBase), 1328959014U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Starchitect_Source_Starchitect_MyGameStateBase_h_1647030104(TEXT("/Script/Starchitect"),
		Z_CompiledInDeferFile_FID_Starchitect_Source_Starchitect_MyGameStateBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Starchitect_Source_Starchitect_MyGameStateBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
