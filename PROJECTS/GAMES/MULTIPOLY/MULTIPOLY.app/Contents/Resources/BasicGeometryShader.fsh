#version 330

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

in vec4 colorVarying;
in vec4 ShadowCoord;
in vec4 o_normal;
in DirectionalLight directional_light_out;

uniform sampler2D d_texture;

out vec4 colorOut;

void main()
{
    float nxDir = max(0.1, dot( o_normal.xyz, directional_light_out.Direction.xyz));
    vec4 diffuse = directional_light_out.Color * nxDir;
    
    float visibility = 1.0;
    
    //Pour le moment : texture( d_texture, ShadowCoord.xz ).x est toujours plus petit que ShadowCoord.y
    // -> Ce qui s'explique car la projection de la camera n'est pas bonne, on se retrouve avec des hauteurs qui ne sont pas correctement reprojetées dans "la perspective" de la light camera
    if ( texture( d_texture, ShadowCoord.xy ).x < ShadowCoord.y){
        visibility = 0.4;
    }
    
    colorOut.x = texture( d_texture, ShadowCoord.xy ).x;//texture( d_texture, ShadowCoord.xz ).x;//ShadowCoord.x;//texture( d_texture, ShadowCoord.xz ).x;
    colorOut.y = 0.0;//texture( d_texture, ShadowCoord.xz ).x - ShadowCoord.y;//texture( d_texture, ShadowCoord.xz ).x;//ShadowCoord.y;//ShadowCoord.y;//0.0;//ShadowCoord.y;
    colorOut.z = 0.0;//ShadowCoord.z;
    //colorOut.xy = ShadowCoord.xz;
    colorOut.a = 1.0;
}

