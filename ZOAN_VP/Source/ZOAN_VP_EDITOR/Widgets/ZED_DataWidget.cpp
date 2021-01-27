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
#include "ZED_DataWidget.h"
#include "UObject/Field.h"
#include "UObject/UnrealType.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "../Utilities/ZED_FunctionLibrary.h"

/**
This is a default method for a Slate Object and will be important to make possible syncronize the Data inside of
ZOAN VP Plug-In and The ZOAN Editor Extension.
In fact we are naming the the classes here as Assets but in fact all of them are UObjects making possible serialize
them using the refletion system and exchange data between the plug-ins.
*/
void ZED_DataWidget::Construct(const FArguments& Args)
{
	
	Item = Args._Item;

	UseCustomControls = false;

	if(Item)ReadAsset();

	HeaderRowDefinitions = SNew(SHeaderRow);

	HeaderRowDefinitions->AddColumn(SHeaderRow::Column(FName("FieldName")).DefaultLabel(FText::FromString(" ")));
	HeaderRowDefinitions->AddColumn(SHeaderRow::Column(FName("Widget")).DefaultLabel(FText::FromString(" ")));

	if (Item)
	{
		ChildSlot
			[
				//Creating the button that adds a new item on the list when pressed
				SNew(SScrollBox)
				+ SScrollBox::Slot()
			[
				SNew(SButton).Text(FText::FromString(TEXT("Save Configuration Asset Properties")))
				.OnClicked(this, &ZED_DataWidget::ButtonPressed)
			[
				SNew(SImage).Image(this, &ZED_DataWidget::GetImageBrush)
			]
			]
		//The actual list view creation
		+ SScrollBox::Slot()
			[
				SAssignNew(ListViewWidget, STreeView<TSharedPtr<ZED_AssetField>>)
				.ItemHeight(50)
			.TreeItemsSource(&FieldList) //Substituido Itens por FieldList
			.OnGenerateRow(this, &ZED_DataWidget::OnGenerateRowForList)
			.OnGetChildren(this, &ZED_DataWidget::OnGetChildrenForList)
			.HeaderRow(HeaderRowDefinitions)
			]
			];
	}
	else
	{
		ChildSlot
			[
				//Creating the button that adds a new item on the list when pressed
				SNew(SScrollBox)
				+ SScrollBox::Slot()
			[
				SNew(SButton).Text(FText::FromString(TEXT("Save Configuration Asset Properties")))
				.OnClicked(this, &ZED_DataWidget::ButtonPressed)
			[
				SNew(SImage).Image(this, &ZED_DataWidget::GetImageBrush)
			]
			]
		//The actual list view creation
		+ SScrollBox::Slot()
			[
				SNew(STextBlock).Text(FText::FromString("There is No Data Configuration to be Saved!"))
			]
			];
	}
}

const FSlateBrush* ZED_DataWidget::GetImageBrush() const
{
	FName BrushName;

	BrushName = TEXT("ButtonIcon_custom");

	return FZED_Style::Get().GetBrush(BrushName);
}

/**
This Method will be important since following the Data Driven Design made in the Unreal Engine we will need at the end of each tool
some default buttons to operate in the forms.
*/
FReply ZED_DataWidget::ButtonPressed()
{
	if (!Item)return FReply::Unhandled();

	//Read the entire asset and "Translate" the properties in the Reflectiuon structure(ZED_AssetField)
	ReadAsset();

	//Request the Widget be Updated with the new values
	ListViewWidget->RequestTreeRefresh();

	//The default Widget response to mantain Slate working properly
	return FReply::Handled();
}

