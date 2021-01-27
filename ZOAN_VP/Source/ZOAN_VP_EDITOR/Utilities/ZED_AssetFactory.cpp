/******************************************************************************/
/*Project: ZOAN Editor Extensions                                             */
/*Description:                                                                */
/*The Zoan Editor Extensions is a plug-In responsible to handle the runtime   */
/*Object Customizations and Parameterization for the Zoan Runtime Production  */
/*Plug-In                                                                     */
/******************************************************************************/
/*Object Description:                                                         */
/******************************************************************************/
/*Copyright Zoan Oy, Inc. All Rights Reserved.                                */
/*Author: William D. Wolff                                                    */
/******************************************************************************/

#include "ZED_AssetFactory.h"
#include "../Screens/ZED_ConfigurationData.h"

UZED_AssetFactory::UZED_AssetFactory()
	:Super()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = AZED_ConfigurationData::StaticClass();
}

UObject* UZED_AssetFactory::FactoryCreateNew(UClass* InClass, 
	                                         UObject* InParent, 
	                                         FName InName, 
	                                         EObjectFlags Flags, 
	                                         UObject* Context, 
	                                         FFeedbackContext* Warn, 
	                                         FName 	CallingContext)
{
	auto   NewObjectAsset = NewObject<AZED_ConfigurationData>(InParent,InClass, InName, Flags);
	return NewObjectAsset;
}