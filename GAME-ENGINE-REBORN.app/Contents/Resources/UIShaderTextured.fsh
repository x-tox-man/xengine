#version 330

uniform sampler2D c_texture;

in vec2 textureCoordinates;
in vec4 colorVarying;

out vec4 colorOut;


void main() {
    
    colorOut = texture( c_texture, textureCoordinates );
}

