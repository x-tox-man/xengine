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

varying highp vec4 colorVarying;

uniform mat4 ProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 geometryColor;
uniform vec4 geometryPosition[4];

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 1.0 );
    int index = int(normal.x);
    
    gl_Position = geometryPosition[index] * modelViewMatrix * ProjectionMatrix;
}
