//
//  GRAPHIC_SHADER_PROGRAM.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_TYPE.h"
#include "GRAPHIC_SHADER.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_BIND.h"

XS_CLASS_BEGIN( GRAPHIC_SHADER_PROGRAM )

    GRAPHIC_SHADER_PROGRAM();

    void Initialize();
    void LoadProgram( const CORE_FILESYSTEM_PATH & path );
    void LoadPartial( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type );
    void Finalize();

    void Enable();
    void Disable();

    GRAPHIC_SHADER_ATTRIBUTE & getShaderAttribute( const CORE_HELPERS_IDENTIFIER & identifier ) { return ShaderAttributeTable[identifier]; }

    void setShaderAttribute( const GRAPHIC_SHADER_ATTRIBUTE & attribute ) {

        ShaderAttributeTable[attribute.AttributeName].AttributeIndex = attribute.AttributeIndex;
        ShaderAttributeTable[attribute.AttributeName].AttributeName = attribute.AttributeName;
        ShaderAttributeTable[attribute.AttributeName].AttributeValue = attribute.AttributeValue;
    }

protected:

    std::map<GRAPHIC_SHADER_TYPE, GRAPHIC_SHADER *>
        ShaderTable;
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_SHADER_ATTRIBUTE>
        ShaderAttributeTable;

public:

static const CORE_HELPERS_IDENTIFIER
    ProjectionMatrix,
    modelViewMatrix,
    normalMatrix,
    texture,
    skinningMatrixTable,
    attrBindShapMatrix,
    geometryColor;

#if OPENGLES2
    #include "GRAPHIC_SHADER_PROGRAM_OPENGLES2.hpp"
#elif OPENGL3
    #include "GRAPHIC_SHADER_PROGRAM_OPENGL.hpp"
#else
    #error "Must include file to match graphic runtime"
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM__) */
