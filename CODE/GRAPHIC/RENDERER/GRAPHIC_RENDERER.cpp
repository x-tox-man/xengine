//
//  GRAPHIC_RENDERER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT.h"

GRAPHIC_RENDERER::GRAPHIC_RENDERER():
    Camera( NULL ),
    ShadowMapCameraTable(),
    RenderCallback(),
    DirectionalLight( NULL ),
    AmbientLight( NULL ),
    PointLightTable(),
    SpotLightTable(),
    PassIndex( 0 ),
    NumCascade( 3 ),
    DepthTextureTable(),
    ScissorRectangle(),
    ScissorIsEnabled( false ),
    ColorEnabled( false ),
    LightingIsEnabled( true ) {
    
    PointLightTable[0] = NULL;
    PointLightTable[1] = NULL;
    PointLightTable[2] = NULL;
    PointLightTable[3] = NULL;
    
    SpotLightTable[0] = NULL;
    SpotLightTable[1] = NULL;
    SpotLightTable[2] = NULL;
    SpotLightTable[3] = NULL;
}

GRAPHIC_RENDERER::~GRAPHIC_RENDERER() {

}

void GRAPHIC_RENDERER::EnableScissor( bool enable ) {
    
    ScissorIsEnabled = enable;
    GRAPHIC_SYSTEM::EnableScissor( enable );
}

void GRAPHIC_RENDERER::Resize(int width, int height) {
    
    ResizeViewCallback( width, height );
}

void GRAPHIC_RENDERER::ResetDepth() {
    
}

const CORE_HELPERS_IDENTIFIER & GRAPHIC_RENDERER::GetShadowMapMVPName( int cascade_index ) {
    
    switch (cascade_index) {
        case 0:
            
            return GRAPHIC_SHADER_PROGRAM::ShadowMapMVP1;
            break;
        case 1:
            
            return GRAPHIC_SHADER_PROGRAM::ShadowMapMVP2;
            break;
        case 2:
            
            return GRAPHIC_SHADER_PROGRAM::ShadowMapMVP3;
            break;
        case 3:
            
            return GRAPHIC_SHADER_PROGRAM::ShadowMapMVP4;
            break;
        case 4:
            
            return GRAPHIC_SHADER_PROGRAM::ShadowMapMVP5;
            break;
            
        default:
            break;
    }
    
    return GRAPHIC_SHADER_PROGRAM::ShadowMapMVP1;
}
