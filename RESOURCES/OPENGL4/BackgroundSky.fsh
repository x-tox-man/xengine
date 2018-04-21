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
in vec2 texCoord;
in mat3 TBNMatrix_p;

uniform sampler2D c_texture;
uniform sampler2D n_texture;
uniform AmbientLight ambient_light;
uniform mediump mat4 modelViewMatrix;

out vec4 colorOut;

void main()
{
    float nxDir = max(0.1, dot( o_normal.xyz, directional_light_out.Direction.xyz));
    vec4 diffuse = directional_light_out.Color * nxDir;
    diffuse += ambient_light.Color * ambient_light.AmbientIntensity;
    
    colorOut.rgb = texture( c_texture, texCoord ).rgb * diffuse.rgb;

    colorOut.a = 1.0;
}
