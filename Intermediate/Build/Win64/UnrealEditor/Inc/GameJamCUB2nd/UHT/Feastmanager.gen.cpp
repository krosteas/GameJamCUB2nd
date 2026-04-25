// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameJamCUB2nd/Gameloop/Feastmanager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeFeastmanager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_AFeastmanager();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_AFeastmanager_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameJamCUB2nd();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AFeastmanager ************************************************************
void AFeastmanager::StaticRegisterNativesAFeastmanager()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AFeastmanager;
UClass* AFeastmanager::GetPrivateStaticClass()
{
	using TClass = AFeastmanager;
	if (!Z_Registration_Info_UClass_AFeastmanager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("Feastmanager"),
			Z_Registration_Info_UClass_AFeastmanager.InnerSingleton,
			StaticRegisterNativesAFeastmanager,
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
	return Z_Registration_Info_UClass_AFeastmanager.InnerSingleton;
}
UClass* Z_Construct_UClass_AFeastmanager_NoRegister()
{
	return AFeastmanager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AFeastmanager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Gameloop/Feastmanager.h" },
		{ "ModuleRelativePath", "Gameloop/Feastmanager.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFeastmanager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AFeastmanager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_GameJamCUB2nd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFeastmanager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFeastmanager_Statics::ClassParams = {
	&AFeastmanager::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFeastmanager_Statics::Class_MetaDataParams), Z_Construct_UClass_AFeastmanager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFeastmanager()
{
	if (!Z_Registration_Info_UClass_AFeastmanager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFeastmanager.OuterSingleton, Z_Construct_UClass_AFeastmanager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFeastmanager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFeastmanager);
AFeastmanager::~AFeastmanager() {}
// ********** End Class AFeastmanager **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Gameloop_Feastmanager_h__Script_GameJamCUB2nd_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFeastmanager, AFeastmanager::StaticClass, TEXT("AFeastmanager"), &Z_Registration_Info_UClass_AFeastmanager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFeastmanager), 2267731753U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Gameloop_Feastmanager_h__Script_GameJamCUB2nd_1588279664(TEXT("/Script/GameJamCUB2nd"),
	Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Gameloop_Feastmanager_h__Script_GameJamCUB2nd_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Gameloop_Feastmanager_h__Script_GameJamCUB2nd_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
