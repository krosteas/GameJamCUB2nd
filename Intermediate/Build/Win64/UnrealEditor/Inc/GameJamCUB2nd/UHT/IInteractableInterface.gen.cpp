// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameJamCUB2nd/Interaction/IInteractableInterface.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeIInteractableInterface() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_UIInteractableInterface();
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_UIInteractableInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameJamCUB2nd();
// ********** End Cross Module References **********************************************************

// ********** Begin Interface UIInteractableInterface **********************************************
void UIInteractableInterface::StaticRegisterNativesUIInteractableInterface()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UIInteractableInterface;
UClass* UIInteractableInterface::GetPrivateStaticClass()
{
	using TClass = UIInteractableInterface;
	if (!Z_Registration_Info_UClass_UIInteractableInterface.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("IInteractableInterface"),
			Z_Registration_Info_UClass_UIInteractableInterface.InnerSingleton,
			StaticRegisterNativesUIInteractableInterface,
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
	return Z_Registration_Info_UClass_UIInteractableInterface.InnerSingleton;
}
UClass* Z_Construct_UClass_UIInteractableInterface_NoRegister()
{
	return UIInteractableInterface::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UIInteractableInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Interaction/IInteractableInterface.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IIInteractableInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UIInteractableInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_GameJamCUB2nd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UIInteractableInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UIInteractableInterface_Statics::ClassParams = {
	&UIInteractableInterface::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UIInteractableInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UIInteractableInterface_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UIInteractableInterface()
{
	if (!Z_Registration_Info_UClass_UIInteractableInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UIInteractableInterface.OuterSingleton, Z_Construct_UClass_UIInteractableInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UIInteractableInterface.OuterSingleton;
}
UIInteractableInterface::UIInteractableInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UIInteractableInterface);
// ********** End Interface UIInteractableInterface ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h__Script_GameJamCUB2nd_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UIInteractableInterface, UIInteractableInterface::StaticClass, TEXT("UIInteractableInterface"), &Z_Registration_Info_UClass_UIInteractableInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UIInteractableInterface), 208622514U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h__Script_GameJamCUB2nd_1134998898(TEXT("/Script/GameJamCUB2nd"),
	Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h__Script_GameJamCUB2nd_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h__Script_GameJamCUB2nd_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
