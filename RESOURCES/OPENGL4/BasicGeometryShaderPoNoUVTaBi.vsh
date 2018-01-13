//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 330

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct AmbientLight
{
    vec4 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

in vec4 position;
in vec4 normal;
in vec2 tex0;
in vec3 tangent;
in vec3 bitangent;

uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;

out vec4 colorVarying;
out vec4 o_normal;
out DirectionalLight directional_light_out;
out vec4 ShadowCoord;
out vec2 texCoord;
out mat3 TBNMatrix_p;

uniform mat4 MVPMatrix;
uniform mat4 ShadowMapMVP;
uniform vec4 geometryColor;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    directional_light_out = directional_light;
    
    o_normal = normal;
    texCoord = tex0;
    colorVarying = position;
    
    ShadowCoord = position * ShadowMapMVP;
    gl_Position = position * MVPMatrix;

    mat3 TBNMatrix = transpose(
        mat3(
        tangent,
        bitangent,
        normal
        ));

    TBNMatrix_p = TBNMatrix;
}
