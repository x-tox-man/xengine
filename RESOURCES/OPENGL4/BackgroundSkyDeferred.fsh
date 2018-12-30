#version 330

in vec4 WorldPos0;
in vec4 o_normal;
in vec2 texCoord;
in mat3 TBNMatrix_p;

layout (location = 0) out vec4 WorldPosOut; 
layout (location = 1) out vec4 DiffuseOut; 
layout (location = 2) out vec4 NormalOut;
layout (location = 3) out vec4 ShadowOut;
layout (location = 4) out float SSAO;

uniform sampler2D c_texture;

void main()
{
    WorldPosOut = WorldPos0;
    DiffuseOut.rgb = texture( c_texture, texCoord ).rgb;
    DiffuseOut.a = 1.0;

    NormalOut = o_normal;

    ShadowOut = vec4( 1.0 );
}
