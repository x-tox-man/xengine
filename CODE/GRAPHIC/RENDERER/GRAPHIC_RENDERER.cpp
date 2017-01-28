//
//  GRAPHIC_RENDERER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_RENDERER.h"

GRAPHIC_RENDERER::GRAPHIC_RENDERER():
    Camera( NULL ),
    ShadowMapCamera( NULL ),
    PassIndex( 0 ),
    DepthTexture( NULL ) {
    
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
