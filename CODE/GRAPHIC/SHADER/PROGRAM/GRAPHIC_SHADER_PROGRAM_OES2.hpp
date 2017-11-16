//
//  GRAPHIC_SHADER_PROGRAM_OPENGLES2.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#if OPENGLES2

    void LinkTogether( const GRAPHIC_SHADER_BIND shader_bind );

    inline GLuint GetShaderProgram() { return ShaderProgram; }

    void BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, CORE_HELPERS_IDENTIFIER & identifier );

    private :

    bool ValidateProgram();
    bool LinkProgram();

    GLuint ShaderProgram;
    GRAPHIC_SHADER_BIND BoundParameters;

#endif
