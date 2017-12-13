//
//  UI_MAIN_MENU.cpp
//  Run3d
//
//  Created by Christophe Bernard on 19/09/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_MAIN_MENU.h"
#include "UI_MAIN_MENU_PRESENTER.h"
#include "GRAPHIC_UI_HELPER.h"

UI_MAIN_MENU::UI_MAIN_MENU() :
    R3D_UI_FRAME() {
    
    SetPresenter( new UI_MAIN_MENU_PRESENTER( this ) );
}

void UI_MAIN_MENU::Initialize() {
    
    auto button = new UI_BASE_BUTTON;
    button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomRight );
    button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    button->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( -16.0f, 16.0f ) );
    
    Presenter->BindAction<UI_MAIN_MENU_PRESENTER, &UI_MAIN_MENU_PRESENTER::OnClick>(button, (UI_MAIN_MENU_PRESENTER*) Presenter);
    
    auto network_button = new UI_BASE_BUTTON;
    network_button->GetPlacement().SetAnchor( GRAPHIC_UI_Center );
    network_button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    network_button->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, 16.0f ) );
    
    Presenter->BindAction<UI_MAIN_MENU_PRESENTER, &UI_MAIN_MENU_PRESENTER::OnNetworkButtonPressed>(network_button, (UI_MAIN_MENU_PRESENTER*) Presenter);
    
    AddObject( button );
    AddObject( network_button );
    
    R3D_UI_FRAME::Initialize();
}
