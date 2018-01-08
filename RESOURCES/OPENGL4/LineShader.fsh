#version 330

in vec4 colorVarying;

out vec4 colorOut;

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

in DirectionalLight directional_light_out;

uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;


void main()
{
    colorOut = colorVarying;
}

