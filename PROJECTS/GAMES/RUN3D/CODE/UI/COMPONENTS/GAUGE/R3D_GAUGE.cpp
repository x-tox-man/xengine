//
//  R3D_GAUGE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 5/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "R3D_GAUGE.h"
#include "GRAPHIC_UI_HELPER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "R3D_GAUGE_ANIMATION.h"

R3D_GAUGE::R3D_GAUGE() :
    GRAPHIC_UI_FRAME(),
    Percent( 0.0f ) {
    
}

void R3D_GAUGE::Initialize() {
    
    GetPlacement().SetSize( CORE_MATH_VECTOR( 256.0f, 1.0f) );
    
    static CORE_HELPERS_UNIQUE_IDENTIFIER
        texture_identifier( "frame_gauge" );
    
    GRAPHIC_TEXTURE::LoadResourceForPath( texture_identifier, CORE_FILESYSTEM_PATH::FindFilePath( "frame_gauge", "png", "TEXTURES" ) );
    
    GRAPHIC_UI_HELPER::CreateFrameStyleWithBorderAndContentColor(this, CORE_HELPERS_COLOR( 0.5f, 0.5f, 0.5f, 0.5f ), "frame_gauge" );
    
    auto element = GRAPHIC_UI_HELPER::CreateElement( Gauge );
    element->GetPlacement().SetAnchor( GRAPHIC_UI_Left );
    
    GRAPHIC_UI_HELPER::CreateElementStyleWithContentColor(element, CORE_COLOR_Cyan );
    element->Initialize();
    
    AddObject( element );
    
    GRAPHIC_UI_FRAME::Initialize();
    
    SetPercent( Percent );
}

void R3D_GAUGE::SetPercent( float percent ) {
    Percent = percent;
    
    if( Percent < 0.0f )
        Percent = .0f;
    
    if( Percent > 1.0f )
        Percent = 1.0f;
    
    GetObjectForIdentifier( Gauge )->GetPlacement().SetSize( CORE_MATH_VECTOR( 256.0f * Percent, 4.0f ) );
}

void R3D_GAUGE::SetColor( const CORE_HELPERS_COLOR & color ) {
    
    GetObjectForIdentifier( Gauge )->GetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default )->GetMaterial()->SetDiffuse( color );
}

void R3D_GAUGE::SetPercentAnimated( float percent ) {
    
    GRAPHIC_UI_ELEMENT::PTR
        element = GetObjectForIdentifier( Gauge );
    std::function<void (GRAPHIC_UI_ELEMENT *, std::vector< GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA > &, float)>
        update = R3D_GAUGE_ANIMATION_UpdateSize;
    GRAPHIC_UI_ANIMATION
        animation( element, update, 3.0f );
    GRAPHIC_UI_ANIMATION_INTERPOLATION_DATA
        data;
    CORE_MATH_VECTOR
        c( 256.0f * percent, 4.0f );
    
    Percent = percent;
    
    data.From.FloatArray4[0] = element->GetSize()[0];
    data.From.FloatArray4[1] = element->GetSize()[1];
    
    data.To.FloatArray4[0] = c[0];
    data.To.FloatArray4[1] = c[1];
    
    animation.GetInterpolationData().push_back( data );
    
    GetObjectForIdentifier( Gauge )->GetAnimation() = animation;
}

void R3D_GAUGE::SetColorAnimated( const CORE_HELPERS_COLOR & color ) {
    
}

CORE_HELPERS_IDENTIFIER
    R3D_GAUGE::Gauge( "Gauge" );
