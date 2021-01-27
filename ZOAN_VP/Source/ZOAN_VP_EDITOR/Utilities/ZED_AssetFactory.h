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
#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ZED_AssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class ZOAN_VP_EDITOR_API UZED_AssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	
	UZED_AssetFactory();
	
	virtual UObject* FactoryCreateNew(UClass *          InClass ,
		                              UObject*          InParent, 
		                              FName             InName  , 
		                              EObjectFlags      Flags,
		                              UObject*          Context, 
		                              FFeedbackContext* Warn, 
		                              FName             CallingContext) override;
};
