#version 100

uniform sampler2D c_texture;
uniform highp vec4 geometryColor;

varying vec2 textureCoordinates;

void main() {

    gl_FragColor = texture( c_texture, gl_PointCoord );
}

