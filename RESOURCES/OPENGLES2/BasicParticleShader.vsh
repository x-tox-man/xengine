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

uniform sampler2D c_texture;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;

void main()
{
    vec4 t = normal;
    gl_PointSize = 2.0;
    gl_Position = MVPMatrix * position;
}
