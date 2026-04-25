// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameJamCUB2nd/Customers/CustomerOrderComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCustomerOrderComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_UCustomerOrderComponent();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_UCustomerOrderComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameJamCUB2nd();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UCustomerOrderComponent **************************************************
void UCustomerOrderComponent::StaticRegisterNativesUCustomerOrderComponent()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCustomerOrderComponent;
UClass* UCustomerOrderComponent::GetPrivateStaticClass()
{
	using TClass = UCustomerOrderComponent;
	if (!Z_Registration_Info_UClass_UCustomerOrderComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CustomerOrderComponent"),
			Z_Registration_Info_UClass_UCustomerOrderComponent.InnerSingleton,
			StaticRegisterNativesUCustomerOrderComponent,
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
	return Z_Registration_Info_UClass_UCustomerOrderComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UCustomerOrderComponent_NoRegister()
{
	return UCustomerOrderComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCustomerOrderComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Customers/CustomerOrderComponent.h" },
		{ "ModuleRelativePath", "Customers/CustomerOrderComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomerOrderComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCustomerOrderComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_GameJamCUB2nd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomerOrderComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCustomerOrderComponent_Statics::ClassParams = {
	&UCustomerOrderComponent::StaticClass,
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
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomerOrderComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UCustomerOrderComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCustomerOrderComponent()
{
	if (!Z_Registration_Info_UClass_UCustomerOrderComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCustomerOrderComponent.OuterSingleton, Z_Construct_UClass_UCustomerOrderComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCustomerOrderComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomerOrderComponent);
UCustomerOrderComponent::~UCustomerOrderComponent() {}
// ********** End Class UCustomerOrderComponent ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Customers_CustomerOrderComponent_h__Script_GameJamCUB2nd_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCustomerOrderComponent, UCustomerOrderComponent::StaticClass, TEXT("UCustomerOrderComponent"), &Z_Registration_Info_UClass_UCustomerOrderComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCustomerOrderComponent), 3142300000U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Customers_CustomerOrderComponent_h__Script_GameJamCUB2nd_2842427008(TEXT("/Script/GameJamCUB2nd"),
	Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Customers_CustomerOrderComponent_h__Script_GameJamCUB2nd_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Customers_CustomerOrderComponent_h__Script_GameJamCUB2nd_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
