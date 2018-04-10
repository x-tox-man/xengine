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
in float time;

out float oTime;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;
uniform vec4 ScaleFactor;

void main()
{
    oTime = normal.x;
    
    gl_Position = position * MVPMatrix;
    gl_PointSize = oTime * ScaleFactor.x;
}
