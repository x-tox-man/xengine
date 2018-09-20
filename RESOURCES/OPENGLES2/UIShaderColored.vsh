//
//  UIShaderTextured.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 100

attribute vec4 position;
attribute vec4 normal;

varying highp vec4 colorVarying;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;

void main()
{
    colorVarying = geometryColor;
    
    gl_Position = MVPMatrix * position;
}
