//
//  GRAPHIC_SHADER_TYPE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_GRAPHIC_SHADER_TYPE_h
#define GAME_ENGINE_REBORN_GRAPHIC_SHADER_TYPE_h

enum GRAPHIC_SHADER_TYPE
{
    GRAPHIC_SHADER_None = 0,
    GRAPHIC_SHADER_Vertex,
    GRAPHIC_SHADER_Pixel,
    GRAPHIC_SHADER_Geometry,
    GRAPHIC_SHADER_Compute,
    GRAPHIC_SHADER_HullControlShader,
    GRAPHIC_SHADER_TessellateEvaluation,
    GRAPHIC_SHADER_Count
};

#endif
