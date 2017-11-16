#version 100

uniform sampler2D c_texture;
uniform highp vec4 geometryColor;

void main() {

    gl_FragColor = texture2D( c_texture, gl_PointCoord );
}

