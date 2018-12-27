#version 410 core

in vec4 position;
in vec4 normal;
in vec2 tex0;
in vec3 tangent;
in vec3 bitangent;

out vec4 WorldPos0_CS_IN;
out vec2 texCoord_CS_IN;
out vec4 o_normal_CS_IN;
//out vec4 ShadowCoord_CS_IN[3];
//out mat3 TBNMatrix_p_CS_IN;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
//uniform sampler2D c_texture;
//uniform sampler2D n_texture;
//uniform sampler2D d_texture;
//uniform sampler2D d_texture1;
//uniform sampler2D d_texture2;
//uniform float cascadeEndClipSpace[3];
//uniform mat4 ShadowMapMVP1;
//uniform mat4 ShadowMapMVP2;
//uniform mat4 ShadowMapMVP3;

void main()
{
    WorldPos0_CS_IN = ModelMatrix * position;
    texCoord_CS_IN = tex0;
    o_normal_CS_IN = ModelMatrix * normal;
    o_normal_CS_IN = normalize( o_normal_CS_IN );

    //ShadowCoord_CS_IN[0] = ShadowMapMVP1 * position;
    //ShadowCoord_CS_IN[1] = ShadowMapMVP2 * position;
    //ShadowCoord_CS_IN[2] = ShadowMapMVP3 * position;

    mat3 TBNMatrix = transpose(
        mat3(
        tangent,
        bitangent,
        normal
        ));

    //TBNMatrix_p_CS_IN = TBNMatrix;
}