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

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;

void main()
{
    gl_Position = MVPMatrix * position;
}
