//
//  UI_ENDGAME.cpp
//  Run3d
//
//  Created by Christophe Bernard on 28/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_ENDGAME.h"
#include "UI_ENDGAME_PRESENTER.h"
#include "GRAPHIC_UI_HELPER.h"
#include "RUN3D_APPLICATION.h"

UI_ENDGAME::UI_ENDGAME() :
    R3D_UI_FRAME() {
    
    SetPresenter( new UI_ENDGAME_PRESENTER( this ) );
}

UI_ENDGAME::~UI_ENDGAME() {
    
}

void UI_ENDGAME::Initialize() {
    
    R3D_APP_PTR->GetApplicationWindow().EnableBackgroundContext( true );
    
    auto proceed_button = new UI_BASE_BUTTON;
    proceed_button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomRight );
    proceed_button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    proceed_button->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, 16.0f ) );
    proceed_button->Initialize();
    
    auto end_text = GRAPHIC_UI_HELPER::CreateTextElement( CORE_HELPERS_IDENTIFIER( "end" ), L"End Game" );
    end_text->GetPlacement().SetAnchor( GRAPHIC_UI_Center );
    end_text->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( .0f, -16.0f ) );
    end_text->Initialize();
    end_text->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    
    Presenter->BindAction<UI_ENDGAME_PRESENTER, &UI_ENDGAME_PRESENTER::OnProceedButtonPressed >( proceed_button, (UI_ENDGAME_PRESENTER*) Presenter);
    
    const wchar_t * duration = L"NULL";
    
    auto text = GRAPHIC_UI_HELPER::CreateTextElement( CORE_HELPERS_IDENTIFIER( "Texttest" ), duration );
    text->Initialize();
    text->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( CORE_COLOR_White );
    
    AddObject( text );
    AddObject( end_text );
    AddObject( proceed_button );
    
    R3D_UI_FRAME::Initialize();
    R3D_APP_PTR->GetApplicationWindow().EnableBackgroundContext( false );
}
