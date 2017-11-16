//
//  APPLICATION_GAME_HUD.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 29/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_GAME_HUD.h"
#include "APPLICATION_MULTIPLAYER_HUD_PRESENTER.h"
#include "APPLICATION_SINGLEPLAYER_HUD_PRESENTER.h"
#include "Application.h"

APPLICATION_GAME_HUD::APPLICATION_GAME_HUD() :
    GRAPHIC_UI_FRAME(),
    Presenter( NULL) {
    
}

APPLICATION_GAME_HUD::~APPLICATION_GAME_HUD() {
    
    CORE_MEMORY_ObjectSafeDeallocation( Presenter );
}

void APPLICATION_GAME_HUD::Initialize() {
    
    auto first_item = new GRAPHIC_UI_FRAME();
    first_item->GetPlacement().SetAnchor(GRAPHIC_UI_Left);
    first_item->GetPlacement().SetSize( CORE_MATH_VECTOR(512.0f, 256.0f) );
    first_item->SetPosition( CORE_MATH_VECTOR(0.0f, 0.0f) );
    first_item->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().FrameRenderStyle );
    
    AddObject(first_item);

    
    if (((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->IsMultiplayer() ) {
        
        Presenter = new APPLICATION_MULTIPLAYER_HUD_PRESENTER;
    }
    else {
        
        Presenter = new APPLICATION_SINGLEPLAYER_HUD_PRESENTER;
    }
}
