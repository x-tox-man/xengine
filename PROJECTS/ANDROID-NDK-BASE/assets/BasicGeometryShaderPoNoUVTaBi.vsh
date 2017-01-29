//
//  BasicGeometryShaderPoNoUVTaBi.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 03/04/16.
//  Copyright (c) 2016 Christophe Bernard. All rights reserved.
//

#version 100

// -- TYPES

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

// -- IN

attribute highp vec4 position;
attribute highp vec4 normal;

// -- OUT

varying vec4 colorVarying;
varying vec4 o_normal;

// -- CONSTANTS

uniform mat4 ProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 geometryColor;
uniform DirectionalLight directional_light;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    o_normal = normal;
    
    colorVarying = normalize(position);
    
    gl_Position = position * modelViewMatrix * ProjectionMatrix;
}