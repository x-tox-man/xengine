#version 410 core

in vec4 position;
in vec4 normal;
in vec2 tex0;
in vec3 tangent;
in vec3 bitangent;

uniform mat4 MVPMatrix;

void main()
{
	gl_Position = MVPMatrix * position;
}