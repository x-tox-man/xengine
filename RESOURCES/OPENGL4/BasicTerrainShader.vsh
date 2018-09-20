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

uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;

out vec4 colorVarying;
out vec4 o_normal;
out DirectionalLight directional_light_out;
out vec4 ShadowCoord[3];
out vec3 WorldPos0;
out vec2 texCoord;
out mat3 TBNMatrix_p;
out float ClipSpacePosZ;

uniform mat4 MVPMatrix;
uniform mat4 ShadowMapMVP1;
uniform mat4 ShadowMapMVP2;
uniform mat4 ShadowMapMVP3;
uniform vec4 geometryColor;
uniform mat4 modelViewMatrix;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    directional_light_out = directional_light;
    
    o_normal = (modelViewMatrix * normal); 
    WorldPos0 = (modelViewMatrix * position).xyz;
    texCoord = tex0;
    colorVarying = position;
    
    ShadowCoord[0] = ShadowMapMVP1 * position;
    ShadowCoord[1] = ShadowMapMVP2 * position;
    ShadowCoord[2] = ShadowMapMVP3 * position;

    ClipSpacePosZ = gl_Position.z;
    
    gl_Position = MVPMatrix * position;
}
