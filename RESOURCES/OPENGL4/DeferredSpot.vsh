#version 330 

in vec4 position;
in vec4 normal;

out vec4 EyeWorldPosition;
out vec4 LightPosition;

struct PointLight
{
    vec4 Color;
    vec4 Position;
    float AmbientIntensity;
    float DiffuseIntensity;

    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExp;
};

uniform mat4 MVPMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 geometryColor;
uniform PointLight point_light_table[1];
uniform vec4 CameraWorldPosition;

void main()
{
    LightPosition = modelViewMatrix * point_light_table[0].Position; // in world position
    EyeWorldPosition = modelViewMatrix * CameraWorldPosition; // in world position
	gl_Position = MVPMatrix * position;
}