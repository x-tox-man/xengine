#version 330

in vec4 colorVarying;
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
uniform mediump mat4 modelViewMatrix;
uniform float cascadeEndClipSpace[3];

uniform sampler2D gColorMap; 

float CalcShadowFactor(int CascadeIndex, vec4 LightSpacePos)
{ 
    float Depth = 0.0;

    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;

    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;

    if ( CascadeIndex == 0) 
        Depth = texture( d_texture, UVCoords.xy).x; 
    if ( CascadeIndex == 1)
        Depth = texture( d_texture1, UVCoords.xy).x; 
    if ( CascadeIndex == 2) 
        Depth = texture( d_texture2, UVCoords.xy).x;

    if (Depth > z + 0.001 ) 
        return 0.01;
    else 
        return 1.0; 
}

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
    DiffuseOut.a = 1.0;
    NormalOut = vec4( NewNormal, 1.0 );
    WorldPosOut = vec4( WorldPos0, 1.0);

    ShadowOut.rgba = vec4(1.0);

    for (int i = 0 ; i < 3 ; i++) {

        if ( ClipSpacePosZ <= cascadeEndClipSpace[i]) {
            
            ShadowOut.rgba = vec4(CalcShadowFactor(i, ShadowCoord[i]));
            break;
        }
    }

    /*vec3 ProjCoords = ShadowCoord[0].xyz / ShadowCoord[0].w;

    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;

    ShadowOut.r = texture( d_texture, UVCoords.xy).x;
    ShadowOut.gb = vec2(0.0);//UVCoords.xy;*/
    ShadowOut.a = 1.0;
}