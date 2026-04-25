// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameJamCUB2nd/Crafting/AlchemyStation.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAlchemyStation() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_AALchemyStation();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_AALchemyStation_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameJamCUB2nd();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AALchemyStation **********************************************************
void AALchemyStation::StaticRegisterNativesAALchemyStation()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AALchemyStation;
UClass* AALchemyStation::GetPrivateStaticClass()
{
	using TClass = AALchemyStation;
	if (!Z_Registration_Info_UClass_AALchemyStation.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("ALchemyStation"),
			Z_Registration_Info_UClass_AALchemyStation.InnerSingleton,
			StaticRegisterNativesAALchemyStation,
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
	return Z_Registration_Info_UClass_AALchemyStation.InnerSingleton;
}
UClass* Z_Construct_UClass_AALchemyStation_NoRegister()
{
	return AALchemyStation::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AALchemyStation_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Crafting/AlchemyStation.h" },
		{ "ModuleRelativePath", "Crafting/AlchemyStation.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AALchemyStation>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AALchemyStation_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_GameJamCUB2nd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AALchemyStation_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AALchemyStation_Statics::ClassParams = {
	&AALchemyStation::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AALchemyStation_Statics::Class_MetaDataParams), Z_Construct_UClass_AALchemyStation_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AALchemyStation()
{
	if (!Z_Registration_Info_UClass_AALchemyStation.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AALchemyStation.OuterSingleton, Z_Construct_UClass_AALchemyStation_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AALchemyStation.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AALchemyStation);
AALchemyStation::~AALchemyStation() {}
// ********** End Class AALchemyStation ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Crafting_AlchemyStation_h__Script_GameJamCUB2nd_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AALchemyStation, AALchemyStation::StaticClass, TEXT("AALchemyStation"), &Z_Registration_Info_UClass_AALchemyStation, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AALchemyStation), 2882324128U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Crafting_AlchemyStation_h__Script_GameJamCUB2nd_2552163237(TEXT("/Script/GameJamCUB2nd"),
	Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Crafting_AlchemyStation_h__Script_GameJamCUB2nd_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Crafting_AlchemyStation_h__Script_GameJamCUB2nd_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
