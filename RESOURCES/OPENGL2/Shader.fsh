#version 330

// -- TYPES

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

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

// PIXEL INPUT

in vec4 colorVarying;
in vec2 textureCoordinates;
in vec4 position_p;
in vec4 normal_p;
in vec3 tangent_p;
//in mat3 TBNMatrix;
in vec3 LightDirection_tangentspace;
in vec3 EyeDirection_tangentspace;

// SHADER UNIFORM

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform vec4 CameraWorldPosition;
uniform float LightSpecularPower;
uniform float MaterialSpecularIntensity;
uniform DirectionalLight directional_light;
uniform PointLight point_light_table[2];
uniform SpotLight spot_light_table[2];

// PIXEL OUTPUT

layout(location = 0) out vec4 colorOut;

// METHODS

vec4 CalcLightInternal(PointLight point, vec3 LightDirection, vec3 Normal)
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

// FRAGMENT SHADER

void main() {
    
    vec4 norm = normal_p;
    
    texture(n_texture, textureCoordinates) * 2.0 - 1.0;
    
    vec4 baseColor = texture(c_texture, textureCoordinates);
    
    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);
    
    // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
    // http://ogldev.atspace.co.uk/www/tutorial19/tutorial19.html
    // http://ogldev.atspace.co.uk/www/tutorial26/tutorial26.html
    
    /*
     So we’ve got everything we need now. Diffuse lighting uses clamp( dot( n,l ), 0,1 ), with n and l expressed in tangent space (it doesn’t matter in which space you make your dot and cross products; the important thing is that n and l are both expressed in the same space). Specular lighting uses clamp( dot( E,R ), 0,1 ), again with E and R expressed in tangent space. Yay !
     
     */
    
    /*vec3 NewNormal;
    
    {
        vec3 Normal = normalize( normal_p.xyz );
        vec3 Tangent = normalize( tangent_p );
        
        Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
        
        vec3 Bitangent = cross(Tangent, Normal);
        vec3 BumpMapNormal = norm.xyz;
        
        mat3 TBN = mat3(Tangent, Bitangent, Normal);
        NewNormal = TBN * BumpMapNormal;
        NewNormal = normalize(NewNormal);
    }*/
    
    vec4 TotalLight = vec4( 0,0,0,1);
    
    
    {
        float DiffuseFactor = clamp( dot(norm.xyz, LightDirection_tangentspace), 0,1 );
        
        if ( DiffuseFactor > 0 ) {
            
            DiffuseColor = vec4( directional_light.Color ) * directional_light.DiffuseIntensity * DiffuseFactor;
            
            vec3 VertexToEye = normalize( CameraWorldPosition.xyz - position_p.xyz );
            
            vec3 LightReflect = normalize(reflect( LightDirection_tangentspace, norm.xyz ));
            
            float SpecularFactor = clamp( dot( VertexToEye, LightReflect ), 0,1 );
            
            if ( SpecularFactor > 0 ) {
                
                SpecularFactor = pow( SpecularFactor, LightSpecularPower );
                SpecularColor = vec4( directional_light.Color * MaterialSpecularIntensity * SpecularFactor);
            }
        }
    }
    
    TotalLight = DiffuseColor + SpecularColor;
    
    int gNumPointLights = 2;
    
    for (int i = 0 ; i < gNumPointLights ; i++) {
        
        TotalLight += CalcPointLight(point_light_table[i], normal_p.xyz);
    }
    
    for (int i = 0 ; i < gNumPointLights ; i++) {
        
        TotalLight += CalcSpotLight(spot_light_table[i], normal_p.xyz);
    }
    
    colorOut.rgb = vec3(1.0, 1.0, 1.0); //baseColor.rgb * TotalLight.rgb;
    
    
    colorOut.a = 1.0;//baseColor.a;
}
