//
//  OPENGL_2_SHADER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#if OPENGLES2

    Scalar_SGet( GLuint, Program );

    private :

    bool CompileShader( GLuint & shader, GLenum type,  const CORE_FILESYSTEM_PATH & path );

    GLuint
        Shader;
#endif
