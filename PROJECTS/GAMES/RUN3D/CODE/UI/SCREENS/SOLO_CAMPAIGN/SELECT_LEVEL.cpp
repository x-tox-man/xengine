//
//  SELECT_LEVEL.cpp
//  Run3d
//
//  Created by Christophe Bernard on 30/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "SELECT_LEVEL.h"
#include "SELECT_LEVEL_PRESENTER.h"
#include "GRAPHIC_UI_HELPER.h"
#include "TOOLS_LOCALE_SYSTEM.h"

SELECT_LEVEL::SELECT_LEVEL() :
    R3D_UI_FRAME() {

}

void SELECT_LEVEL::Initialize() {
    
    auto level_frame = GRAPHIC_UI_HELPER::CreateFrame( "LevelsContainer" );
    
    auto presenter_adapter = new SELECT_LEVEL_PRESENTER( level_frame );
    
    GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "Level1_picto" ), CORE_FILESYSTEM_PATH::FindFilePath( "Level1_picto", "png", "TEXTURES" ) );
    
    SetPresenter( presenter_adapter );
    
    level_frame->GetPlacement().SetSize(CORE_MATH_VECTOR( 768.0f, 256.0f ) );
    level_frame->SetAdapter( presenter_adapter );
    level_frame->Initialize();
    
    auto back_button = new UI_BASE_BUTTON;
    back_button->GetPlacement().SetAnchor( GRAPHIC_UI_BottomLeft );
    back_button->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 32.0f ) );
    back_button->GetPlacement().SetRelativePosition(CORE_MATH_VECTOR( 16.0f, 16.0f ) );
    back_button->SetTitle( TOOLS_LOCALE_SYSTEM::GetInstance().FindTranslation( CORE_HELPERS_UNIQUE_IDENTIFIER( "Back" ) ) );
    back_button->Initialize();
    
    Presenter->BindAction<SELECT_LEVEL_PRESENTER, &SELECT_LEVEL_PRESENTER::OnBackButtonClicked>( back_button, (SELECT_LEVEL_PRESENTER*) Presenter);
    
    AddObject( level_frame );
    AddObject( back_button );
    
    R3D_UI_FRAME::Initialize();
    
    OnPlacementPropertyChanged();
}
