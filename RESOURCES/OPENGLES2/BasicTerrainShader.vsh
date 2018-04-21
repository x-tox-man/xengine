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

uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;

varying highp vec4 colorVarying;
varying highp vec4 o_normal;
varying highp vec2 texCoord;

uniform mat4 MVPMatrix;
uniform mat4 ShadowMapMVP;
uniform vec4 geometryColor;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    o_normal = normal;
    texCoord = tex0;
    colorVarying = position;
    gl_Position = position * MVPMatrix;
}
