#version 100

uniform sampler2D c_texture;

varying highp vec4 colorVarying;
varying highp vec2 textureCoordinates;

void main()
{
    gl_FragColor = texture2D( c_texture, textureCoordinates ) * colorVarying;
}
