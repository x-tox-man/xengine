//
//  GRAPHIC_SHADER_LIGHT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 23/09/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_LIGHT.h"
#include "GRAPHIC_RENDERER.h"

GRAPHIC_SHADER_LIGHT::GRAPHIC_SHADER_LIGHT() :
    Type( GRAPHIC_SHADER_LIGHT_TYPE_None ),
    InternalLight() {
    
}

GRAPHIC_SHADER_LIGHT::~GRAPHIC_SHADER_LIGHT() {

}

void GRAPHIC_SHADER_LIGHT::InitializePoint(
                     CORE_MATH_VECTOR & color,
                     CORE_MATH_VECTOR & position,
                     float exp,
                     float constant,
                     float linear,
                     float ambient_intensity,
                     float diffuse_intensity ) {
    
    Type = GRAPHIC_SHADER_LIGHT_TYPE_Point;
    
    InternalLight.Point.Color[0] = color[0];
    InternalLight.Point.Color[1] = color[1];
    InternalLight.Point.Color[2] = color[2];
    
    InternalLight.Point.Position[0] = position[0];
    InternalLight.Point.Position[1] = position[1];
    InternalLight.Point.Position[2] = position[2];
    
    InternalLight.Point.Exp = exp;
    InternalLight.Point.Constant = constant;
    InternalLight.Point.Linear = linear;
    InternalLight.Point.AmbientIntensity = ambient_intensity;
    InternalLight.Point.DiffuseIntensity = diffuse_intensity;
}

void GRAPHIC_SHADER_LIGHT::InitializeAmbient(
                       CORE_MATH_VECTOR & color,
                       float ambient_intensity,
                       float diffuse_intensity ) {
    
    Type = GRAPHIC_SHADER_LIGHT_TYPE_Ambient;
    
    Type = GRAPHIC_SHADER_LIGHT_TYPE_Point;
    
    InternalLight.Ambient.Color[0] = color[0];
    InternalLight.Ambient.Color[1] = color[1];
    InternalLight.Ambient.Color[2] = color[2];
    
    InternalLight.Ambient.AmbientIntensity = ambient_intensity;
    InternalLight.Ambient.DiffuseIntensity = diffuse_intensity;
}

void GRAPHIC_SHADER_LIGHT::InitializeSpot(
                    CORE_MATH_VECTOR & color,
                    CORE_MATH_VECTOR & position,
                    CORE_MATH_VECTOR & direction,
                    float exp,
                    float constant,
                    float linear,
                    float cutoff,
                    float ambient_intensity,
                    float diffuse_intensity) {
    
    Type = GRAPHIC_SHADER_LIGHT_TYPE_Spot;
    
    InternalLight.Spot.Color[0] = color[0];
    InternalLight.Spot.Color[1] = color[1];
    InternalLight.Spot.Color[2] = color[2];
    
    InternalLight.Spot.Position[0] = position[0];
    InternalLight.Spot.Position[1] = position[1];
    InternalLight.Spot.Position[2] = position[2];
    
    InternalLight.Spot.Direction[0] = direction[0];
    InternalLight.Spot.Direction[1] = direction[1];
    InternalLight.Spot.Direction[2] = direction[2];
    
    InternalLight.Spot.Exp = exp;
    InternalLight.Spot.Constant = constant;
    InternalLight.Spot.Linear = linear;
    InternalLight.Spot.Cutoff = cutoff;
    InternalLight.Spot.AmbientIntensity = ambient_intensity;
    InternalLight.Spot.DiffuseIntensity = diffuse_intensity;
}

void GRAPHIC_SHADER_LIGHT::InitializeDirectional(
                           CORE_MATH_VECTOR & color,
                           CORE_MATH_VECTOR & direction,
                           float ambient_intensity,
                            float diffuse_intensity) {
    
    Type = GRAPHIC_SHADER_LIGHT_TYPE_Directional;
    
    InternalLight.Directional.Color[0] = color[0];
    InternalLight.Directional.Color[1] = color[1];
    InternalLight.Directional.Color[2] = color[2];
    
    InternalLight.Directional.Direction[0] = direction[0];
    InternalLight.Directional.Direction[1] = direction[1];
    InternalLight.Directional.Direction[2] = direction[2];
    
    InternalLight.Directional.AmbientIntensity = ambient_intensity;
    InternalLight.Directional.DiffuseIntensity = diffuse_intensity;
}

void GRAPHIC_SHADER_LIGHT::Apply( GRAPHIC_SHADER_PROGRAM & program ) {
    
    switch ( Type ) {
            
        case GRAPHIC_SHADER_LIGHT_TYPE_Directional:
            
            GRAPHIC_SYSTEM::ApplyLightDirectional( *this, program );
            
            break;
            
        case GRAPHIC_SHADER_LIGHT_TYPE_Ambient:
            
            GRAPHIC_SYSTEM::ApplyLightAmbient( *this, program );
            
            break;
            
        case GRAPHIC_SHADER_LIGHT_TYPE_Point:
            
            GRAPHIC_SYSTEM::ApplyLightPoint( *this, program, 0 );
            
            break;
            
        case GRAPHIC_SHADER_LIGHT_TYPE_Spot:
            
            GRAPHIC_SYSTEM::ApplyLightSpot( *this, program, 0 );
            
            break;
            
        default:
            break;
    }
}

void GRAPHIC_SHADER_LIGHT::ComputeModelViewProjection( GRAPHIC_RENDERER & renderer, CORE_MATH_MATRIX & mvp ) {
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    
    mvp = renderer.GetCamera().GetProjectionMatrix();
    mvp *= renderer.GetCamera().GetViewMatrix();
    mvp *= CORE_MATH_MATRIX( CORE_MATH_MATRIX::Identity );
}
