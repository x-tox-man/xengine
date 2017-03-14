#version 330

in vec4 colorVarying;

uniform sampler2D c_texture;

out vec4 colorOut;
in vec2 textureCoordinates;

void main()
{
    colorOut = texture( c_texture, textureCoordinates );
}

