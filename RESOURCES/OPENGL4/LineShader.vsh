//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 330

in vec4 position;

out vec4 colorVarying;

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

uniform DirectionalLight directional_light;
uniform AmbientLight ambient_light;

uniform mat4 MVPMatrix;
uniform vec4 geometryColor;

out DirectionalLight directional_light_out;

void main()
{
    //float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 0.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 1.0 );

    directional_light_out = directional_light;
    
    gl_Position = MVPMatrix * position;
}
