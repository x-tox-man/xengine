//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 330

// -- TYPES

struct DirectionalLight
{
    vec4 Color;
    vec4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};


struct PointLight
{
    vec4 Color;
    vec4 Position;
    float AmbientIntensity;
    float DiffuseIntensity;
    
    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExp;
};

struct SpotLight
{
    PointLight Base;
    vec4 Direction;
    float Cutoff;
};

// -- VERTEX INPUT

in vec4 position;
in vec4 normal;
in vec2 tex0;
in vec3 weights;
in vec3 joint_indices;
in vec3 tangent;
in vec3 bitangent;

// -- SHADER UNIFORM

uniform mat4 MVPMatrix;
uniform mat4 jointsMatrix[128];
uniform mat4 attrBindShapeMatrix;
uniform vec4 geometryColor;
uniform mat4 diffuse_light;
uniform vec4 CameraWorldPosition;
uniform DirectionalLight directional_light;
uniform PointLight point_light_table[2];
uniform SpotLight spot_light_table[2];

// -- VERTEX TO PIXEL INPUT

// -- VERTEX SHADER

void main()
{
    mat4 blend_result = weights.x * jointsMatrix[int( joint_indices.x )];
    blend_result = blend_result + weights.y * jointsMatrix[int( joint_indices.y )];
    blend_result = blend_result + weights.z * jointsMatrix[int( joint_indices.z )];
    
    gl_Position = position * attrBindShapeMatrix * blend_result * MVPMatrix;
}
