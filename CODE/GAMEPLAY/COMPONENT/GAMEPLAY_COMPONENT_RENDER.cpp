//
//  GAMEPLAY_COMPONENT_RENDER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "CORE_MEMORY.h"
#include "GAMEPLAY_COMPONENT.h"
#include "CORE_DATA_STREAM.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_OBJECT.h"

GAMEPLAY_COMPONENT_RENDER::GAMEPLAY_COMPONENT_RENDER() :
    GAMEPLAY_COMPONENT( sizeof( GAMEPLAY_COMPONENT_RENDER ) ),
    ObjectProxy(),
    EffectProxy(),
    MaterialProxy(),
    ShadowmapEffectProxy(),
    AABBNode( 0.1f ),
    ScaleFactor( 1.0f ) {
    
}

GAMEPLAY_COMPONENT_RENDER::GAMEPLAY_COMPONENT_RENDER( const GAMEPLAY_COMPONENT_RENDER & other ) :
    GAMEPLAY_COMPONENT( sizeof( GAMEPLAY_COMPONENT_RENDER ) ),
    ObjectProxy( other.ObjectProxy ),
    EffectProxy( other.EffectProxy ),
    MaterialProxy( other.MaterialProxy ),
    ShadowmapEffectProxy( other.ShadowmapEffectProxy ),
    AABBNode( other.AABBNode ),
    ScaleFactor( other.ScaleFactor ) {
    
}

GAMEPLAY_COMPONENT_RENDER::~GAMEPLAY_COMPONENT_RENDER() {

}

void GAMEPLAY_COMPONENT_RENDER::Render( GRAPHIC_RENDERER & renderer, GAMEPLAY_COMPONENT_POSITION * component, GAMEPLAY_COMPONENT_POSITION * parent ) {
    
    GRAPHIC_OBJECT
        * object = ObjectProxy.GetResource< GRAPHIC_OBJECT >();
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options,
        parent_options;
    GRAPHIC_SHADER_EFFECT
        * effect = EffectProxy.GetResource< GRAPHIC_SHADER_EFFECT >();
    
    options.SetPosition( component->GetPosition() + component->GetPositionOffset() );
    options.SetOrientation(component->GetOrientation() );
    options.SetScaleFactor( CORE_MATH_VECTOR(ScaleFactor, ScaleFactor,ScaleFactor, 1.0f) );
    
    if ( parent != NULL ) {
        
        parent_options.SetPosition( parent->GetPosition() + parent->GetPositionOffset() );
        parent_options.SetOrientation(parent->GetOrientation() );
        parent_options.SetScaleFactor( CORE_MATH_VECTOR(ScaleFactor, ScaleFactor,ScaleFactor, 1.0f) );
        
        options.SetParent( &parent_options );
    }

    if ( renderer.GetPassIndex() == 0 ) {
        
        effect->SetMaterial( MaterialProxy.GetResource< GRAPHIC_MATERIAL >() );
        object->Render( renderer, options, effect );
    }
    else if ( renderer.GetPassIndex() == 1 ) {
        
        auto shadow_effect = ShadowmapEffectProxy.GetResource< GRAPHIC_SHADER_EFFECT >();
        options.SetTexturing( false );
        
        if ( shadow_effect ) {
            object->Render( renderer, options, shadow_effect );
        }
    }
}

void GAMEPLAY_COMPONENT_RENDER::ComputeSize( CORE_MATH_SHAPE & shape ) {
    
    GRAPHIC_OBJECT
        * object = ObjectProxy.GetResource< GRAPHIC_OBJECT >();
    
    object->ComputeAABBox( shape );
}
