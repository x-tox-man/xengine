#version 330

in vec4 o_normal;
in vec2 texCoord;
in vec3 WorldPos0;
in float ClipSpacePosZ;
in vec4 ShadowCoord[3];

layout (location = 0) out vec4 WorldPosOut; 
layout (location = 1) out vec4 DiffuseOut; 
layout (location = 2) out vec4 NormalOut;
layout (location = 3) out vec4 ShadowOut;
layout (location = 4) out float SSAO;

uniform sampler2D c_texture;
uniform sampler2D d_texture;
uniform sampler2D d_texture1;
uniform sampler2D d_texture2;
uniform mediump mat4 ModelMatrix;
uniform float cascadeEndClipSpace[3];
uniform float MaterialSpecularIntensity;

float CalcShadowFactor(int CascadeIndex, vec4 LightSpacePos)
{ 
    float Depth = 0.0;

    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;

    if ( CascadeIndex == 0) 
        Depth = texture( d_texture, ProjCoords.xy).x; 
    if ( CascadeIndex == 1)
        Depth = texture( d_texture1, ProjCoords.xy).x; 
    if ( CascadeIndex == 2) 
        Depth = texture( d_texture2, ProjCoords.xy).x;

    if (Depth > ProjCoords.z + 0.001 ) 
        return 0.01;
    else 
        return 1.0; 
}

void main() 
{ 
    DiffuseOut = texture( c_texture, texCoord );
    DiffuseOut.a = 1.0;
    NormalOut = o_normal;
    WorldPosOut = vec4( WorldPos0, 1.0);

    ShadowOut.rgba = vec4(1.0);

    if ( dot( o_normal.xyz, directional_light.Direction.xyz ) > 0.0 ) {
        
        for (int i = 0 ; i < 3 ; i++) {

            if ( ClipSpacePosZ <= cascadeEndClipSpace[i] ) {
                
                ShadowOut.rgba = vec4(CalcShadowFactor(i, ShadowCoord[i]));
                break;
            }
        }
    }

    ShadowOut.g = MaterialSpecularIntensity;

    ShadowOut.a = 1.0;
}