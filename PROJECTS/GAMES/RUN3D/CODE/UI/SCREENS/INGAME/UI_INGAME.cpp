//
//  UI_INGAME.cpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_INGAME.h"
#include "UI_INGAME_PRESENTER.h"
#include "GRAPHIC_UI_HELPER.h"
#include "RUN3D_APPLICATION.h"

UI_INGAME::UI_INGAME() :
    R3D_UI_FRAME() {
    
    SetPresenter( new UI_INGAME_PRESENTER( this ) );
}

UI_INGAME::~UI_INGAME() {
    
}

void UI_INGAME::Initialize() {
    
    R3D_APP_PTR->GetApplicationWindow().EnableBackgroundContext( true );
    R3D_UI_FRAME::SetBorderLess();
    
    auto pause_button = new UI_BASE_BUTTON;
    pause_button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomRight );
    pause_button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    pause_button->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, .0f ) );
    pause_button->Initialize();
    
    Presenter->BindAction<UI_INGAME_PRESENTER, &UI_INGAME_PRESENTER::OnPauseButtonPressed >( pause_button, (UI_INGAME_PRESENTER*) Presenter);
    
    AddObject( pause_button );
    
    R3D_UI_FRAME::Initialize();
    R3D_APP_PTR->GetApplicationWindow().EnableBackgroundContext( false );
}