/**
This Method takes advantage of the Unreal´s Reflection System to dinamically parse all the Asset Fields
This will be moved to a specific class and its importance are based on the efforts needed to use the internal Editor structures...
Simplifying... We take less time defining a "little deflection table" and using basic Slate Objects to compound our Widgets, than trying
Find Out an Object that make the job for us(All the logic are spread across the Core System designed to work internally in the engine 
itself and are not prepeared for editor extension)...
*/
void ZED_DataWidget::ReadAsset()
{
	int Counter = 0;
	
	//Parse only valid object!
	if (!Item)return;

	//Get the Static Class used to find out object pointers and structs
	ItemStaticClass = Item->GetClass();

	//Acctually we are reading the Asset directly, later we will decouple this passing an asset by parameter List.
	//STEP 01: Fill the Field Control Attributes
	for (TFieldIterator<FProperty> PropertyIterator(ItemStaticClass); PropertyIterator; ++PropertyIterator)
	{
		//For each property the Unreal Reflection System provides all the information needed to build the refletion table
		FProperty* Property = *PropertyIterator;

		//To mantain memory and Unreal´s Sanity...we use TSharedPtr here... Tadá! :)
		TSharedPtr<ZED_AssetField> tAssetField = MakeShareable(new ZED_AssetField());
		
		//Assign the Field Original Order
		tAssetField.Get()->FieldOrder = Counter;

		FProperty     * FieldProperty    = CastField<FProperty>(Property);
		UStruct       * FieldStruct      = FieldProperty->GetOwnerStruct();
		UObject       * FieldOwner       = Item;
		UClass        * FieldStaticClass = ItemStaticClass;
		void          * FieldContainer   = Property->ContainerPtrToValuePtr<void>(FieldOwner);

		//WARNING - Only the properties declared on the class scope must be processed
		//If we remove this check ALL will be parsed generating fails at the class scope pointer for structs.
		if (!FieldProperty->GetFName().ToString().Contains("ZED_"))
		{
			//Only Fields decleared on the DataClass Scope need be processed!
			continue;
		}

		ExtractFieldHeaders(tAssetField, Counter, FieldProperty , FieldOwner , FieldStaticClass , FieldContainer);

		if (tAssetField.Get()->IsEnum == true)
		{
			ExtractEnumValues(tAssetField,false);
		}
		else if (tAssetField.Get()->IsStruct == true)
		{
			ExtractStructValues(tAssetField,false);
		}
		else if (tAssetField.Get()->IsObject == true)
		{
			ExtractObjectValues(tAssetField,false);
		}
		else if (tAssetField.Get()->IsNative == true)
		{
			if (tAssetField.Get()->IsNumber == true)
			{
				ExtractNumericValue(tAssetField,false);
			}
			else if (tAssetField.Get()->IsConditional == true)
			{
				ExtractBoolValue(tAssetField,false);
			}
			else
			{
				ExtractAlphaNmValue(tAssetField,false);
			}
		}
		else if (tAssetField.Get()->IsNative == false)
		{
			if (tAssetField.Get()->IsNumber == true)
			{
				ExtractNumericValue(tAssetField,false);
			}
			else if (tAssetField.Get()->IsConditional == true)
			{
				ExtractBoolValue(tAssetField,false);
			}
			else
			{
				ExtractAlphaNmValue(tAssetField,false);
			}
		}
		
		FieldList.Add(tAssetField);
		Counter++;
	}
}

