#version 330

in vec2 TexCoord;

layout (location = 0) out vec4 WorldPosOut; 
layout (location = 1) out vec4 DiffuseOut; 
layout (location = 2) out vec4 NormalOut;
layout (location = 3) out vec4 Shadow;
layout (location = 4) out vec4 SSAO;

uniform sampler2D c_texture;

float Offsets[4] = float[]( -1.5, -0.5, 0.5, 1.5 );

void main()
{
    vec3 Color = vec3(0.0, 0.0, 0.0);

    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            vec2 tc = TexCoord;
            tc.x = TexCoord.x + Offsets[j] / textureSize(c_texture, 0).x;
            tc.y = TexCoord.y + Offsets[i] / textureSize(c_texture, 0).y;
            Color += texture(c_texture, tc).xyz;
        }
    }

    Color /= 16.0;

    SSAO = vec4(Color, 1.0);
}