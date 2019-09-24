#version 330 

in vec4 position;
in vec4 normal;
in vec2 tex0;

out vec4 o_normal;
out vec2 texCoord;
out vec3 WorldPos0;
out mat3 TBNMatrix_p;
out float ClipSpacePosZ;
out vec4 ShadowCoord[3];

uniform mat4 MVPMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ShadowMapMVP1;
uniform mat4 ShadowMapMVP2;
uniform mat4 ShadowMapMVP3;

void main()
{
    texCoord = tex0; 
    o_normal =  ModelMatrix * normal; 
    WorldPos0 = ( ModelMatrix * position).xyz;

    gl_Position = MVPMatrix * position; 
    ClipSpacePosZ = gl_Position.z;

    ShadowCoord[0] = ShadowMapMVP1 * position;
    ShadowCoord[1] = ShadowMapMVP2 * position;
    ShadowCoord[2] = ShadowMapMVP3 * position;

    /*mat3 TBNMatrix = transpose(
        mat3(
        tangent,
        bitangent,
        normal

        ));*/

    //TBNMatrix_p = TBNMatrix;
}