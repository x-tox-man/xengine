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

attribute highp vec4 position;
attribute highp vec4 normal;

uniform DirectionalLight directional_light;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;
uniform mat4 ShadowMapMVP;

void main()
{
    gl_Position = position * MVPMatrix;
}
