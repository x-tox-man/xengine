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

void main()
{
	oTime = time;
	gl_Position = normal;
    gl_Position = MVPMatrix * position;
    gl_PointSize = 35.0f;
    
}
