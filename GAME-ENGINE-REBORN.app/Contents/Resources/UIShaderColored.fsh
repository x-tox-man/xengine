#version 330

uniform sampler2D c_texture;

in vec4 colorVarying;

out vec4 colorOut;


void main() {
    
    colorOut = colorVarying;
}

