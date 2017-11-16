#version 100

uniform sampler2D c_texture;
uniform sampler2D n_texture;

varying highp vec4 colorVarying;
varying highp vec2 textureCoordinates;
varying highp vec3 lightvec;
varying highp vec4 position_p;

varying highp vec3 tangent_p;
varying highp vec3 bitangent_p;

void main()
{
    highp vec3 norm = texture2D(n_texture, textureCoordinates).rgb * 2.0 - 1.0;
    highp vec4 baseColor = texture2D(c_texture, textureCoordinates);
    
    highp float dist = 500.0;
    
    highp vec3 lightVector = normalize( vec3(0,0,1) );
    highp float nxDir = max(0.1, dot(norm, vec3(0,0,1)));
    highp vec4 diffuse = vec4(0.4,0.4,0.4,1) * nxDir;
    diffuse.a = 1.0;
    
    highp float specularPower = 0.0;
    
    if(nxDir != 0.0)
    {
        highp vec3 cameraVector = normalize(vec3(0,0,1) - position_p.xyz);
        highp vec3 halfVector = normalize(lightVector + cameraVector);
        highp float nxHalf = max(0.0,dot(norm, halfVector));
        specularPower = pow(nxHalf, 0.2);
    }
    
    highp vec3 specular = vec3(0.3,0.3,0.3) * specularPower;
    
    highp vec4 colorOut;
    
    colorOut.rgb = (diffuse.rgb * baseColor.rgb);//+specular;
    colorOut.a = baseColor.a;
    
    gl_FragColor = colorOut;
}



