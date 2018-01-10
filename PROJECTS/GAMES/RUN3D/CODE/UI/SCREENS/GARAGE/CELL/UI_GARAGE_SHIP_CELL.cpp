//
//  UI_GARAGE_SHIP_CELL.cpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_GARAGE_SHIP_CELL.h"
#include "R3D_RESOURCES.h"
#include "GRAPHIC_UI_HELPER.h"

UI_GARAGE_SHIP_CELL::UI_GARAGE_SHIP_CELL() :
    GRAPHIC_UI_FRAME(),
    Camera(),
    Accumulated( 0.0f ),
    ShipModel( NULL ) {
        
    CORE_MATH_QUATERNION q;
        
    Camera.Reset(1.0f, 100.0f, 1024.0f, 768.0f, CORE_MATH_VECTOR(0.0f, -2.0f, 0.0f, 0.0f ), q );
}

UI_GARAGE_SHIP_CELL::~UI_GARAGE_SHIP_CELL() {
    
}

void UI_GARAGE_SHIP_CELL::Initialize() {
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext( true );
    Accumulated = (rand() % 100) * 0.01f * M_PI_2;
    
    GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 128.0f ) );
    
    GRAPHIC_UI_RENDER_STYLE *style = new GRAPHIC_UI_RENDER_STYLE;
    auto r = R3D_RESOURCES::GetInstance().FindResourceProxy( CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship" ) );
    auto e = R3D_RESOURCES::GetInstance().FindResourceProxy( "shader" );
    auto m = new GRAPHIC_MATERIAL;
    
    style->SetShape( (GRAPHIC_OBJECT_SHAPE::PTR) r->GetResource< GRAPHIC_OBJECT >() );
    style->SetEffect( e->GetResource< GRAPHIC_SHADER_EFFECT >() );
    style->SetMaterial( m );
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship1_diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    m->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( text ) );
    
    auto element = GRAPHIC_UI_HELPER::CreateElement( "ship" );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, style );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, style );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, style );
    element->GetPlacement().SetSize( CORE_MATH_VECTOR( 128.0f, 128.0f ) );
    element->Initialize();
    AddObject( element );
    
    CORE_HELPERS_UNIQUE_IDENTIFIER
        texture_identifier( "frameBorder3" );
    
    GRAPHIC_TEXTURE::LoadResourceForPath( texture_identifier, CORE_FILESYSTEM_PATH::FindFilePath( "frameBorder3", "png", "TEXTURES" ) );
    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.5f, 0.5f, 0.5f, 0.5f ), "frameBorder3" );
    
    GRAPHIC_UI_FRAME::Initialize();
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext( false );
}

void UI_GARAGE_SHIP_CELL::Update(const float time_step ) {
    
    GRAPHIC_UI_FRAME::Update( time_step );
    
    Accumulated += time_step;
    GetObjectAtIndex( 0 )->GetPlacement().SetRotation( Accumulated );
}

void UI_GARAGE_SHIP_CELL::Render( GRAPHIC_RENDERER & renderer ) {
    
    //GRAPHIC_CAMERA * camera = renderer.GetCamera();
    
    GRAPHIC_UI_FRAME::Render( renderer );
}

GRAPHIC_UI_ELEMENT * UI_GARAGE_SHIP_CELL::Copy() {
    
    return new UI_GARAGE_SHIP_CELL();
}
