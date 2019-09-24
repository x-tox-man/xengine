#version 330

uniform sampler2D c_texture;
uniform vec4 geometryColor;
uniform float TimeModulator;


out vec4 colorOut;
in float oTime;



void main() {
    
    colorOut = texture( c_texture, gl_PointCoord ) * 0.1;


}


