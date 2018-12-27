#version 330

in vec4 position;
in vec4 normal;
in vec2 tex0;

out vec2 texCoord;

uniform mat4 MVPMatrix;

void main()
{
	gl_Position = MVPMatrix * position;
	texCoord = tex0;
}