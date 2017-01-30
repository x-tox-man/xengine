//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 100

attribute vec4 position;
attribute vec4 normal;
attribute vec2 tex0;

varying highp vec2 textureCoordinates;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;

void main()
{
    textureCoordinates = tex0;
    
    vec4 t = normal;
    gl_PointSize = 2.0;
    gl_Position = position * MVPMatrix;
}
