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
in vec2 tex0;
in vec3 tangent;
in vec3 bitangent;

out vec4 colorVarying;
out vec4 o_normal;
out vec2 texCoord;
out mat3 TBNMatrix_p;

uniform mat4 MVPMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ShadowMapMVP1;
uniform mat4 ShadowMapMVP2;
uniform mat4 ShadowMapMVP3;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    directional_light_out = directional_light;

    vec4 ShadowCoord1 = ShadowMapMVP1 * position;
    vec4 ShadowCoord2 = ShadowMapMVP2 * position;
    vec4 ShadowCoord3 = ShadowMapMVP3 * position;
    
    o_normal = normal;
    texCoord = tex0;
    colorVarying = position;

    mat3 TBNMatrix = transpose(
        mat3(
        tangent,
        bitangent,
        normal
        ));

    TBNMatrix_p = TBNMatrix;

    gl_Position = MVPMatrix * position;
    gl_Position.z = gl_Position.w;
}
