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

uniform AmbientLight ambient_light;

in vec4 colorVarying;
in vec4 ShadowCoord;
in vec4 o_normal;
uniform float TimeModulator;
in DirectionalLight directional_light_out;

in vec2 texCoord;

uniform sampler2D c_texture;

out vec4 colorOut;

void main()
{
    float nxDir = max(0.1, dot( o_normal.xyz, directional_light_out.Direction.xyz));
    vec4 diffuse = texture(c_texture, texCoord);// * directional_light_out.Color;// * nxDir;

    diffuse += ambient_light.Color * ambient_light.AmbientIntensity;
    
    float visibility = 1.0;
    
    //Pour le moment : texture( c_texture, ShadowCoord.xz ).x est toujours plus petit que ShadowCoord.y
    // -> Ce qui s'explique car la projection de la camera n'est pas bonne, on se retrouve avec des hauteurs qui ne sont pas correctement reprojetées dans "la perspective" de la light camera
    if ( texture( c_texture, ShadowCoord.xy ).x < ShadowCoord.y){
        visibility = 0.4;
    }
    
    colorOut = diffuse;
    colorOut.a = 0.1;
}

