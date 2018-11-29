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

struct SpotLight
{
    PointLight Base;
    vec4 Direction;
    float Cutoff;
};

in vec4 EyeWorldPosition;
in vec4 LightPosition;
in vec4 iLightDirection;

out vec4 colorOut;

uniform sampler2D c_texture; //Position
uniform sampler2D c_texture_1; //Diffuse
uniform sampler2D c_texture_2; //Normal
uniform sampler2D c_texture_3; //Shadow
uniform sampler2D c_texture_4; //SSAO
uniform SpotLight spot_light_table[1];
uniform vec4 CameraWorldPosition;
uniform float LightSpecularPower;
uniform float MaterialSpecularIntensity;

vec2 CalcTexCoord()
{
   return gl_FragCoord.xy / vec2(1024.0, 768.0);
}

vec4 CalcLightInternal(PointLight point, vec3 LightDirection, vec3 Normal, vec3 Position )
{
    vec4 AmbientColor = point.Color * point.AmbientIntensity;
    float DiffuseFactor = dot(Normal, -LightDirection);
    
    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);
    
    if (DiffuseFactor > 0) {
        
        DiffuseColor = point.Color * point.DiffuseIntensity * DiffuseFactor;
        
        vec3 VertexToEye = normalize( EyeWorldPosition.xyz - Position);
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        
        float SpecularFactor = dot(VertexToEye, LightReflect);
        
        if (SpecularFactor > 0) {
            SpecularFactor = pow(SpecularFactor, LightSpecularPower);
            SpecularColor = point.Color * MaterialSpecularIntensity * SpecularFactor;
        }
    }
    
    return DiffuseColor + SpecularColor;
}

vec4 CalcPointLight( vec3 WorldPos, PointLight point, vec3 Normal)
{
    vec3 LightDirection = WorldPos.xyz - spot_light_table[0].Base.Position.xyz;
    
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

    vec4 color_l = CalcLightInternal( point, LightDirection.xyz, Normal, WorldPos );

    float Attenuation = point.AttenuationConstant +
        point.AttenuationLinear * Distance +
        point.AttenuationExp * Distance * Distance;

    return color_l / Attenuation;
}

vec4 CalcSpotLight(vec3 WorldPos, SpotLight l, vec3 Normal)
{
    vec3 LightToPixel = normalize(WorldPos.xyz - spot_light_table[0].Base.Position.xyz);
    float SpotFactor = dot(LightToPixel, spot_light_table[0].Direction.xyz);

    if (SpotFactor > l.Cutoff) {
        vec4 Color = CalcPointLight(WorldPos, l.Base, Normal);
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));
        //return vec4(spot_light_table[0].Base.Position.xyz, 1.0);
    }
    else {
        //return vec4(SpotFactor);
        return vec4(0.0);
    }
}

void main()
{ 
    vec2 tx = CalcTexCoord();
    vec3 WorldPos = texture( c_texture, tx ).xyz;
    vec3 Color = texture( c_texture_1, tx ).xyz;
    vec3 Normal = texture( c_texture_2, tx ).xyz;
    float shadow = texture( c_texture_3, tx ).r;
    vec3 ssao = texture( c_texture_4, tx ).xyz;

    colorOut.xyz = Color * CalcSpotLight( WorldPos, spot_light_table[0], normalize(Normal) ).xyz;
    colorOut.a = 1.0;
}
