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
varying mediump vec2 o_tex;
varying mediump mat3 TBNMatrix_p;

// -- CONSTANTS

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform sampler2D d_texture;
uniform mediump vec4 geometryColor;
uniform DirectionalLight directional_light;
uniform mediump mat4 modelViewMatrix;

void main()
{
	mediump vec4 normalTimesLModel = modelViewMatrix * o_normal;

    //-------- NORMAL MAPPING BEGIN

    mediump vec3 BumpMapNormal = texture2D(n_texture, o_tex).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);

    mediump vec3 NewNormal;

    NewNormal = TBNMatrix_p * BumpMapNormal;
    NewNormal = normalize(NewNormal);

    //-------- NORMAL MAPPING END

    mediump float nxDir = max(0.1, dot( NewNormal.xyz, directional_light.Direction.xyz));
    mediump vec4 diffuse = texture2D(c_texture, o_tex) * nxDir;
	diffuse.a = 1.0;

    gl_FragColor = diffuse;
}

