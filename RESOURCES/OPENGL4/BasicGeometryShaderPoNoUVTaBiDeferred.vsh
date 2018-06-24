#version 330 

in vec4 position;
in vec4 normal;
in vec2 tex0;
in vec3 tangent;
in vec3 bitangent;

out vec4 colorVarying;
out vec4 o_normal;
out vec2 texCoord;
out mat3 TBNMatrix_p;
out vec3 WorldPos0;

uniform mat4 MVPMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 geometryColor;

void main()
{
	texCoord = tex0; 
	o_normal = (normal * modelViewMatrix); 
	WorldPos0 = (position * modelViewMatrix).xyz;

    colorVarying = geometryColor;
	gl_Position = position * MVPMatrix;

    mat3 TBNMatrix = transpose(
        mat3(
        tangent,
        bitangent,
        normal
        ));

    TBNMatrix_p = TBNMatrix;
}