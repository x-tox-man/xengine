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
    

    colorOut = diffuse;
    colorOut.a = diffuse.a;
}