void ZED_DataWidget::ExtractFieldHeaders(TSharedPtr<ZED_AssetField> pAssetField,int pFieldOrder , FProperty* pOwnerProperty , UObject* pFieldOwner , UClass* pFieldStaticClass , void *pFieldContainer)
{

	//Sadly, in the past, the core of the engine and reflection system uses FString and Blueprints work only with FText without any operator override 
	FString Workspace;

	//Assign the Field Original Order
	pAssetField.Get()->FieldOrder = pFieldOrder;

	//Fill the original property for future reference
	pAssetField.Get()->FieldProperty    = pOwnerProperty;
	pAssetField.Get()->FieldOwner       = pFieldOwner;
	pAssetField.Get()->FieldContainer   = pFieldContainer;
	pAssetField.Get()->FieldStaticClass = pFieldStaticClass;

	//Get the Name of The Field from reflection system
	Workspace = pOwnerProperty->GetFName().ToString();
	pAssetField.Get()->FieldName = Workspace;
	Workspace.Empty();

	//Get the Field Type from reflection system
	Workspace = pOwnerProperty->GetCPPType();
	pAssetField.Get()->FieldType = Workspace;
	Workspace.Empty();

	//Initialize the Field Flags (This flags are more than enoth to stablish a good graph in future... ;)
	pAssetField.Get()->IsNative      = false;
	pAssetField.Get()->IsNumber      = false;
	pAssetField.Get()->IsConditional = false;
	pAssetField.Get()->IsStruct      = false;
	pAssetField.Get()->IsEnum        = false;
	pAssetField.Get()->IsObject      = false;
	
	//Use Custom Controls?
	pAssetField.Get()->IsCustom = UseCustomControls;

	//Define if its a Native Declaration, a struct or an enumeration Field
	Workspace = pOwnerProperty->GetCPPTypeForwardDeclaration();
	if (Workspace.IsEmpty())
	{
		if(pAssetField.Get()->FieldType.Contains("int32"  )) { pAssetField.Get()->IsNumber      = true ; pAssetField.Get()->IsNative = true ; }
		if(pAssetField.Get()->FieldType.Contains("long"   )) { pAssetField.Get()->IsNumber      = true ; pAssetField.Get()->IsNative = true ; }
		if(pAssetField.Get()->FieldType.Contains("float"  )) { pAssetField.Get()->IsNumber      = true ; pAssetField.Get()->IsNative = true ; }
		if(pAssetField.Get()->FieldType.Contains("double" )) { pAssetField.Get()->IsNumber      = true ; pAssetField.Get()->IsNative = true ; }
		if(pAssetField.Get()->FieldType.Contains("bool"   )) { pAssetField.Get()->IsConditional = true ; pAssetField.Get()->IsNative = true ; }
		if(pAssetField.Get()->FieldType.Contains("FString")) { pAssetField.Get()->IsNumber      = false; pAssetField.Get()->IsNative = false; }
	}
	else if (Workspace.Contains("struct"))
	{
		pAssetField.Get()->IsStruct  = true;
	}
	else if (Workspace.Contains("enum"))
	{
		pAssetField.Get()->IsEnum = true;
	}
	else if (Workspace.Contains("class"))
	{
		pAssetField.Get()->IsObject       = true;
	}
}

void ZED_DataWidget::ExtractNumericValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FNumericProperty* Property = (FNumericProperty*)pAssetField.Get()->FieldProperty;

	if (Property->IsInteger())
	{
		if (pAssetField.Get()->FieldType == "int32")
		{
			ExtractIntValue(pAssetField, isStrObj);
		}
		if (pAssetField.Get()->FieldType == "long")
		{
			ExtractLongValue(pAssetField, isStrObj);
		}
	}
	else
	{
		if (pAssetField.Get()->FieldType == "float")
		{
			ExtractFloatValue(pAssetField, isStrObj);
		}
		if (pAssetField.Get()->FieldType == "double")
		{
			ExtractDoubleValue(pAssetField, isStrObj);
		}
	}
}

void ZED_DataWidget::ExtractAlphaNmValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	if (pAssetField.Get()->FieldProperty->IsNative())
	{
		if (pAssetField.Get()->FieldType == "FString")
		{
			ExtractFStringValue(pAssetField, isStrObj);
		}
		if (pAssetField.Get()->FieldType == "FText")
		{
			ExtractFTextValue(pAssetField, isStrObj);
		}
	}
	else
	{
		if (pAssetField.Get()->FieldType == "FString")
		{
			ExtractFStringValue(pAssetField, isStrObj);
		}
		if (pAssetField.Get()->FieldType == "FText")
		{
			ExtractFTextValue(pAssetField, isStrObj);
		}
	}
}

void ZED_DataWidget::ExtractIntValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FNumericProperty* Property = (FNumericProperty * )pAssetField.Get()->FieldProperty;

	if (Property->IsInteger())
	{
		if (pAssetField.Get()->FieldType == "int32")
		{
			if (!isStrObj)
			{
				//Get the single property Widget
				pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());

				int* IntPtr = Property->ContainerPtrToValuePtr<int>(pAssetField.Get()->FieldOwner);
				if (IntPtr != NULL)
				{
					pAssetField.Get()->FieldIntValue = *IntPtr;
				}
			}
			else
			{
				//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
				pAssetField.Get()->IsCustom = true;

				//pAssetField.Get()->FieldIntValue = 999;
				int* IntPtr = Property->ContainerPtrToValuePtr<int>(pAssetField.Get()->FieldContainer);
				if (IntPtr != NULL)
				{
					pAssetField.Get()->FieldIntValue = *IntPtr;
				}
			}
		}
	}
}

