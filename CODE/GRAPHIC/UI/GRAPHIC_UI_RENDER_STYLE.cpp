//
//  GRAPHIC_UI_RENDER_STYLE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_RENDER_STYLE.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER_ATTRIBUTE.h"
#include "GRAPHIC_OBJECT_RENDER_OPTIONS.h"

GRAPHIC_UI_RENDER_STYLE::GRAPHIC_UI_RENDER_STYLE() :
    Effect( NULL ),
    DecoratingEffect( NULL ),
    Shape( NULL ),
    DecoratingShape( NULL ),
    Material( NULL ),
    DecoratingMaterial( NULL ) {
    
}

GRAPHIC_UI_RENDER_STYLE::GRAPHIC_UI_RENDER_STYLE( GRAPHIC_OBJECT_SHAPE * shape, GRAPHIC_SHADER_EFFECT * effect, const CORE_HELPERS_COLOR & color, GRAPHIC_OBJECT_SHAPE * decorating_shape, GRAPHIC_SHADER_EFFECT * decorating_effect ) :
    Effect( effect ),
    DecoratingEffect( decorating_effect ),
    Shape( shape ),
    DecoratingShape( decorating_shape ) {

}

GRAPHIC_UI_RENDER_STYLE::~GRAPHIC_UI_RENDER_STYLE() {

}

void GRAPHIC_UI_RENDER_STYLE::Apply( GRAPHIC_RENDERER & renderer, const GRAPHIC_UI_PLACEMENT & placement, float opacity ) {
    
    GRAPHIC_OBJECT_RENDER_OPTIONS
        option;
    
    renderer.EnableColor( true );
    
    if ( Shape && Effect ) {
        
        option.SetPosition( placement.GetAbsolutePosition() );
        option.SetScaleFactor( placement.GetSize() );
        
        CORE_MATH_QUATERNION orientation;
        orientation.RotateY( placement.GetRotation() );
        orientation.Normalize();
        
        option.SetOrientation( orientation );
        
        Material->GetDiffuse().W( opacity );
        Effect->SetMaterial( Material );
        
        Shape->Render( renderer, option, Effect );
    }
    
    if ( DecoratingShape && DecoratingEffect) {
        
        option.SetPosition( placement.GetAbsolutePosition() );
        option.SetScaleFactor( placement.GetSize() );
        
        DecoratingMaterial->GetDiffuse().W( opacity );
        DecoratingEffect->SetMaterial( DecoratingMaterial );
        
        DecoratingShape->Render( renderer, option, DecoratingEffect );
    }
    
    renderer.EnableColor( false );
}
