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

in DirectionalLight directional_light_out;
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

/*vec4 CalcLightInternal(PointLight point, vec3 LightDirection, vec3 Normal)
{
    vec4 AmbientColor = point.Color * point.AmbientIntensity;
    float DiffuseFactor = dot(Normal, -LightDirection);
    
    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);
    
    if (DiffuseFactor > 0) {
        
        DiffuseColor = point.Color * point.DiffuseIntensity * DiffuseFactor;
        
        vec3 VertexToEye = normalize(position_p - CameraWorldPosition).xyz;
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
    
    vec4 Color = CalcLightInternal(point, LightDirection.xyz, Normal);
    
    float Attenuation = point.AttenuationConstant +
        point.AttenuationLinear * Distance +
        point.AttenuationExp * Distance * Distance;
    
    return Color / Attenuation;
}

vec4 CalcSpotLight( SpotLight spot, vec3 Normal)
{
    vec3 LightToPixel = normalize( CameraWorldPosition - spot.Base.Position).xyz;
    float SpotFactor = dot(LightToPixel, spot.Direction.xyz);
    
    if (SpotFactor > spot.Cutoff) {
        
        vec4 Color = CalcPointLight( spot.Base, Normal);
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - spot.Cutoff));
    }
    else {
        return vec4(0,0,0,0);
    }
}

vec4 CalcDirectionalLight()
{
    
}*/

void main() 
{ 
    vec3 WorldPos = texture( c_texture, texCoord ).xyz;
    vec3 Color = texture( c_texture_2, texCoord ).xyz;
    vec3 Normal = texture( c_texture_2, texCoord ).xyz;

    Normal = normalize(Normal);

    colorOut = vec4( Color, 1.0 );// * /*CalcDirectionalLight( WorldPos, Normal ) + vec4( Color, 1.0 ) * */ ambient_light.Color * ambient_light.AmbientIntensity;
    colorOut.a = 1.0;
}