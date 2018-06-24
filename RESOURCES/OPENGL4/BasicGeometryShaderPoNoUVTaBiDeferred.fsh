#version 330

in vec4 colorVarying;
in vec4 o_normal;
in vec2 texCoord;
in mat3 TBNMatrix_p;
in vec3 WorldPos0;

layout (location = 0) out vec4 WorldPosOut; 
layout (location = 1) out vec4 DiffuseOut; 
layout (location = 2) out vec4 NormalOut;

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform mediump mat4 modelViewMatrix;

uniform sampler2D gColorMap; 

void main() 
{ 
	vec4 normalTimesLModel = modelViewMatrix * o_normal;

    //-------- NORMAL MAPPING BEGIN
    vec3 BumpMapNormal = texture(n_texture, texCoord).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);

    vec3 NewNormal;

    NewNormal = TBNMatrix_p * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    //-------- NORMAL MAPPING END

    DiffuseOut = texture( c_texture, texCoord );// * colorVarying.xyz;
    NormalOut = vec4( NewNormal, 1.0 );
    WorldPosOut = vec4( WorldPos0, 1.0);
}