#version 330

#if __SUPPORTS_DIRECTIONAL_LIGHT__
    struct DirectionalLight
    {
        vec4 Color;
        vec4 Direction;
        float AmbientIntensity;
        float DiffuseIntensity;
    };

    uniform DirectionalLight directional_light;
#endif

in vec4 colorVarying;
in vec4 o_normal;

out vec4 colorOut;

void main()
{
    float nxDir = max(0.1, dot( o_normal.xyz, directional_light.Direction.xyz));
    vec4 diffuse = directional_light.Color * nxDir;
    
    colorOut = colorVarying* 0.005f + diffuse*0.1f;
}

