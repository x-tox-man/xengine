//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 330

in vec4 position;
in vec4 normal;
in vec2 tex0;
in vec3 tangent;
in vec3 bitangent;

out vec4 WorldPos0;
out vec4 o_normal;
out vec2 texCoord;

uniform mat4 MVPMatrix;
uniform mat4 ModelMatrix;

void main()
{
    o_normal = ModelMatrix * normal; 
    texCoord = tex0;

    WorldPos0 = ModelMatrix * position;
    gl_Position = MVPMatrix * position;
    WorldPos0.z = gl_Position.w;
}
