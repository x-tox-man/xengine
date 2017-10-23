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
in vec4 o_normal;
in DirectionalLight directional_light_out;
in vec4 ShadowCoord;
in vec2 texCoord;

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform sampler2D d_texture;
uniform AmbientLight ambient_light;

out vec4 colorOut;

void main()
{
    float nxDir = max(0.1, dot( o_normal.xyz, directional_light_out.Direction.xyz));
    vec4 diffuse = directional_light_out.Color * nxDir;
    diffuse += ambient_light.Color * ambient_light.AmbientIntensity;
    
    float visibility = 1.0;

    if ( texture( d_texture, ShadowCoord.xy ).x < (ShadowCoord.z -0.005) ) {
        visibility = 0.5;
    }
    
    //colorOut.x = texture( d_texture, ShadowCoord.xy ).x;//texture( d_texture, ShadowCoord.xz ).x;//ShadowCoord.x;//texture( d_texture, ShadowCoord.xz ).x;
    //colorOut.y = 0.0;//texture( d_texture, ShadowCoord.xz ).x - ShadowCoord.y;//texture( d_texture, ShadowCoord.xz ).
    
    colorOut.rgb = texture( c_texture, texCoord ).rgb * diffuse.rgb;

    colorOut.a = texture( c_texture, texCoord ).a;
}
