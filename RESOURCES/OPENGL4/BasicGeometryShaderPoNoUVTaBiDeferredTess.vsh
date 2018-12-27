#version 410 core

in vec4 position;
in vec4 normal;
in vec2 tex0;
in vec3 tangent;
in vec3 bitangent;

out vec4 WorldPos0_CS_IN;
out vec2 texCoord_CS_IN;
out vec4 o_normal_CS_IN;
out vec4 ShadowCoord_CS_IN[3];
out mat3 TBNMatrix_p_CS_IN;

uniform mat4 ModelMatrix;
uniform mat4 ShadowMapMVP1;
uniform mat4 ShadowMapMVP2;
uniform mat4 ShadowMapMVP3;

void main()
{
	o_normal_CS_IN = ModelMatrix * normal; 
	WorldPos0_CS_IN = ModelMatrix * position;
    texCoord_CS_IN = tex0;

    ShadowCoord_CS_IN[0] = ShadowMapMVP1 * position;
    ShadowCoord_CS_IN[1] = ShadowMapMVP2 * position;
    ShadowCoord_CS_IN[2] = ShadowMapMVP3 * position;

    mat3 TBNMatrix = transpose(
        mat3(
        tangent,
        bitangent,
        normal
        ));

    TBNMatrix_p_CS_IN = TBNMatrix;
}