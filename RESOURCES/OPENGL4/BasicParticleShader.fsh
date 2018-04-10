#version 330

uniform sampler2D c_texture;
uniform vec4 geometryColor;
uniform float TimeModulator;

in float oTime;
out vec4 colorOut;


void main() {
    
    colorOut = texture( c_texture, gl_PointCoord ) * ( 1.0 - (oTime * 0.1));
}

