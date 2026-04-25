// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameJamCUB2nd/Gameloop/DayManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeDayManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_ADayManager();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_ADayManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameJamCUB2nd();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ADayManager **************************************************************
void ADayManager::StaticRegisterNativesADayManager()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADayManager;
UClass* ADayManager::GetPrivateStaticClass()
{
	using TClass = ADayManager;
	if (!Z_Registration_Info_UClass_ADayManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("DayManager"),
			Z_Registration_Info_UClass_ADayManager.InnerSingleton,
			StaticRegisterNativesADayManager,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_ADayManager.InnerSingleton;
}
UClass* Z_Construct_UClass_ADayManager_NoRegister()
{
	return ADayManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ADayManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Gameloop/DayManager.h" },
		{ "ModuleRelativePath", "Gameloop/DayManager.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADayManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ADayManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_GameJamCUB2nd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADayManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ADayManager_Statics::ClassParams = {
	&ADayManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADayManager_Statics::Class_MetaDataParams), Z_Construct_UClass_ADayManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ADayManager()
{
	if (!Z_Registration_Info_UClass_ADayManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADayManager.OuterSingleton, Z_Construct_UClass_ADayManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ADayManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ADayManager);
ADayManager::~ADayManager() {}
// ********** End Class ADayManager ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Gameloop_DayManager_h__Script_GameJamCUB2nd_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADayManager, ADayManager::StaticClass, TEXT("ADayManager"), &Z_Registration_Info_UClass_ADayManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADayManager), 756288860U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Gameloop_DayManager_h__Script_GameJamCUB2nd_2734387172(TEXT("/Script/GameJamCUB2nd"),
	Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Gameloop_DayManager_h__Script_GameJamCUB2nd_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Gameloop_DayManager_h__Script_GameJamCUB2nd_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
