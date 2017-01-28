//
//  GRAPHIC_SHADER_OPENGL.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#if OPENGL2PLUS

        Scalar_SGet( GLuint, Program );

    private :

        bool CompileShader( GLuint & shader, GLenum type,  const CORE_FILESYSTEM_PATH & path );

    GLuint
        Shader;
#endif
