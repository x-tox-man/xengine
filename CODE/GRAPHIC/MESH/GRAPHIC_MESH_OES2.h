//
//  GRAPHIC_MESH_OPENGL2.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 18/07/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

public :

inline GLuint & GetVertexBuffer() { return VertexBuffer; }
inline GLuint & GetIndexBuffer() { return IndexBuffer; }

private :

GLuint
    VertexBuffer,
    IndexBuffer;

GLuint *
    VertexArrays;
