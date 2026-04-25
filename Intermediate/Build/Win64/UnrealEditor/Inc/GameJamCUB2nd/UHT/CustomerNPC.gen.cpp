// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameJamCUB2nd/Customers/CustomerNPC.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCustomerNPC() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_ACustomerNPC();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_ACustomerNPC_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameJamCUB2nd();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACustomerNPC *************************************************************
void ACustomerNPC::StaticRegisterNativesACustomerNPC()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACustomerNPC;
UClass* ACustomerNPC::GetPrivateStaticClass()
{
	using TClass = ACustomerNPC;
	if (!Z_Registration_Info_UClass_ACustomerNPC.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CustomerNPC"),
			Z_Registration_Info_UClass_ACustomerNPC.InnerSingleton,
			StaticRegisterNativesACustomerNPC,
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
	return Z_Registration_Info_UClass_ACustomerNPC.InnerSingleton;
}
UClass* Z_Construct_UClass_ACustomerNPC_NoRegister()
{
	return ACustomerNPC::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACustomerNPC_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Customers/CustomerNPC.h" },
		{ "ModuleRelativePath", "Customers/CustomerNPC.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACustomerNPC>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ACustomerNPC_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_GameJamCUB2nd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACustomerNPC_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACustomerNPC_Statics::ClassParams = {
	&ACustomerNPC::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACustomerNPC_Statics::Class_MetaDataParams), Z_Construct_UClass_ACustomerNPC_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACustomerNPC()
{
	if (!Z_Registration_Info_UClass_ACustomerNPC.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACustomerNPC.OuterSingleton, Z_Construct_UClass_ACustomerNPC_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACustomerNPC.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACustomerNPC);
ACustomerNPC::~ACustomerNPC() {}
// ********** End Class ACustomerNPC ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Customers_CustomerNPC_h__Script_GameJamCUB2nd_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACustomerNPC, ACustomerNPC::StaticClass, TEXT("ACustomerNPC"), &Z_Registration_Info_UClass_ACustomerNPC, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACustomerNPC), 3889001169U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Customers_CustomerNPC_h__Script_GameJamCUB2nd_2098255079(TEXT("/Script/GameJamCUB2nd"),
	Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Customers_CustomerNPC_h__Script_GameJamCUB2nd_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Customers_CustomerNPC_h__Script_GameJamCUB2nd_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
