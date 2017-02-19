//
//  APPLICATION_LOADER_SCREEN.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_LOADER_SCREEN.h"
#include "Application.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "APPLICATION_GAME_HUD.h"

APPLICATION_LOADER_SCREEN::APPLICATION_LOADER_SCREEN() :
    GRAPHIC_UI_FRAME(),
    Percentage( 0.0f ),
    DefaultRenderStyle() {
    
}

APPLICATION_LOADER_SCREEN::~APPLICATION_LOADER_SCREEN() {
    
    CORE_MEMORY_ObjectSafeDeallocation( ProgressBar );
    CORE_MEMORY_ObjectSafeDeallocation( DefaultRenderStyle );
}

void APPLICATION_LOADER_SCREEN::Initialize() {
    
    Percentage = 0.0f;
    
    DefaultRenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    
    DefaultRenderStyle->SetColor( CORE_MATH_VECTOR( 1.0f, 0.0f, 1.0f, 1.0f ) );
    DefaultRenderStyle->SetShape( GLOBAL_RESOURCES::GetInstance().UIPlanObject );
    DefaultRenderStyle->SetTextureBlock( &GLOBAL_RESOURCES::GetInstance().UITextureAtlas.GetTextureBlock( CORE_HELPERS_UNIQUE_IDENTIFIER( "Create_Server_button" ) ) );
    
    ProgressBar = new GRAPHIC_UI_FRAME();
    ProgressBar->GetPlacement().SetAnchor(GRAPHIC_UI_Left);
    ProgressBar->GetPlacement().SetSize( CORE_MATH_VECTOR(0.0f, 32.0f) );
    ProgressBar->SetPosition( CORE_MATH_VECTOR(0.0f, 0.0f) );
    ProgressBar->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, GLOBAL_RESOURCES::GetInstance().FrameRenderStyle );
    {
        auto object_bar = new GRAPHIC_UI_ELEMENT();
        object_bar->GetPlacement().SetAnchor(GRAPHIC_UI_Center);
        object_bar->SetPosition( CORE_MATH_VECTOR(25.0f, -25.0f) );
        object_bar->Initialize();
        object_bar->GetPlacement().SetSize( CORE_MATH_VECTOR(128.0f, 32.0f) );
        object_bar->SetRenderStyleForState(GRAPHIC_UI_ELEMENT_STATE_Default, DefaultRenderStyle );
        
        ProgressBar->AddObject( object_bar );
    }
    
    AddObject(ProgressBar);
}

void APPLICATION_LOADER_SCREEN::Update( const float time_step ) {
    
    if ( Percentage > 1.0f) {
        
        if (((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->IsMultiplayer() ) {
            
            APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_GAME_HUD>( "MultiplayerHUD" );
        }
        else {
            
            APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_GAME_HUD>( "SinglePlayerHUD" );
        }
    }
    else {
        Percentage += time_step * 0.1f;
        
        ProgressBar->GetPlacement().SetSize( CORE_MATH_VECTOR(128.0f * Percentage, 32.0f) );
    }
}
