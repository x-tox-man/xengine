#version 330

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

in vec2 texCoord;
in vec4 o_position;
out vec4 colorOut;

uniform sampler2D c_texture; //Position
uniform sampler2D c_texture_1; //Normal
uniform sampler2D c_texture_2; //Diffuse
uniform PointLight point_light;
uniform vec4 CameraWorldPosition;
uniform float LightSpecularPower;
uniform float MaterialSpecularIntensity;

vec4 CalcLightInternal(PointLight point, vec3 LightDirection, vec3 Normal )
{
    vec4 AmbientColor = point.Color * point.AmbientIntensity;
    float DiffuseFactor = dot(Normal, -LightDirection);
    
    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);
    
    if (DiffuseFactor > 0) {
        
        DiffuseColor = point.Color * point.DiffuseIntensity * DiffuseFactor;
        
        vec3 VertexToEye = normalize( o_position - CameraWorldPosition).xyz;
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        
        float SpecularFactor = dot(VertexToEye, LightReflect);
        
        if (SpecularFactor > 0) {
            SpecularFactor = pow(SpecularFactor, LightSpecularPower);
            SpecularColor = point.Color * MaterialSpecularIntensity * SpecularFactor;
        }
    }
    
    return (AmbientColor + DiffuseColor + SpecularColor);
}

vec4 CalcPointLight(PointLight point, vec3 Normal)
{
    vec4 LightDirection = CameraWorldPosition - point.Position;
    
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);
    
    vec4 Color = CalcLightInternal( point, LightDirection.xyz, Normal );
    
    float Attenuation = point.AttenuationConstant +
        point.AttenuationLinear * Distance +
        point.AttenuationExp * Distance * Distance;
    
    return Color / Attenuation;
}

void main()
{ 
    vec3 WorldPos = texture( c_texture, texCoord ).xyz;
    vec3 Color = texture( c_texture_1, texCoord ).xyz;
    vec3 Normal = texture( c_texture_2, texCoord ).xyz;

    Normal = normalize(Normal);

    colorOut = vec4( Color, 1.0 ) * CalcPointLight( point_light, Normal );
    colorOut.a = 1.0;
}