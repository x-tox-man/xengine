#version 100

uniform sampler2D c_texture;

varying highp vec4 colorVarying;
varying highp vec2 textureCoordinates;
uniform highp vec4 geometryColor;

void main()
{
    gl_FragColor = texture2D( c_texture, textureCoordinates ) * geometryColor;
}
