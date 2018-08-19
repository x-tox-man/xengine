//
//  UIShaderTextured.vsh
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 100

attribute vec4 position;
attribute vec4 normal;
attribute vec2 tex0;

varying highp vec4 colorVarying;
varying highp vec2 textureCoordinates;

uniform vec4 geometryColor;
uniform mat4 MVPMatrix;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = geometryColor;
    textureCoordinates = tex0;
    
    gl_Position = MVPMatrix * position;
}
