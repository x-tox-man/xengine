//
//  GRAPHIC_RENDERER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER.h"

GRAPHIC_RENDERER::GRAPHIC_RENDERER():
    Camera( NULL ),
    ShadowMapCamera( NULL ),
    RenderCallback(),
    DirectionalLight( NULL ),
    AmbientLight( NULL ),
    PointLightTable(),
    SpotLightTable(),
    PassIndex( 0 ),
    DepthTexture( NULL ),
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
