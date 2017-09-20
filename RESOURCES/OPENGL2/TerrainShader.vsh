//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 330

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

in vec4 position;
in vec4 normal;
in vec2 tex0;

uniform DirectionalLight directional_light;

out vec4 colorVarying;
out vec4 o_normal;
out DirectionalLight directional_light_out;
out vec4 ShadowCoord;
out vec2 texCoord;

uniform mat4 MVPMatrix;
uniform mat4 ShadowMapMVP;
uniform vec4 geometryColor;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    directional_light_out = directional_light;
    
    o_normal = normal;
    texCoord = tex0;
    colorVarying = position;
    
    ShadowCoord = position * ShadowMapMVP;
    gl_Position = position * MVPMatrix;
}
