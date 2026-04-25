// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameJamCUB2nd/Player/ShopKeeperCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeShopKeeperCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_AShopKeeperCharacter();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_AShopKeeperCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameJamCUB2nd();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AShopKeeperCharacter *****************************************************
void AShopKeeperCharacter::StaticRegisterNativesAShopKeeperCharacter()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AShopKeeperCharacter;
UClass* AShopKeeperCharacter::GetPrivateStaticClass()
{
	using TClass = AShopKeeperCharacter;
	if (!Z_Registration_Info_UClass_AShopKeeperCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("ShopKeeperCharacter"),
			Z_Registration_Info_UClass_AShopKeeperCharacter.InnerSingleton,
			StaticRegisterNativesAShopKeeperCharacter,
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
	return Z_Registration_Info_UClass_AShopKeeperCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_AShopKeeperCharacter_NoRegister()
{
	return AShopKeeperCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AShopKeeperCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Player/ShopKeeperCharacter.h" },
		{ "ModuleRelativePath", "Player/ShopKeeperCharacter.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AShopKeeperCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AShopKeeperCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_GameJamCUB2nd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AShopKeeperCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AShopKeeperCharacter_Statics::ClassParams = {
	&AShopKeeperCharacter::StaticClass,
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
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AShopKeeperCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AShopKeeperCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AShopKeeperCharacter()
{
	if (!Z_Registration_Info_UClass_AShopKeeperCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AShopKeeperCharacter.OuterSingleton, Z_Construct_UClass_AShopKeeperCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AShopKeeperCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AShopKeeperCharacter);
AShopKeeperCharacter::~AShopKeeperCharacter() {}
// ********** End Class AShopKeeperCharacter *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Player_ShopKeeperCharacter_h__Script_GameJamCUB2nd_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AShopKeeperCharacter, AShopKeeperCharacter::StaticClass, TEXT("AShopKeeperCharacter"), &Z_Registration_Info_UClass_AShopKeeperCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AShopKeeperCharacter), 3446492082U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Player_ShopKeeperCharacter_h__Script_GameJamCUB2nd_3745763428(TEXT("/Script/GameJamCUB2nd"),
	Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Player_ShopKeeperCharacter_h__Script_GameJamCUB2nd_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Player_ShopKeeperCharacter_h__Script_GameJamCUB2nd_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
