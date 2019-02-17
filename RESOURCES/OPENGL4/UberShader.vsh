//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 330

// VERTEX INPUT

#if __POSITION__ENABLED__
    in vec4 position;
#endif

#if __NORMAL__ENABLED__
    in vec4 normal;
#endif

#if __BLEND3_ENABLED
    in vec3 weights;
    in vec3 joint_indices;
#else if __BLEND4_ENABLED
    in vec4 weights;
    in vec4 joint_indices;
#endif

#if __TEX0_ENABLED__
    in vec2 tex0;
#endif
#if __TEX1_ENABLED__
    in vec2 tex1;
#endif
#if __TEX2_ENABLED
    in vec2 tex2;
#endif
#if __TEX3_ENABLED
    in vec2 tex3;
#endif
#if __TEX4_ENABLED
    in vec2 tex4;
#endif
#if __TEX5_ENABLED
    in vec2 tex5;
#endif
#if __TEX6_ENABLED
    in vec2 tex6;
#endif
#if __TEX7_ENABLED
    in vec2 tex7;
#endif

#if __NORMAL_MAPPING_ENABLED__
    in vec3 tangent;
    in vec3 bitangent;
#endif

// UNIFORMS

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


uniform mat4 MVPMatrix;

#if __SUPPORTS_GEOMETRY_COLOR__
uniform vec4 geometryColor;
#endif

// VERTEX OUTPUT

out vec4 colorVarying;
out vec4 o_normal;

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 0.0) ) );
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    o_normal = normal;
    
    colorVarying = position;
    
    gl_Position = MVPMatrix * position;
}
