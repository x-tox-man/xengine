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
uniform mat4 modelViewMatrix;
uniform mat4 jointsMatrix[128];
uniform mat4 attrBindShapeMatrix;
uniform vec4 geometryColor;
uniform mat4 diffuse_light;
uniform vec4 CameraWorldPosition;
uniform DirectionalLight directional_light;
uniform PointLight point_light_table[2];
uniform SpotLight spot_light_table[2];

// -- VERTEX TO PIXEL INPUT

out vec4 colorVarying;
out vec2 textureCoordinates;
out vec4 position_p;
out vec4 normal_p;
out vec3 tangent_p;
//out mat3 TBNMatrix;

out vec3 LightDirection_tangentspace;
out vec3 EyeDirection_tangentspace;



// -- VERTEX SHADER

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    mat4 blend_result = weights.x * jointsMatrix[int( joint_indices.x )];
    blend_result = blend_result + weights.y * jointsMatrix[int( joint_indices.y )];
    blend_result = blend_result + weights.z * jointsMatrix[int( joint_indices.z )];
    
    textureCoordinates = tex0;
    

    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    vec3 vertexTangent_cameraspace = mat3(modelViewMatrix) * normalize(tangent).rgb;
    vec3 vertexBitangent_cameraspace = mat3(modelViewMatrix) * normalize(bitangent).rgb;
    vec3 vertexNormal_cameraspace = mat3(modelViewMatrix) * normalize(normal).rgb;
    
    mat3 TBNMatrix = transpose(
        mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
        ));
    
    position_p = modelViewMatrix * position;
    normal_p = modelViewMatrix * normal;
    tangent_p = tangent;
    
    LightDirection_tangentspace = /*TBNMatrix * */- directional_light.Direction.xyz;
    EyeDirection_tangentspace =  TBNMatrix * CameraWorldPosition.xyz;
    
    gl_Position = position * attrBindShapeMatrix * blend_result * MVPMatrix;
}