void ZED_DataWidget::ExtractFloatValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FNumericProperty* Property = (FNumericProperty*)pAssetField.Get()->FieldProperty;

	if (Property->IsFloatingPoint())
	{
		if (pAssetField.Get()->FieldType == "float")
		{
			if (!isStrObj)
			{
				//Get the single property Widget
				pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());

				float* FloatPtr = Property->ContainerPtrToValuePtr<float>(pAssetField.Get()->FieldOwner);
				if (FloatPtr != NULL)
				{
					pAssetField.Get()->FieldFloatValue = *FloatPtr;
				}
			}
			else
			{
				//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
				pAssetField.Get()->IsCustom = true;

				//pAssetField.Get()->FieldFloatValue = 9.999;
				float* FloatPtr = Property->ContainerPtrToValuePtr<float>(pAssetField.Get()->FieldContainer);
				if (FloatPtr != NULL)
				{
					pAssetField.Get()->FieldFloatValue = *FloatPtr;
				}
			}
		}
	}
}

void ZED_DataWidget::ExtractDoubleValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FNumericProperty* Property = (FNumericProperty*)pAssetField.Get()->FieldProperty;

	if (Property->IsFloatingPoint())
	{
		if (pAssetField.Get()->FieldType == "double")
		{
			if (!isStrObj)
			{
				//Get the single property Widget
				pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());

				double* DoublePtr = Property->ContainerPtrToValuePtr<double>(pAssetField.Get()->FieldOwner);
				if (DoublePtr != NULL)
				{
					pAssetField.Get()->FieldDoubleValue = *DoublePtr;
				}
			}
			else
			{
				//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
				pAssetField.Get()->IsCustom = true;

				//pAssetField.Get()->FieldDoubleValue = 9.999;
				double* DoublePtr = Property->ContainerPtrToValuePtr<double>(pAssetField.Get()->FieldContainer);
				if (DoublePtr != NULL)
				{
					pAssetField.Get()->FieldDoubleValue = *DoublePtr;
				}
			}
		}
	}
}

void ZED_DataWidget::ExtractLongValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FNumericProperty* Property = (FNumericProperty*)pAssetField.Get()->FieldProperty;
	
	if (Property->IsInteger())
	{
		if (pAssetField.Get()->FieldType == "long")
		{
			if (!isStrObj)
			{
				//Get the single property Widget
				pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());

				long* LongPtr = Property->ContainerPtrToValuePtr<long>(pAssetField.Get()->FieldOwner);
				if (LongPtr != NULL)
				{
					pAssetField.Get()->FieldLongValue = *LongPtr;
				}
			}
			else
			{
				//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
				pAssetField.Get()->IsCustom = true;

				//pAssetField.Get()->FieldLongValue = 999;
				long* LongPtr = Property->ContainerPtrToValuePtr<long>(pAssetField.Get()->FieldContainer);
				if (LongPtr != NULL)
				{
					pAssetField.Get()->FieldLongValue = *LongPtr;
				}
			}
		}
	}
}

void ZED_DataWidget::ExtractFStringValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FStrProperty* Property = CastField<FStrProperty>(pAssetField.Get()->FieldProperty);
	
	//Get the single property Widget

	if (Property->IsNative())
	{
		if (pAssetField.Get()->FieldType == "FString")
		{
			if (Property->IsValidLowLevel())
			{
				if (!isStrObj)
				{
					//Get the single property Widget
					pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());

					FString* StrPtr = Property->ContainerPtrToValuePtr<FString>(pAssetField.Get()->FieldOwner);
					if (StrPtr != NULL)
					{
						pAssetField.Get()->FieldStringValue = *StrPtr;
					}
				}
				else
				{
					//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
					pAssetField.Get()->IsCustom = true;

					//pAssetField.Get()->FieldStringValue = "Object Text";
					FString* StrPtr = Property->ContainerPtrToValuePtr<FString>(pAssetField.Get()->FieldContainer);
					if (StrPtr != NULL)
					{
						pAssetField.Get()->FieldStringValue = *StrPtr;
					}
				}
			}
			else
			{
				pAssetField.Get()->FieldStringValue = FString("Please! Initialize your " ) + pAssetField.Get()->FieldName + FString(" Attribute!");
			}
		}
	}
}

