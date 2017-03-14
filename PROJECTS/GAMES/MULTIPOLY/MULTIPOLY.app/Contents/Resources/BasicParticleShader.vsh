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

out vec2 textureCoordinates;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;

void main()
{
    textureCoordinates = tex0;
    
    vec4 t = normal;
    
    gl_Position = position * MVPMatrix;
}
