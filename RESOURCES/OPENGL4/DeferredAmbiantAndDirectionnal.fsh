#version 330
#define M_PI 3.1415926535897932384626433832795
#define M_PI_2 (M_PI / 2)

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
uniform sampler2D c_texture_1; //Diffuse
uniform sampler2D c_texture_2; //Normal
uniform sampler2D c_texture_3; //Shadow
uniform sampler2D c_texture_4; //SSAO
uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;
uniform mat4 ProjectionMatrix;

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
    float shadow = texture( c_texture_3, texCoord ).r;
    vec3 ssao = texture( c_texture_4, texCoord ).xyz;

    Normal = normalize(Normal);

    colorOut.rgb = Color * CalcDirectionalLight( directional_light, Normal ).rgb + Color * 1.0 * ambient_light.Color.rgb * ambient_light.AmbientIntensity;

    //colorOut.rgb = texture( c_texture_3, texCoord ).xyz;
    //colorOut.rgb = offset.rgb;//WorldPos;//offset.rgb;//vec3(sampleDepth,sampleDepth,sampleDepth);
    //colorOut.rgb = vec3(shadow);//ssao.xyz;
    colorOut.rgb = ssao.xyz;
    //colorOut.rgb = 1.0 * ambient_light.Color.rgb * ambient_light.AmbientIntensity * ssao;
    colorOut.a = 1.0;
}