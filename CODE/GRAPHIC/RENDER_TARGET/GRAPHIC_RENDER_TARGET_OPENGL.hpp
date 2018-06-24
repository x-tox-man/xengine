//
//  GRAPHIC_RENDER_TARGET_OPENGL.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/09/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_GRAPHIC_RENDER_TARGET_OPENGL_h
#define GAME_ENGINE_REBORN_GRAPHIC_RENDER_TARGET_OPENGL_h

int
    Attachments;
GLuint
    FrameBuffer,
    DepthrenderBuffer;
GLenum
    DrawBuffers[8];

#endif
