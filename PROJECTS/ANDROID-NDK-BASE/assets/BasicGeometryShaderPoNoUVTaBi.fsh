//
//  BasicGeometryShaderPoNoUVTaBi.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 03/04/16.
//  Copyright (c) 2016 Christophe Bernard. All rights reserved.
//

#version 100

// -- TYPES

struct DirectionalLight
{
    lowp vec4 Color;
    lowp vec4 Direction;
    lowp float AmbientIntensity;
    lowp float DiffuseIntensity;
};

// -- IN/OUT

varying mediump vec4 colorVarying;
varying mediump vec4 o_normal;

// -- CONSTANTS

uniform mediump vec4 geometryColor;
uniform DirectionalLight directional_light;

void main()
{
    mediump float nxDir = max(0.1, dot( o_normal.xyz, directional_light.Direction.xyz));
    mediump vec4 diffuse = directional_light.Color * nxDir;
    
    gl_FragColor = o_normal + colorVarying* geometryColor* 0.005 + diffuse * 0.1;
}

