// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameJamCUB2nd/Crafting/CraftingComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCraftingComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_UCraftingComponent();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_UCraftingComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameJamCUB2nd();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UCraftingComponent *******************************************************
void UCraftingComponent::StaticRegisterNativesUCraftingComponent()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCraftingComponent;
UClass* UCraftingComponent::GetPrivateStaticClass()
{
	using TClass = UCraftingComponent;
	if (!Z_Registration_Info_UClass_UCraftingComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CraftingComponent"),
			Z_Registration_Info_UClass_UCraftingComponent.InnerSingleton,
			StaticRegisterNativesUCraftingComponent,
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
	return Z_Registration_Info_UClass_UCraftingComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UCraftingComponent_NoRegister()
{
	return UCraftingComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCraftingComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Crafting/CraftingComponent.h" },
		{ "ModuleRelativePath", "Crafting/CraftingComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCraftingComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCraftingComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_GameJamCUB2nd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCraftingComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCraftingComponent_Statics::ClassParams = {
	&UCraftingComponent::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCraftingComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UCraftingComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCraftingComponent()
{
	if (!Z_Registration_Info_UClass_UCraftingComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCraftingComponent.OuterSingleton, Z_Construct_UClass_UCraftingComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCraftingComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCraftingComponent);
UCraftingComponent::~UCraftingComponent() {}
// ********** End Class UCraftingComponent *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Crafting_CraftingComponent_h__Script_GameJamCUB2nd_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCraftingComponent, UCraftingComponent::StaticClass, TEXT("UCraftingComponent"), &Z_Registration_Info_UClass_UCraftingComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCraftingComponent), 1867223054U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Crafting_CraftingComponent_h__Script_GameJamCUB2nd_3683922745(TEXT("/Script/GameJamCUB2nd"),
	Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Crafting_CraftingComponent_h__Script_GameJamCUB2nd_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Crafting_CraftingComponent_h__Script_GameJamCUB2nd_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
