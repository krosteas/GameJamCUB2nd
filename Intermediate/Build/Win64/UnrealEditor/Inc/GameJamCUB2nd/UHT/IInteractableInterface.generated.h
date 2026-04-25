// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Interaction/IInteractableInterface.h"

#ifdef GAMEJAMCUB2ND_IInteractableInterface_generated_h
#error "IInteractableInterface.generated.h already included, missing '#pragma once' in IInteractableInterface.h"
#endif
#define GAMEJAMCUB2ND_IInteractableInterface_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Interface UIInteractableInterface **********************************************
GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_UIInteractableInterface_NoRegister();

#define FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMEJAMCUB2ND_API UIInteractableInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UIInteractableInterface(UIInteractableInterface&&) = delete; \
	UIInteractableInterface(const UIInteractableInterface&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMEJAMCUB2ND_API, UIInteractableInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UIInteractableInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UIInteractableInterface) \
	virtual ~UIInteractableInterface() = default;


#define FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_13_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUIInteractableInterface(); \
	friend struct Z_Construct_UClass_UIInteractableInterface_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMEJAMCUB2ND_API UClass* Z_Construct_UClass_UIInteractableInterface_NoRegister(); \
public: \
	DECLARE_CLASS2(UIInteractableInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/GameJamCUB2nd"), Z_Construct_UClass_UIInteractableInterface_NoRegister) \
	DECLARE_SERIALIZER(UIInteractableInterface)


#define FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_13_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_13_GENERATED_UINTERFACE_BODY() \
	FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_13_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_13_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IIInteractableInterface() {} \
public: \
	typedef UIInteractableInterface UClassType; \
	typedef IIInteractableInterface ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_10_PROLOG
#define FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h_13_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UIInteractableInterface;

// ********** End Interface UIInteractableInterface ************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_LENOVO_Documents_Unreal_Projects_GameJamCUB2nd_Source_GameJamCUB2nd_Interaction_IInteractableInterface_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
