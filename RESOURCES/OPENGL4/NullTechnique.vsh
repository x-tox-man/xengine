#version 330 

in vec4 position;
in vec4 normal;

uniform mat4 MVPMatrix;

void main()
{
	gl_Position = MVPMatrix * position;
}