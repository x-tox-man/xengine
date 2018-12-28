#version 330 

in vec4 position;
in vec4 normal;

out vec4 EyeWorldPosition;
out vec4 LightPosition;
out vec4 iLightDirection;

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

struct SpotLight
{
    PointLight Base;
    vec4 Direction;
    float Cutoff;
};

uniform mat4 MVPMatrix;
uniform mat4 ModelMatrix;
uniform vec4 geometryColor;
uniform SpotLight spot_light_table[1];
uniform vec4 CameraWorldPosition;

void main()
{
    LightPosition = ModelMatrix * spot_light_table[0].Base.Position; // in world position
    EyeWorldPosition = ModelMatrix * CameraWorldPosition; // in world position
	gl_Position = MVPMatrix * position;
    iLightDirection = MVPMatrix * spot_light_table[0].Direction;
}