void ZED_DataWidget::ExtractFTextValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FStrProperty* Property = (FStrProperty*)pAssetField.Get()->FieldProperty;

	if (Property->IsNative())
	{
		if (pAssetField.Get()->FieldType == "FText")
		{
			if (!isStrObj)
			{
				//Get the single property Widget
				pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());

				FText* StrPtr = Property->ContainerPtrToValuePtr<FText>(pAssetField.Get()->FieldOwner);
				if (StrPtr != NULL)
				{
					pAssetField.Get()->FieldTextValue = *StrPtr;
				}

			}
			else
			{
				//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
				pAssetField.Get()->IsCustom = true;

				//pAssetField.Get()->FieldTextValue = FText().FromString(FString("Texto Objeto"));
				FText* StrPtr = Property->ContainerPtrToValuePtr<FText>(pAssetField.Get()->FieldContainer);
				if (StrPtr != NULL)
				{
					pAssetField.Get()->FieldTextValue = *StrPtr;
				}
			}
		}
	}
}

void ZED_DataWidget::ExtractBoolValue(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FBoolProperty* Property = (FBoolProperty*)pAssetField.Get()->FieldProperty;

	if (Property->IsNativeBool())
	{
		if (!isStrObj)
		{
			//Get the single property Widget
			pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());

			bool* BoolPtr = Property->ContainerPtrToValuePtr<bool>(pAssetField.Get()->FieldOwner);
			if (BoolPtr != NULL)
			{
				pAssetField.Get()->FieldBoolValue = *BoolPtr;
			}
		}
		else
		{
			//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
			pAssetField.Get()->IsCustom = true;

			//pAssetField.Get()->FieldTextValue = FText().FromString(FString("Texto Objeto"));
			bool* BoolPtr = Property->ContainerPtrToValuePtr<bool>(pAssetField.Get()->FieldContainer);
			if (BoolPtr != NULL)
			{
				pAssetField.Get()->FieldBoolValue = *BoolPtr;
			}
		}
	}
}

void ZED_DataWidget::ExtractEnumValues(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FEnumProperty* Property = (FEnumProperty*)pAssetField.Get()->FieldProperty;
	UEnum* EnumPtr = Property->GetEnum();

	if (!isStrObj)
	{
		//Get the single property Widget
		pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());
	}
	else
	{
		//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
		pAssetField.Get()->IsCustom = true;
	}

	for (int i = 0; i < EnumPtr->NumEnums() - 1; i++)
	{
		pAssetField.Get()->FieldEnumValues.Add(MakeShareable(new FString(EnumPtr->GetDisplayNameTextByIndex(i).ToString())));
	}
}

void ZED_DataWidget::ExtractObjectValues(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	FClassProperty* Property       = (FClassProperty*)pAssetField.Get()->FieldProperty;
	UClass        * PropertyClass  = (UClass        *)Property->GetOwnerClass();

	if (!isStrObj)
	{
		//Get the single property Widget
		pAssetField.Get()->FieldView = pWidgetBuilder.GetPropertyWidget(Property->GetOwnerUObject(), Property->GetFName());

		UObject* ObjPtr = Property->ContainerPtrToValuePtr<UObject>(pAssetField.Get()->FieldOwner);
		if (ObjPtr != NULL)
		{
			pAssetField.Get()->FieldObjectValue = ObjPtr;
		}
	}
	else
	{
		//Mark as Custom, to make possible we solve the structs pointer(Happening With Details Editor Too)
		pAssetField.Get()->IsCustom = true;

		//pAssetField.Get()->FieldTextValue = FText().FromString(FString("Texto Objeto"));
		UObject* ObjPtr = Property->ContainerPtrToValuePtr<UObject>(pAssetField.Get()->FieldContainer);
		if (ObjPtr != NULL)
		{
			pAssetField.Get()->FieldObjectValue = ObjPtr;
		}
	}
}


