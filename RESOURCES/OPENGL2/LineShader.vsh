//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 330

in vec4 position;

out vec4 colorVarying;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;

void main()
{
    //float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 1.0 );
    
    gl_Position = position * MVPMatrix;
}
