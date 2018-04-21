#version 100

struct DirectionalLight
{
    mediump vec4 Color;
    mediump vec4 Direction;
    mediump float AmbientIntensity;
    mediump float DiffuseIntensity;
};

struct AmbientLight
{
    mediump vec4 Color;
    mediump float AmbientIntensity;
    mediump float DiffuseIntensity;
};

varying mediump vec4 colorVarying;
varying mediump vec2 texCoord;
varying mediump vec4 o_normal;

uniform sampler2D c_texture; // base texture for indexing decals - each composant is the weight of the texture
uniform sampler2D c_texture_1; // Decal 1
uniform sampler2D c_texture_2; // Decal 2
uniform sampler2D c_texture_3; // Decal 3
uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;

void main()
{
    mediump vec4 colorOut = vec4(0.0, 0.0, 0.0, 1.0 );
    mediump float nxDir = max(0.1, dot( o_normal.xyz, directional_light.Direction.xyz));
    mediump vec4 diffuse = (directional_light.Color) * nxDir;
    diffuse += ambient_light.Color * ambient_light.AmbientIntensity;

    mediump vec4 decalsWeights = texture2D(c_texture, texCoord);
    
    if ( decalsWeights.x > 0.0 ) {
        colorOut += texture2D( c_texture_1, texCoord * 512.0 ) * decalsWeights.x;
    }
    if ( decalsWeights.z > 0.0 ) {
        colorOut += texture2D( c_texture_2, texCoord * 512.0 ) * decalsWeights.y;
    }
    if ( decalsWeights.z > 0.0 ) {
        colorOut += texture2D( c_texture_3, texCoord * 512.0 ) * decalsWeights.z;
    }

    gl_FragColor = colorOut;
    colorOut.a = 1.0;
}
