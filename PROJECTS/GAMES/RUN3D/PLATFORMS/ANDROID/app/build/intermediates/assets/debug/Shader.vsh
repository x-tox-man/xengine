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
    mediump float AttenuationConstant;
    mediump float AttenuationLinear;
    mediump float AttenuationExp;
};

struct SpotLight
{
    PointLight Base;
    vec4 Direction;
    float Cutoff;
};

attribute vec4 position;
attribute vec4 normal;
attribute vec2 tex0;
attribute vec3 weights;
attribute vec3 joint_indices;
attribute vec3 tangent;
attribute vec3 bitangent;

varying highp vec4 colorVarying;
varying highp vec2 textureCoordinates;
varying highp vec4 position_p;
varying highp vec4 normal_p;
varying highp vec3 tangent_p;
varying highp mat3 TBNMatrix;

varying highp vec3 LightDirection_tangentspace;
varying highp vec3 EyeDirection_tangentspace;

uniform mat4 MVPMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 jointsMatrix[128];
uniform mat4 attrBindShapeMatrix;
uniform vec4 geometryColor;

uniform mat4 diffuse_light;
uniform vec4 CameraWorldPosition;
uniform DirectionalLight directional_light;
uniform PointLight point_light_table[2];
uniform SpotLight spot_light_table[2];

highp mat3 transpose(in highp mat3 inMatrix) {
    highp vec3 i0 = inMatrix[0];
    highp vec3 i1 = inMatrix[1];
    highp vec3 i2 = inMatrix[2];
    
    highp mat3 outMatrix = mat3(
                                vec3(i0.x, i1.x, i2.x),
                                vec3(i0.y, i1.y, i2.y),
                                vec3(i0.z, i1.z, i2.z)
                                );
    
    return outMatrix;
}

void main()
{
    float cosTheta = dot( normal,normalize(vec4( 1.0, 0.0, 0.0, 1.0) ) );
    
    highp mat4 blend_result = weights.x * jointsMatrix[int( joint_indices.x )];
    blend_result = blend_result + weights.y * jointsMatrix[int( joint_indices.y )];
    blend_result = blend_result + weights.z * jointsMatrix[int( joint_indices.z )];
    
    colorVarying = vec4( 0.4, 0.4, 0.4, 0.4 ) * cosTheta;
    
    textureCoordinates = tex0;
    
    vec3 vertexNormal_cameraspace = mat3(modelViewMatrix) * normalize( normal ).rgb;
    vec3 vertexTangent_cameraspace = mat3(modelViewMatrix) * normalize( tangent ).rgb;
    vec3 vertexBitangent_cameraspace = mat3(modelViewMatrix) * normalize( bitangent ).rgb;
    
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
