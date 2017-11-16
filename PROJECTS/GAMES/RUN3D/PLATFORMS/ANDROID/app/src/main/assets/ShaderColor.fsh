#version 100

varying highp vec4 colorVarying;
varying highp vec2 textureCoordinates;

uniform highp vec4 geometryColor;

void main()
{
    gl_FragColor = colorVarying * geometryColor;
}

