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
in vec4 ShadowCoord[3];
in vec2 texCoord;
in mat3 TBNMatrix_p;
in float ClipSpacePosZ;

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform sampler2D d_texture;
uniform sampler2D d_texture1;
uniform sampler2D d_texture2;
uniform AmbientLight ambient_light;
uniform mediump mat4 modelViewMatrix;
uniform float cascadeEndClipSpace[3];

out vec4 colorOut;

float CalcShadowFactor(int CascadeIndex, vec4 LightSpacePos)
{ 
    float Depth;

    if ( CascadeIndex == 0) 
        Depth = texture( d_texture, LightSpacePos.xy).x; 
    if ( CascadeIndex == 1)
        Depth = texture( d_texture1, LightSpacePos.xy).x; 
    if ( CascadeIndex == 2) 
        Depth = texture( d_texture2, LightSpacePos.xy).x; 


    if (Depth > LightSpacePos.z + 0.001 ) 
        return 0.1;
    else 
        return 1.0; 
} 

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

    float visibility = 0.0;
    vec4 clcolor[3];

    clcolor[0]= vec4( 1.0, 0.3, 0.0, 1.0 );
    clcolor[1]= vec4( 0.0, 1.0, 0.0, 1.0 );
    clcolor[2]= vec4( 0.0, 0.3, 1.0, 1.0 );

    vec4 clcolorfin;

    for (int i = 0 ; i < 3 ; i++) {
        if ( ClipSpacePosZ <= cascadeEndClipSpace[i]) {
            
            visibility = CalcShadowFactor(i, ShadowCoord[i]);
            clcolorfin = clcolor[i];
            break;
        }
    }

    diffuse += ambient_light.Color * ambient_light.AmbientIntensity * visibility;
    //diffuse += clcolorfin * visibility;
    colorOut.rgb = texture( c_texture, texCoord ).rgb * diffuse.rgb;

    //colorOut.rgb = ShadowCoord[0].xyz;
    //colorOut.r = (texture( d_texture, ShadowCoord[0].xy).x - ShadowCoord[0].z);//cascadeEndClipSpace[0] - ClipSpacePosZ;//texture( d_texture, ShadowCoord[0].xy).x;//-cascadeEndClipSpace[0];
    //colorOut.g = 0.0;//-cascadeEndClipSpace[1];
    //colorOut.b = 0.0;//-cascadeEndClipSpace[2];*/
    //colorOut = clcolorfin;

    colorOut.a = 1.0;
}
