#version 100

varying highp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}

