//
//  Shader.vsh
//  AR-POC
//
//  Created by Christophe Bernard on 11/09/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#version 100

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

attribute highp vec4 position;
attribute highp vec4 normal;
attribute highp vec2 tex0;
attribute highp vec3 weights;
attribute highp vec3 joint_indices;
attribute highp vec3 tangent;
attribute highp vec3 bitangent;

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
