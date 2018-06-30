#version 330

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct AmbientLight
{
    vec4 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

in vec4 ShadowCoord[3];
in vec2 texCoord;
in float ClipSpacePosZ;

out vec4 colorOut;

uniform sampler2D c_texture; //Position
uniform sampler2D c_texture_1; //Normal
uniform sampler2D c_texture_2; //Diffuse
uniform sampler2D d_texture;
uniform sampler2D d_texture1;
uniform sampler2D d_texture2;
uniform float cascadeEndClipSpace[3];
uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;

vec4 CalcDirectionalLight( DirectionalLight light, vec3 normal)
{
    float DiffuseFactor = dot(normalize(vec4(normal, 1.0) ), - light.Direction);
    vec4 DiffuseColor;

    if (DiffuseFactor > 0) {
        DiffuseColor = light.Color * light.DiffuseIntensity * DiffuseFactor;
    }
    else {
        DiffuseColor = vec4(0, 0, 0, 0);
    }

    return DiffuseColor;
}

void main() 
{ 
    vec3 WorldPos = texture( c_texture, texCoord ).xyz;
    vec3 Color = texture( c_texture_1, texCoord ).xyz;
    vec3 Normal = texture( c_texture_2, texCoord ).xyz;

    Normal = normalize(Normal);

    colorOut = vec4( Color, 1.0 ) * CalcDirectionalLight( directional_light, Normal ) + vec4( Color, 1.0 ) * ambient_light.Color * ambient_light.AmbientIntensity;
    colorOut.a = 1.0;
}