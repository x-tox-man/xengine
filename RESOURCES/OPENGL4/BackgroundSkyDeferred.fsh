#version 330

in vec4 o_normal;
in vec2 texCoord;
in mat3 TBNMatrix_p;
in vec3 WorldPos0;
in float ClipSpacePosZ;
in vec4 ShadowCoord[3];

layout (location = 0) out vec4 WorldPosOut; 
layout (location = 1) out vec4 DiffuseOut; 
layout (location = 2) out vec4 NormalOut;
layout (location = 3) out vec4 ShadowOut;
layout (location = 4) out float SSAO;

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform sampler2D d_texture;
uniform sampler2D d_texture1;
uniform sampler2D d_texture2;
uniform mediump mat4 ModelMatrix;
uniform float cascadeEndClipSpace[3];

void main()
{
    
    colorOut.rgb = texture( c_texture, texCoord ).rgb * diffuse.rgb;

    colorOut.a = 1.0;
}
