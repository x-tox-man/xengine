#version 330

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct AmbientLight
{
    vec4 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

in vec4 colorVarying;
in vec2 texCoord;
in vec4 o_normal;
in vec4 ShadowCoord[3];
in DirectionalLight directional_light_out;
in float ClipSpacePosZ;
in vec3 WorldPos0;

uniform sampler2D c_texture; // base texture for indexing decals - each composant is the weight of the texture
uniform sampler2D c_texture_1; // Decal 1
uniform sampler2D c_texture_2; // Decal 2
uniform sampler2D c_texture_3; // Decal 3
uniform sampler2D d_texture;
uniform sampler2D d_texture1;
uniform sampler2D d_texture2;
uniform AmbientLight ambient_light;
uniform mat4 modelViewMatrix;
uniform float cascadeEndClipSpace[3];

layout (location = 0) out vec4 WorldPosOut; 
layout (location = 1) out vec4 DiffuseOut; 
layout (location = 2) out vec4 NormalOut;
layout (location = 3) out float ShadowOut;
layout (location = 4) out float SSAO;

float CalcShadowFactor(int CascadeIndex, vec4 LightSpacePos)
{ 
    float Depth;

    if ( CascadeIndex == 0) 
        Depth = texture( d_texture, LightSpacePos.xy).x; 
    if ( CascadeIndex == 1)
        Depth = texture( d_texture1, LightSpacePos.xy).x; 
    if ( CascadeIndex == 2) 
        Depth = texture( d_texture2, LightSpacePos.xy).x; 


    if (Depth > LightSpacePos.z + 0.001 ) 
        return 0.1;
    else 
        return 1.0; 
}

void main()
{
    float nxDir = max(0.1, dot( o_normal.xyz, directional_light_out.Direction.xyz));
    vec4 diffuse = (directional_light_out.Color) * nxDir;
    diffuse += ambient_light.Color * ambient_light.AmbientIntensity;

    vec4 decalsWeights = texture(c_texture, texCoord);

    float visibility = 0.0;

    NormalOut = o_normal;
    WorldPosOut = vec4( WorldPos0, 1.0);

    ShadowOut = 0.0;

    for (int i = 0 ; i < 3 ; i++) {

        if ( ClipSpacePosZ <= cascadeEndClipSpace[i]) {
            
            ShadowOut = CalcShadowFactor(i, ShadowCoord[i]);
            break;
        }
    }
    
    DiffuseOut = ( texture( c_texture_1, texCoord * 512.0 ) * decalsWeights.x + texture( c_texture_2, texCoord * 128.0) * decalsWeights.y + texture( c_texture_3, texCoord * 128.0) * decalsWeights.z ) * diffuse * visibility;
    DiffuseOut.a = 1.0;
}
