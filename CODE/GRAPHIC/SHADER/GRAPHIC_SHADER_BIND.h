//
//  GRAPHIC_SHADER_BIND.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_GRAPHIC_SHADER_BIND_h
#define GAME_ENGINE_REBORN_GRAPHIC_SHADER_BIND_h

#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"

enum GRAPHIC_SHADER_BIND
{
    GRAPHIC_SHADER_BIND_None =          0,
    GRAPHIC_SHADER_BIND_Position =      1,
    GRAPHIC_SHADER_BIND_Normal =        2,
    GRAPHIC_SHADER_BIND_Color =         4,
    GRAPHIC_SHADER_BIND_Texcoord0 =     8,
    GRAPHIC_SHADER_BIND_Texcoord1 =     16,
    GRAPHIC_SHADER_BIND_SkinWeight =    32,
    GRAPHIC_SHADER_BIND_JointIndices =  64,
    GRAPHIC_SHADER_BIND_Tangents =      128,
    GRAPHIC_SHADER_BIND_Bitangents =    256,
    GRAPHIC_SHADER_BIND_CustomFloat =    512,
};

extern GRAPHIC_SHADER_BIND GRAPHIC_SHADER_BIND_PositionNormal;
extern GRAPHIC_SHADER_BIND GRAPHIC_SHADER_BIND_PositionNormalCustom;
extern GRAPHIC_SHADER_BIND GRAPHIC_SHADER_BIND_PositionTexture;
extern GRAPHIC_SHADER_BIND GRAPHIC_SHADER_BIND_PositionNormalTexture;
extern GRAPHIC_SHADER_BIND GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent;

#if OPENGL4
    enum GRAPHIC_SHADER_BIND_OPENGL4 {
        GRAPHIC_SHADER_BIND_OPENGL4_Position =      0,
        GRAPHIC_SHADER_BIND_OPENGL4_Normal,
        GRAPHIC_SHADER_BIND_OPENGL4_Color,
        GRAPHIC_SHADER_BIND_OPENGL4_Texcoord0,
        GRAPHIC_SHADER_BIND_OPENGL4_Texcoord1,
        GRAPHIC_SHADER_BIND_OPENGL4_SkinWeight,
        GRAPHIC_SHADER_BIND_OPENGL4_JointIndices,
        GRAPHIC_SHADER_BIND_OPENGL4_Tangents,
        GRAPHIC_SHADER_BIND_OPENGL4_Bitangents,
        GRAPHIC_SHADER_BIND_OPENGL4_CustomFloat
    };
#endif

#if OPENGLES2
    enum GRAPHIC_SHADER_BIND_OPENGLES2 {
        GRAPHIC_SHADER_BIND_OPENGLES2_Position =      0,
        GRAPHIC_SHADER_BIND_OPENGLES2_Normal,
        GRAPHIC_SHADER_BIND_OPENGLES2_Color,
        GRAPHIC_SHADER_BIND_OPENGLES2_Texcoord0,
        GRAPHIC_SHADER_BIND_OPENGLES2_Texcoord1,
        GRAPHIC_SHADER_BIND_OPENGLES2_SkinWeight,
        GRAPHIC_SHADER_BIND_OPENGLES2_JointIndices,
        GRAPHIC_SHADER_BIND_OPENGLES2_Tangents,
        GRAPHIC_SHADER_BIND_OPENGLES2_Bitangents,
        GRAPHIC_SHADER_BIND_OPENGLES2_CustomFloat
    };
#endif

#endif
