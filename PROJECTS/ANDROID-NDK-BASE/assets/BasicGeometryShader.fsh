#version 100

struct DirectionalLight
{
    highp vec4 Color;
    highp vec4 Direction;
    highp float AmbientIntensity;
    highp float DiffuseIntensity;
};

varying highp vec4 colorVarying;
varying highp vec4 o_normal;

uniform highp vec4 geometryColor;

uniform DirectionalLight directional_light;

void main()
{
	highp float nxDir = max(0.1, dot( o_normal.xyz, directional_light	.Direction.xyz));
    highp vec4 diffuse = directional_light.Color * nxDir;

    gl_FragColor = colorVarying * geometryColor;
}

