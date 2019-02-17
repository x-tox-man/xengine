#version 330

in vec3 WorldPos0;
in vec4 o_normal;
in vec2 texCoord;
in mat3 TBNMatrix_p;
in float ClipSpacePosZ;
in vec4 ShadowCoord[3];

layout (location = 0) out vec4 WorldPosOut; 
layout (location = 1) out vec4 DiffuseOut; 
layout (location = 2) out vec4 NormalOut;
layout (location = 3) out vec4 ShadowOut;
layout (location = 4) out float SSAO;

//uniform mat4 MVPMatrix;
//uniform mat4 ModelMatrix;
uniform sampler2D c_texture; // base texture for indexing decals - each composant is the weight of the texture
uniform sampler2D c_texture_1; // Decal 1
uniform sampler2D c_texture_2; // Decal 2
uniform sampler2D c_texture_3; // Decal 3
//uniform sampler2D n_texture;
uniform sampler2D d_texture;
uniform sampler2D d_texture1;
uniform sampler2D d_texture2;
uniform float cascadeEndClipSpace[3];

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
    //vec4 normalTimesLModel = ModelMatrix * o_normal;

    //-------- NORMAL MAPPING BEGIN
    ///vec3 BumpMapNormal = texture(n_texture, texCoord).xyz;
    //BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);

    //vec3 NewNormal;

    //NewNormal = TBNMatrix_p * BumpMapNormal;
    //NewNormal = normalize(NewNormal);
    //-------- NORMAL MAPPING END

    vec4 decalsWeights = texture(c_texture, texCoord);

    DiffuseOut = ( texture( c_texture_1, texCoord * 512.0 ) * decalsWeights.x + texture( c_texture_2, texCoord * 128.0) * decalsWeights.y + texture( c_texture_3, texCoord * 128.0) * decalsWeights.z ) * vec4( 1.0);

    //DiffuseOut = decalsWeights;//texture( c_texture_1, texCoord);

    DiffuseOut.a = 1.0;
    NormalOut = o_normal;//vec4( NewNormal, 1.0 );
    NormalOut.a = 1.0;
    WorldPosOut = vec4( WorldPos0, 1.0);

    ShadowOut.rgba = vec4(1.0);

    for (int i = 0 ; i < 3 ; i++) {

        if ( ClipSpacePosZ <= cascadeEndClipSpace[i]) {
            
            ShadowOut.rgba = vec4(CalcShadowFactor(i, ShadowCoord[i]));
            break;
        }
    }

    ShadowOut.a = 1.0;
}