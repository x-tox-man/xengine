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
attribute highp vec2 tex0;
attribute highp vec3 tangent;
attribute highp vec3 bitangent;

uniform DirectionalLight directional_light;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;

void main()
{
    gl_Position = MVPMatrix * position;
}
