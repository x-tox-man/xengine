#version 410 core

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

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform sampler2DShadow d_texture;
uniform sampler2DShadow d_texture1;
uniform sampler2DShadow d_texture2;
uniform mediump mat4 ModelMatrix;
uniform float cascadeEndClipSpace[3];
uniform DirectionalLight directional_light;


uniform sampler2D gColorMap; 

float CalcShadowFactor(int CascadeIndex, vec4 LightSpacePos)
{ 
    float Depth = 0.0;

    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;

    float xOffset = 1.0 / 1024.0;
    float yOffset = 1.0 / 768.0;

    float Factor = 0.0;
    const float EPSILON = 0.00001;

    for (int y = -1 ; y <= 1 ; y++) {
        for (int x = -1 ; x <= 1 ; x++) {
            vec2 Offsets = vec2(x * xOffset, y * yOffset);

            vec3 UVC = vec3(ProjCoords.xy + Offsets, ProjCoords.z + EPSILON);

            if ( CascadeIndex == 0) 
                Depth = texture( d_texture, UVC);
            else if ( CascadeIndex == 1)
                Depth = texture( d_texture1, UVC);
            else if ( CascadeIndex == 2) 
                Depth = texture( d_texture2, UVC);

            Factor += Depth;
        }
    }

    return 1.0 - (Factor / 18.0);
}

void main() 
{
    //-------- NORMAL MAPPING BEGIN
    vec3 BumpMapNormal = texture(n_texture, texCoord).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);

    vec3 NewNormal;

    NewNormal = TBNMatrix_p * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    //-------- NORMAL MAPPING END

    DiffuseOut = texture( c_texture, texCoord );
    DiffuseOut.a = 1.0;
    NormalOut = vec4( NewNormal, 1.0 );
    WorldPosOut = vec4( WorldPos0, 1.0);

    ShadowOut.rgba = vec4(0.0);
        
    for (int i = 0 ; i < 1 ; i++) {

        if ( -ClipSpacePosZ <= cascadeEndClipSpace[i] ) {
            
            ShadowOut.rgba = vec4(CalcShadowFactor(i, ShadowCoord[i]));

            break;
        }

    }

    ShadowOut.a = 1.0;
}