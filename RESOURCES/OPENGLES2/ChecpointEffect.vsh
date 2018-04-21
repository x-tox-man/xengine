//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 100

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};
struct AmbientLight
{
    vec4 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

attribute vec4 position;
attribute vec4 normal;
attribute vec2 tex0;

varying vec4 colorVarying;
varying vec4 o_normal;
varying DirectionalLight directional_light_out;
varying vec4 ShadowCoord;
varying vec2 texCoord;

uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;
uniform mat4 MVPMatrix;
uniform mat4 ShadowMapMVP;
uniform float TimeModulator;
uniform vec4 geometryColor;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    directional_light_out = directional_light;
    
    o_normal = normal;
    texCoord = tex0 + TimeModulator;
    colorVarying = position;
    
    ShadowCoord = position * ShadowMapMVP;
    gl_Position = position * MVPMatrix;
}
