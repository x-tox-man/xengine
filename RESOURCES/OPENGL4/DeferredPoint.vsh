#version 330 

in vec4 position;
in vec4 normal;
in vec2 tex0;
in vec3 tangent;
in vec3 bitangent;

out vec4 colorVarying;
out vec4 o_normal;
out vec4 o_position;
out vec2 texCoord;
out mat3 TBNMatrix_p;

uniform mat4 MVPMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 geometryColor;

void main()
{
    texCoord = tex0; 
	gl_Position = o_position = position * MVPMatrix;

    mat3 TBNMatrix = transpose(
        mat3(
        tangent,
        bitangent,
        normal
        ));

    TBNMatrix_p = TBNMatrix;
}