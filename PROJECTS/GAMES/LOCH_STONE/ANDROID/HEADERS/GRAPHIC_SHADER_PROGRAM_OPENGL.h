//
//  GRAPHIC_SHADER_PROGRAM_OPENGL.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM_OPENGL__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM_OPENGL__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER_OPENGL.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_BIND.h"

#if OPENGL2PLUS
    XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_PROGRAM_OPENGL, GRAPHIC_SHADER_PROGRAM )

        GRAPHIC_SHADER_PROGRAM_OPENGL();

        virtual void Initialize();
        virtual void LoadProgram( const char * path );
        virtual void LoadPartial( const char * path, GRAPHIC_SHADER_TYPE shader_type );
        virtual void Finalize();

        virtual void Enable();
        virtual void Disable();

        void LinkTogether( const GRAPHIC_SHADER_BIND shader_bind );

        void BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, CORE_HELPERS_IDENTIFIER & identifier );

    private :

        bool ValidateProgram();
        bool LinkProgram();

        GLuint ShaderProgram;
        GRAPHIC_SHADER_BIND BoundParameters;

    public :

    static const CORE_HELPERS_IDENTIFIER
        ProjectionMatrix,
        modelViewMatrix,
        normalMatrix,
        texture,
        skinningMatrixTable,
        attrBindShapMatrix,
        geometryColor;

    XS_CLASS_END
#endif

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM_OPENGL__) */
