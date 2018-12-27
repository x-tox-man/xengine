#version 410 core

in vec3 oWorldPos0;
in vec2 texCoord;
in vec4 o_normal;
//layout (location = 3) in float ClipSpacePosZ;
//layout (location = 4) in vec4 ShadowCoord[3];
//layout (location = 5) in mat3 TBNMatrix_p;

layout (location = 0) out vec4 WorldPosOut; 
layout (location = 1) out vec4 DiffuseOut; 
layout (location = 2) out vec4 NormalOut;
layout (location = 3) out vec4 ShadowOut;
layout (location = 4) out float SSAO;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
//uniform sampler2D c_texture;
//uniform sampler2D n_texture;
//uniform sampler2D d_texture;
//uniform sampler2D d_texture1;
//uniform sampler2D d_texture2;
//uniform float cascadeEndClipSpace[3];


/*float CalcShadowFactor(int CascadeIndex, vec4 LightSpacePos)
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
}*/

void main() 
{ 
	vec4 normalTimesLModel = o_normal;

    //-------- NORMAL MAPPING BEGIN
    /*vec3 BumpMapNormal = texture(n_texture, texCoord).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);

    vec3 NewNormal;

    NewNormal = vec3(1.0);//TBNMatrix_p * BumpMapNormal;
    NewNormal = normalize(NewNormal);*/
    //-------- NORMAL MAPPING END

    //DiffuseOut = texture( c_texture, texCoord );
    DiffuseOut = vec4( 1.0 );
    NormalOut = vec4( 1.0 );
    WorldPosOut = vec4( oWorldPos0, 1.0);

    ShadowOut.rgba = vec4(1.0);

    //float d = texture( d_texture, texCoord.xy).x  + texture( d_texture1, texCoord.xy).x + texture( d_texture2, texCoord.xy).x;

    /*for (int i = 0 ; i < 3 ; i++) {

        if ( ClipSpacePosZ <= cascadeEndClipSpace[i]) {
            
            ShadowOut.rgba = vec4(CalcShadowFactor(i, ShadowCoord[i]));
            break;
        }
    }*/

    DiffuseOut = vec4(1.0,0.0, 0.0, 1.0);

    ShadowOut.a = 1.0;
}