void ZED_DataWidget::ExtractStructValues(TSharedPtr<ZED_AssetField> pAssetField, bool isStrObj)
{
	//Initialize the struct field counter
	int Counter = 0;
	
	FStructProperty *Property       = CastField<FStructProperty>(pAssetField.Get()->FieldProperty);
	UScriptStruct   *PropertyStruct = Property->Struct;
	
	
	//WARNING! Only the structs Owned by the class must be sent (Check the Null Value!)
	void* FieldContainer = Cast<AZED_ConfigurationData>(Item)->GetStructContainer(Property->GetFName());
	if (!FieldContainer)
	{
		//If the Struct cannot be recovered means that structure was decleared in other object...
		return;
	}

	//Pass the entire struct structure to be used in Slate if necessary
	pAssetField.Get()->FieldScrStruct = PropertyStruct;

	FProperty* pRoot  = PropertyStruct->PropertyLink;
	FField*    pField = PropertyStruct->ChildProperties;

	while (pRoot != NULL)
	{

		FProperty* FieldProperty = CastField<FProperty>(pRoot);

		FString tName;

		FieldProperty->GetName(tName);

		FName tFname = FName(tName);
		
		UStruct   *FieldStruct      = Property->Struct;
		UObject   *FieldOwner       = PropertyStruct;
		
		//To mantain memory and Unreal´s Sanity...we use TSharedPtr here... Tadá! :)
		TSharedPtr<ZED_AssetField> tStructField = MakeShareable(new ZED_AssetField());

		ExtractFieldHeaders(tStructField, Counter, FieldProperty , FieldOwner , ItemStaticClass , FieldContainer);

		if (tStructField.Get()->IsEnum == true)
		{
			ExtractEnumValues(tStructField,true);
		}
		else if (tStructField.Get()->IsStruct == true)
		{
			ExtractStructValues(tStructField,true);
		}
		else if (tStructField.Get()->IsObject == true)
		{
			ExtractObjectValues(tStructField,true);
		}
		else if (tStructField.Get()->IsNative == true)
		{
			if (tStructField.Get()->IsNumber == true)
			{
				ExtractNumericValue(tStructField,true);
			}
			else if (tStructField.Get()->IsConditional == true)
			{
				ExtractBoolValue(tStructField,true);
			}
			else
			{
				ExtractAlphaNmValue(tStructField,true);
			}
		}
		else if (tStructField.Get()->IsNative == false)
		{
			if (tStructField.Get()->IsNumber == true)
			{
				ExtractNumericValue(tStructField,true);
			}
			else if (tStructField.Get()->IsConditional == true)
			{
				ExtractBoolValue(tStructField,true);
			}
			else
			{
				ExtractAlphaNmValue(tStructField,true);
			}
		}

		pAssetField.Get()->FieldStructValues.Add(tStructField);
		Counter++;
		pRoot = pRoot->PropertyLinkNext;
	}
}

/**
This will be an important method to stablish a good design in the future implementations since this class will be
"the core ZED" class for the fields in a Tool Screen!
The main idea is use Object Factory with a GridWidGet for any tool being Developed, so... we will develop this once and
all developers can use it anywhere anytime... ;)
*/
TSharedRef<ITableRow> ZED_DataWidget::OnGenerateRowForList(TSharedPtr<ZED_AssetField> ItemRow, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(ZED_ListRow, OwnerTable).Item(ItemRow);
}

/**
This will be an important method to stablish a good design in the future implementations since this class will be
"the core ZED" class for the fields in a Tool Screen!
The main idea is use Object Factory with a GridWidGet for any tool being Developed, so... we will develop this once and
all developers can use it anywhere anytime... ;)
*/
void ZED_DataWidget::OnGetChildrenForList(TSharedPtr<ZED_AssetField> ItemChildren, TArray< TSharedPtr<ZED_AssetField> >& OutChildren)
{
	if (ItemChildren.IsValid())
	{
		if (ItemChildren.Get()->IsStruct)
		{
			for (int i = 0; i < ItemChildren.Get()->FieldStructValues.Num(); i++)
			{
				OutChildren.Add(ItemChildren.Get()->FieldStructValues[i]);
			}
		}
	}
}