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

in vec4 colorVarying;
in vec4 o_normal;
in DirectionalLight directional_light_out;
in vec4 ShadowCoord;
in vec2 texCoord;
in mat3 TBNMatrix_p;

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform sampler2D d_texture;
uniform AmbientLight ambient_light;
uniform mediump mat4 modelViewMatrix;

out vec4 colorOut;

void main()
{
    vec4 normalTimesLModel = modelViewMatrix * o_normal;

    //-------- NORMAL MAPPING BEGIN
    vec3 BumpMapNormal = texture(n_texture, texCoord).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);

    vec3 NewNormal;

    NewNormal = TBNMatrix_p * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    //-------- NORMAL MAPPING END

    float nxDir = max(0.1, dot( NewNormal.xyz, directional_light_out.Direction.xyz));
    vec4 diffuse = directional_light_out.Color * nxDir;
    
    
    float visibility = 1.0;

    if ( texture( d_texture, ShadowCoord.xy ).x < (ShadowCoord.z -0.005) ) {
        visibility = 0.5;
    }

    diffuse += ambient_light.Color * ambient_light.AmbientIntensity * visibility;
    

    colorOut.rgb = texture( c_texture, texCoord ).rgb * diffuse.rgb;

    colorOut.a = 1.0;
}
