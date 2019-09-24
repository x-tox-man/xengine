//
//  GRAPHIC_SHADER_METAL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/08/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_METAL.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "GRAPHIC_SHADER.h"
#include "GRAPHIC_SYSTEM.h"

void GRAPHIC_SHADER::LoadShader( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type ) {
    
    switch ( shader_type ) {
        case GRAPHIC_SHADER_TYPE::GRAPHIC_SHADER_Vertex:
            
            vertexFunction = GRAPHIC_SYSTEM::CreateMetalFunction( "vertexShader" );
            break;
            
        case GRAPHIC_SHADER_TYPE::GRAPHIC_SHADER_Pixel:
            fragmentFunction = GRAPHIC_SYSTEM::CreateMetalFunction( "fragmentShader" );
            break;
            
        default:
            CORE_RUNTIME_Abort()
            break;
    }
}
