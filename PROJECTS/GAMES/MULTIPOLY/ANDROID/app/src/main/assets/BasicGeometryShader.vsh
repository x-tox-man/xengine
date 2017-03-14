//
//  BasicGeometryShader.vsh
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 100

struct DirectionalLight
{
    highp vec4 Color;
    highp vec4 Direction;
    highp float AmbientIntensity;
    highp float DiffuseIntensity;
};


attribute vec4 position;
attribute vec4 normal;

varying highp vec4 colorVarying;
varying highp vec4 o_normal;

uniform highp mat4 MVPMatrix;
uniform vec4 geometryColor;
uniform DirectionalLight directional_light;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    o_normal = normal;
    
    gl_Position = position * MVPMatrix;
}
