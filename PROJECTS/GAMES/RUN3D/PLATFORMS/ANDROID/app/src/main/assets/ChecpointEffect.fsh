#version 100

struct DirectionalLight
{
    mediump vec4 Color;
    mediump vec4 Direction;
    mediump float AmbientIntensity;
    mediump float DiffuseIntensity;
};

struct AmbientLight
{
    mediump vec4 Color;
    mediump float AmbientIntensity;
    mediump float DiffuseIntensity;
};

uniform mediump AmbientLight ambient_light;
uniform sampler2D c_texture;
uniform highp float TimeModulator;

varying vec4 colorVarying;
varying vec4 ShadowCoord;
varying vec4 o_normal;
varying vec2 texCoord;
varying DirectionalLight directional_light_out;

out vec4 colorOut;

void main()
{
    float nxDir = max(0.1, dot( o_normal.xyz, directional_light_out.Direction.xyz));
    vec4 diffuse = texture(c_texture, texCoord);// * directional_light_out.Color;// * nxDir;

    diffuse += ambient_light.Color * ambient_light.AmbientIntensity;
    
    colorOut = diffuse;
}

