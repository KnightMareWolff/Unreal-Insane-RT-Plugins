// Fill out your copyright notice in the Description page of Project Settings.


#include "ZED_Subsystem.h"
#include "ZED_WidgetBuilder.h"

bool UZED_Subsystem::IsSimulationRunning=false;

void UZED_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    IsSimulationRunning = true;
    
    TSharedPtr<SDockTab> tab = FGlobalTabmanager::Get()->InvokeTab(FName("ZED_ConfigTab"));
    tab->RequestCloseTab();
    
    //FZED_WidgetBuilder::pWidgetView->SetDisableCustomDetailLayouts(true);
    //FZED_WidgetBuilder::pWidgetView->SetEnabled(false);
    //FZED_WidgetBuilder::pWidgetView->SetVisibility(EVisibility::Collapsed);

}

void UZED_Subsystem::Deinitialize()
{
    IsSimulationRunning = false;
    
    //FZED_WidgetBuilder::pWidgetView->SetDisableCustomDetailLayouts(false);
    //FZED_WidgetBuilder::pWidgetView->SetEnabled(true);
    //FZED_WidgetBuilder::pWidgetView->SetVisibility(EVisibility::Visible);
}