#version 330

uniform sampler2D c_texture;
uniform vec4 geometryColor;

in vec2 textureCoordinates;

out vec4 colorOut;


void main() {
    
    colorOut = texture( c_texture, gl_PointCoord );
}

