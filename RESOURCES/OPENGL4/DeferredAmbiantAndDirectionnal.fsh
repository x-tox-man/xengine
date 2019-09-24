#version 330
#define M_PI 3.1415926535897932384626433832795
#define M_PI_2 (M_PI / 2)
#define LightSpecularPower 1.0

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
in vec4 EyeWorldPosition;

out vec4 colorOut;

uniform sampler2D o_texture; //Position
uniform sampler2D o_texture_1; //Diffuse
uniform sampler2D o_texture_2; //Normal
uniform sampler2D o_texture_3; //Shadow
uniform sampler2D o_texture_4; //SSAO
uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;
uniform mat4 ProjectionMatrix;

vec4 CalcDirectionalLight( DirectionalLight light, vec3 normal, vec3 Position, float specular_intensity )
{
    float DiffuseFactor = dot(normalize(vec4( normal, 1.0) ), light.Direction);

    vec4 DiffuseColor = vec4(0);
    vec4 SpecularColor = vec4(0);

    if (DiffuseFactor > 0) {

        DiffuseColor = light.Color * light.DiffuseIntensity * DiffuseFactor;
        
        vec3 VertexToEye = normalize( EyeWorldPosition.xyz - Position);
        vec3 LightReflect = normalize( reflect( light.Direction.xyz, normal ) );
        
        float SpecularFactor = dot(VertexToEye, LightReflect);
        
        if (SpecularFactor > 0) {
            SpecularFactor = pow(SpecularFactor, LightSpecularPower);
            SpecularColor = light.Color * specular_intensity * SpecularFactor;
        }
    }

    return DiffuseColor + SpecularColor;
}

void main()
{ 
    vec3 WorldPos = texture( o_texture, texCoord ).xyz;
    vec3 Color = texture( o_texture_1, texCoord ).xyz;
    vec3 Normal = texture( o_texture_2, texCoord ).xyz;
    float shadow = texture( o_texture_3, texCoord ).r;
    float ao = texture( o_texture_4, texCoord ).r;

    float specular_intensity = texture( o_texture_3, texCoord ).g;

    colorOut.rgb = Color * CalcDirectionalLight( directional_light, Normal, WorldPos, specular_intensity ).rgb * shadow + Color * ambient_light.Color.rgb * ambient_light.AmbientIntensity * ao ;
    colorOut.a = 1.0;
}