//
//  GRAPHIC_SHADER_PROGRAM_OPENGL.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM_OPENGL__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM_OPENGL__

    #if OPENGL2PLUS

        void LinkTogether( const GRAPHIC_SHADER_BIND shader_bind );

        void BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, CORE_HELPERS_IDENTIFIER & identifier );

        private :

        bool ValidateProgram();
        bool LinkProgram();

        GLuint ShaderProgram;
        GRAPHIC_SHADER_BIND BoundParameters;

    #endif

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM_OPENGL__) */
