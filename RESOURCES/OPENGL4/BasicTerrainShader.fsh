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
in vec4 ShadowCoord;
in DirectionalLight directional_light_out;

uniform sampler2D c_texture; // base texture for indexing decals - each composant is the weight of the texture
uniform sampler2D c_texture_1; // Decal 1
uniform sampler2D c_texture_2; // Decal 2
uniform sampler2D c_texture_3; // Decal 3
uniform sampler2D d_texture;
uniform AmbientLight ambient_light;

out vec4 colorOut;

void main()
{
    float nxDir = max(0.1, dot( o_normal.xyz, directional_light_out.Direction.xyz));
    vec4 diffuse = (directional_light_out.Color) * nxDir;
    diffuse += ambient_light.Color * ambient_light.AmbientIntensity;

    vec4 decalsWeights = texture(c_texture, texCoord);

    float visibility = 1.0;

    if ( texture( d_texture, ShadowCoord.xy ).x < (ShadowCoord.z -0.005) ) {
        visibility = 0.5;
    }
    
    colorOut = ( texture( c_texture_1, texCoord * 512.0 ) * decalsWeights.x + texture( c_texture_2, texCoord * 128.0) * decalsWeights.y + texture( c_texture_3, texCoord * 128.0) * decalsWeights.z ) * diffuse * visibility;
    colorOut.a = 1.0;
}
