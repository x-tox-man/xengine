#version 100

// -- TYPES

struct DirectionalLight
{
    mediump vec4 Color;
    mediump vec4 Direction;
    mediump float AmbientIntensity;
    mediump float DiffuseIntensity;
};

struct PointLight
{
    mediump vec4 Color;
    mediump vec4 Position;
    mediump float AmbientIntensity;
    mediump float DiffuseIntensity;

    mediump float AttenuationConstant;
    mediump float AttenuationLinear;
    mediump float AttenuationExp;
};

struct SpotLight
{
    PointLight Base;
    mediump vec4 Direction;
    mediump float Cutoff;
};

// PIXEL INPUT

varying mediump vec4 colorVarying;
varying mediump vec2 textureCoordinates;
varying mediump vec4 position_p;
varying mediump vec4 normal_p;
varying mediump vec3 tangent_p;
varying mediump mat3 TBNMatrix;
varying mediump vec3 LightDirection_tangentspace;
varying mediump vec3 EyeDirection_tangentspace;

// SHADER UNIFORM

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform mediump vec4 CameraWorldPosition;
uniform mediump float LightSpecularPower;
uniform mediump float MaterialSpecularIntensity;
uniform DirectionalLight directional_light;
uniform PointLight point_light_table[2];
uniform SpotLight spot_light_table[2];

// METHODS

mediump vec4 CalcLightInternal(PointLight point, mediump vec3 LightDirection, mediump vec3 Normal)
{
    mediump vec4 AmbientColor = point.Color * point.AmbientIntensity;
    mediump float DiffuseFactor = dot(Normal, -LightDirection);
    
    mediump vec4 DiffuseColor = vec4(0, 0, 0, 0);
    mediump vec4 SpecularColor = vec4(0, 0, 0, 0);
    
    if (DiffuseFactor > 0.0 ) {
        
        DiffuseColor = point.Color * point.DiffuseIntensity * DiffuseFactor;
        
        mediump vec3 VertexToEye = normalize(position_p - CameraWorldPosition).xyz;
        mediump vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        
        mediump float SpecularFactor = dot(VertexToEye, LightReflect);
        
        if ( SpecularFactor > 0.0 ) {
            SpecularFactor = pow(SpecularFactor, LightSpecularPower);
            SpecularColor = point.Color * MaterialSpecularIntensity * SpecularFactor;
        }
    }
    
    return (AmbientColor + DiffuseColor + SpecularColor);
}

mediump vec4 CalcPointLight(PointLight point, mediump vec3 Normal)
{
    mediump vec4 LightDirection = CameraWorldPosition - point.Position;
    
    mediump float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);
    
    mediump vec4 Color = CalcLightInternal(point, LightDirection.xyz, Normal);
    
    mediump float Attenuation = point.AttenuationConstant +
        point.AttenuationLinear * Distance +
        point.AttenuationExp * Distance * Distance;
    
    return Color / Attenuation;
}

mediump vec4 CalcSpotLight( SpotLight spot, mediump vec3 Normal)
{
    mediump vec3 LightToPixel = normalize( CameraWorldPosition - spot.Base.Position).xyz;
    mediump float SpotFactor = dot(LightToPixel, spot.Direction.xyz);
    
    if (SpotFactor > spot.Cutoff) {
        
        mediump vec4 Color = CalcPointLight( spot.Base, Normal);
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - spot.Cutoff));
    }
    else {
        return vec4(0,0,0,0);
    }
}

// FRAGMENT SHADER

void main()
{
    mediump vec3 norm = texture2D(n_texture, textureCoordinates).rgb * 2.0 - 1.0;
    mediump vec4 baseColor = texture2D(c_texture, textureCoordinates);
    
    mediump float dist = 500.0;
    
    mediump vec3 lightVector = normalize( vec3(0,0,1) );
    mediump float nxDir = max(0.1, dot(norm, vec3(0,0,1)));
    mediump vec4 diffuse = vec4(0.4,0.4,0.4,1) * nxDir;
    diffuse.a = 1.0;
    
    mediump float specularPower = 0.0;
    
    if(nxDir != 0.0)
    {
        mediump vec3 cameraVector = normalize(vec3(0,0,1) - position_p.xyz);
        mediump vec3 halfVector = normalize(lightVector + cameraVector);
        mediump float nxHalf = max(0.0,dot(norm, halfVector));
        specularPower = pow(nxHalf, 0.2);
    }
    
    mediump vec3 specular = vec3(0.3,0.3,0.3) * specularPower;
    
    mediump vec4 colorOut;
    
    colorOut.rgb = (diffuse.rgb * baseColor.rgb);//+specular;
    colorOut.a = baseColor.a;
    
    gl_FragColor = colorOut;
}



