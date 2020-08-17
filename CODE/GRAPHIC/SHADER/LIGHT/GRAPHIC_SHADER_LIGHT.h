//
//  GRAPHIC_SHADER_LIGHT.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 23/09/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_LIGHT__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_LIGHT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "GRAPHIC_SHADER_ATTRIBUTE.h"
#include "GRAPHIC_SHADER_TYPE.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "CORE_FILESYSTEM.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_MATRIX.h"
#include "GRAPHIC_SHADER_LIGHT_TYPE.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_TEXTURE_LOADER.h"

class GRAPHIC_RENDERER;

struct GRAPHIC_SHADER_LIGHT_POINT {
    
    float Color[4];
    float Position[4];
    float AmbientIntensity;
    float DiffuseIntensity;
    float Exp;
    float Linear;
    float Constant;
};

struct GRAPHIC_SHADER_LIGHT_AMBIENT {
    
    float Color[4];
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct GRAPHIC_SHADER_LIGHT_SPOT {
    
    float Color[4];
    float Position[4];
    float Direction[4];
    float Orientation[4];
    float Cutoff;
    float AmbientIntensity;
    float DiffuseIntensity;
    float Exp;
    float Linear;
    float Constant;
};

struct GRAPHIC_SHADER_LIGHT_DIRECTIONAL {
    
    float Color[4];
    float Direction[4];
    float AmbientIntensity;
    float DiffuseIntensity;
};

union GRAPHIC_SHADER_LIGHT_INTERNAL {
    
    GRAPHIC_SHADER_LIGHT_POINT Point;
    GRAPHIC_SHADER_LIGHT_AMBIENT Ambient;
    GRAPHIC_SHADER_LIGHT_SPOT Spot;
    GRAPHIC_SHADER_LIGHT_DIRECTIONAL Directional;
};

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_SHADER_LIGHT )

    GRAPHIC_SHADER_LIGHT();
    ~GRAPHIC_SHADER_LIGHT();

    void InitializePoint(
                         const CORE_MATH_VECTOR & color,
                         const CORE_MATH_VECTOR & position,
                         float exp,
                         float constant,
                         float linear,
                         float ambient_intensity,
                         float diffuse_intensity
                         );

    void InitializeAmbient(
                           const CORE_MATH_VECTOR & color,
                           float ambient_intensity,
                           float diffuse_intensity
                           );
    void InitializeSpot(
                        const CORE_MATH_VECTOR & color,
                        const CORE_MATH_VECTOR & position,
                        const CORE_MATH_VECTOR & direction,
                        float exp,
                        float constant,
                        float linear,
                        float cutoff,
                        float ambient_intensity,
                        float diffuse_intensity);

    void InitializeDirectional(
                               const CORE_MATH_VECTOR & color,
                               const CORE_MATH_VECTOR & direction,
                               float ambient_intensity,
                               float diffuse_intensity);

    void ComputeModelViewProjection( GRAPHIC_RENDERER & renderer, CORE_MATH_MATRIX & mvp );

    void Apply( GRAPHIC_SHADER_PROGRAM & program );

    GRAPHIC_SHADER_LIGHT & operator=( const GRAPHIC_SHADER_LIGHT & other ) {
        
        Type = other.Type;
        InternalLight = other.InternalLight;
        LightIndex = other.LightIndex;
        
        return *this;
    }


    GRAPHIC_SHADER_LIGHT_TYPE
        Type;
    GRAPHIC_SHADER_LIGHT_INTERNAL
        InternalLight;
    int
        LightIndex;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_LIGHT__) */
