//
//  Shaders.metal
//  TestMetalMac
//
//  Created by Christophe Bernard on 08/07/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

// File for Metal kernel and shader functions

#include <metal_stdlib>
#include <simd/simd.h>

// Including header shared between this Metal shader code and Swift/C code executing Metal API commands
#import "METAL_SHADER_TYPES.h"

using namespace metal;

typedef struct
{
    float3 position [[attribute(VertexAttributePosition)]];
    float2 texCoord [[attribute(VertexAttributeTexcoords)]];
} VertexPosColor;

typedef struct
{
    float4 position [[attribute(VertexAttributePosition)]];
    float4 normal [[attribute(VertexAttributeNormal)]];
    float2 texcoords [[attribute(VertexAttributeTexcoords)]];
} VertexPosNormalTex;

typedef struct
{
    float4 position [[attribute(VertexAttributePosition)]];
    float4 normal [[attribute(VertexAttributeNormal)]];
} VertexPosNormal;

typedef struct
{
    float4 position [[attribute(VertexAttributePosition)]];
    float4 normal [[attribute(VertexAttributeNormal)]];
    float2 texcoords [[attribute(VertexAttributeTexcoords)]];
    float3 tangent [[attribute(VertexAttributeTangent)]];
    float3 bitangent [[attribute(VertexAttributeBitangent)]];
} VertexPosNormalTexTanBi;

typedef struct
{
    float4 position [[attribute(VertexAttributePosition)]];
    float4 normal [[attribute(VertexAttributeNormal)]];
    float2 texcoords [[attribute(VertexAttributeTexcoords)]];
    float3 tangent [[attribute(VertexAttributeTangent)]];
    float3 bitangent [[attribute(VertexAttributeBitangent)]];
    float4 weights [[attribute(VertexAttributeSkinWeight)]];
    float4 joint_indices [[attribute(VertexAttributeJointIndices)]];
} VertexPosNormalTexTanBiWeJoIn;

typedef struct
{
    float4 position [[position]];
    float2 texCoord;
} ColorInOut;

typedef struct
{
    float4 Color;
    float4 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
} DirectionalLight;

typedef struct
{
    float4 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
} AmbientLight;

typedef struct {
    
    float4 Color;
    float4 Position;
    float AmbientIntensity;
    float DiffuseIntensity;
    float Exp;
    float Linear;
    float Constant;
} PointLight;

typedef struct {
    
    float4 Color;
    float4 Position;
    float4 Direction;
    float4 Orientation;
    float Cutoff;
    float AmbientIntensity; //Goes to material?
    float DiffuseIntensity;
    float Exp;
    float Linear;
    float Constant;
} SpotLight;

// ------------------------------------------------------
// functions
// ------------------------------------------------------

float CalcShadowFactor(float3 normal, float3 directional_light, float4 LightSpacePos[4], texture2d<float> depth_texture[4], sampler texture_sampler, const float cascadeEndClipSpace[4], float ClipSpacePosZ)
{
    float Depth = 1.0;
    
    if ( dot( normal, directional_light ) > 0.0 ) {
        
        for (int i = 0 ; i < 4 ; i++) {

            if ( ClipSpacePosZ <= cascadeEndClipSpace[i] ) {
                
                float3 ProjCoords = LightSpacePos[i].xyz / LightSpacePos[i].w;

                Depth = depth_texture[ i ].sample(texture_sampler, ProjCoords.xy).x;

                if (Depth > ProjCoords.z + 0.001 )
                    return 0.01;
                else
                    return 1.0;
            }
        }
    }

    return 1.0;
}

float3 ComputeNormalMapping( float3x3 TBNMatrix_p, float3 base_normal ) {
    
    base_normal = 2.0 * base_normal - float3( 1.0, 1.0, 1.0 );

    float3 final_normal;

    final_normal = TBNMatrix_p * base_normal;
    final_normal = normalize( final_normal );
    
    return final_normal;
}

float4 CalcDirectionalLight( float4 color, float3 light_direction, float3 normal, float3 world_position, float3 eye_world_position, float specular_power, float diffuse_intensity )
{
    float diffuse_factor = dot( normal, -light_direction );
    
    float4 diffuse_color = float4(0, 0, 0, 0);
    float4 specular_color = float4(0, 0, 0, 0);
    
    if ( diffuse_factor > 0 ) {
        
        diffuse_color = color * diffuse_intensity * diffuse_factor;
        
        float3 vertex_to_eye = normalize( eye_world_position - world_position );
        float3 light_reflect = normalize( reflect( light_direction, normal) );
        
        float specular_factor = dot( vertex_to_eye, light_reflect );
        
        if ( specular_factor > 0 ) {
            
            specular_factor = pow( specular_factor, specular_power );
            specular_color = color * specular_power * specular_factor;
        }
    }

    return diffuse_color + specular_color;
}

float4 CalcPointLight( float4 color, float3 normal, float3 world_pos, float3 eye_world_position, float3 light_position, float specular_power, float diffuse_intensity, float light_constant, float light_linear, float light_exp )
{
    float3 light_direction = world_pos - light_position;
    
    float light_distance = length( light_direction );
    light_direction = normalize( light_direction );

    float4 color_l = CalcDirectionalLight( color, light_direction, normal, world_pos, eye_world_position, specular_power, diffuse_intensity );

    float attenuation = light_constant +
        light_linear * light_distance +
        light_exp * light_distance * light_distance;

    return (color_l / attenuation);
}

float4 CalcSpotLight(float3 world_pos, float3 eye_world_position, SpotLight light, float3 normal, float specular_power)
{
    float3 light_to_pixel = normalize( world_pos - light.Position.xyz);
    float spot_factor = dot( light_to_pixel, -light.Direction.xyz );

    if ( spot_factor > light.Cutoff) {
        
        float4 color = CalcPointLight( light.Color, normal, world_pos.xyz, eye_world_position, light.Position.xyz, specular_power, light.DiffuseIntensity, light.Constant, light.Linear, light.Exp );
        return color * ( 1.0 - (1.0 - spot_factor ) * 1.0/(1.0 - light.Cutoff));
    }
    else {
        return float4(0.0);
    }
}

// ------------------------------------------------------
// Default shader
// ------------------------------------------------------
vertex ColorInOut vertexShader(VertexPosColor in [[stage_in]],
                               constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    ColorInOut out;

    out.position = uniforms.MVPMatrix * float4( in.position, 1.0 );
    out.texCoord = in.texCoord;

    return out;
}

fragment float4 fragmentShader(ColorInOut in [[stage_in]],
                               constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                               texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);

    half4 colorSample   = colorMap.sample(colorSampler, in.texCoord.xy);

    return float4(colorSample);
}

// ------------------------------------------------------
// Background Sky
// ------------------------------------------------------

// ------------------------------------------------------
// Background Sky Deferred
// ------------------------------------------------------

// ------------------------------------------------------
// BasicGeometryShader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
} BasicGeometryShader_ColorInOut;

vertex BasicGeometryShader_ColorInOut BasicGeometryShader_vs(VertexPosNormalTexTanBi in [[stage_in]],
                               constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicGeometryShader_ColorInOut out;
    
    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;

    return out;
}

fragment float4 BasicGeometryShader_fs(BasicGeometryShader_ColorInOut in [[stage_in]],
                               constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    half4 colorSample   = colorMap.sample(colorSampler, in.texcoords.xy);

    return float4(colorSample);
}

typedef struct
{
    float4 position [[position]];
    float4 wposition;
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
    float3 LightDirection_tangentspace;
    float3 EyeDirection_tangentspace;
    float4 ShadowCoord1;
    float4 ShadowCoord2;
    float4 ShadowCoord3;
    float ClipSpacePosZ;
} BasicShaderDeferred_InOut;

vertex BasicShaderDeferred_InOut BasicGeometryShaderDeferred_vs(VertexPosNormalTexTanBi in [[stage_in]],
                               constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicShaderDeferred_InOut out;
    
    out.T = (uniforms.ModelMatrix * normalize( float4(in.tangent, 1.0 ))).xyz;
    out.B = (uniforms.ModelMatrix * normalize( float4(in.bitangent, 1.0 ))).xyz;
    out.N = (uniforms.ModelMatrix * normalize( in.normal )).xyz;
    
    out.ShadowCoord1 = uniforms.ShadowMapMVP1 * in.position;
    out.ShadowCoord2 = uniforms.ShadowMapMVP2 * in.position;
    out.ShadowCoord3 = uniforms.ShadowMapMVP3 * in.position;
    
    out.position = uniforms.MVPMatrix * in.position;
    out.wposition = uniforms.ModelMatrix * in.position;
    out.texcoords = in.texcoords;
    
    out.ClipSpacePosZ = out.position.z;

    return out;
}

fragment GBufferDataFragmentOut BasicGeometryShaderDeferred_fs(BasicShaderDeferred_InOut in [[stage_in]],
                                 constant AnimatedObjectUniforms & uniforms [[ buffer( BufferIndexUniforms ) ]],
                                 constant DirectionalLight & dir_light [[ buffer( BufferIndexDirectionalLightsConstants ) ]],
                                 constant AmbientLight & ambient_light [[ buffer( BufferIndexAmbientLightConstants ) ]],
                                 constant Material & material [[ buffer( MaterialUniforms ) ]],
                                 texture2d<float> colorMap     [[ texture( TextureIndex1Color ) ]],
                                 texture2d<float> normalMap     [[ texture( TextureIndex2Color ) ]],
                                 texture2d<float> cascade1Map     [[ texture( TextureIndex3Color ) ]],
                                 texture2d<float> cascade2Map     [[ texture( TextureIndex4Color ) ]],
                                 texture2d<float> cascade3Map     [[ texture( TextureIndex5Color ) ]] )
{
    GBufferDataFragmentOut out;
    
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    texture2d<float> shadow_texture_array[4] =  {cascade1Map, cascade2Map, cascade3Map, cascade3Map};
    float4 shadow_coord_table[4] = {in.ShadowCoord1, in.ShadowCoord2, in.ShadowCoord3, in.ShadowCoord3 };
    //float end_clip_space_table[4] = {uniforms.cascadeEndClipSpace[0], uniforms.cascadeEndClipSpace[1], uniforms.cascadeEndClipSpace[2], uniforms.cascadeEndClipSpace[3] };
    float end_clip_space_table[4] = {10.0, 100.0, 1000.0, 10000.0};
    
    float4 colorSample = colorMap.sample(colorSampler, in.texcoords.xy);
    float4 base_normal = normalMap.sample(colorSampler, in.texcoords.xy);
    
    float3x3 TBN = float3x3( in.T, in.B, in.N );
    
    out.Position = in.wposition;
    out.Diffuse = colorSample;
    out.Normal = float4( ComputeNormalMapping( TBN, float3( base_normal.xyz ) ), 1.0 );
    out.Specular = 0.0;
    out.Specular.w = 1.0;
    out.Specular.r = CalcShadowFactor(out.Normal.xyz, dir_light.Direction.xyz, shadow_coord_table, shadow_texture_array, colorSampler, end_clip_space_table, in.ClipSpacePosZ );//shadow
    
    return out;
}

// ------------------------------------------------------
// Simple Blur Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
} SimpleBlur_ColorInOut;


vertex BasicGeometryShader_ColorInOut SimpleBlur_vs(VertexPosNormalTexTanBi in [[stage_in]],
                               constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicGeometryShader_ColorInOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;

    return out;
}

fragment float4 SimpleBlur_fs(SimpleBlur_ColorInOut in [[stage_in]],
                               constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    constexpr float Offsets[4] = { -1.5, -0.5, 0.5, 1.5 };
    
    float3 Color = float3(0.0, 0.0, 0.0 );
    
    for (int i = 0 ; i < 4 ; i++) {
        
        for (int j = 0 ; j < 4 ; j++) {
            
            float2 tc = in.texcoords.xy;
            tc.x = in.texcoords.x + Offsets[j] / colorMap.get_width();
            tc.y = in.texcoords.y + Offsets[i] / colorMap.get_height();
            
            Color += float3(colorMap.sample(colorSampler, in.texcoords.xy).xyz);
        }
    }
    
    Color /= 16.0;

    return float4(Color, 1.0);
}

// ------------------------------------------------------
// Background Sky Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 normal;
    //float3 T,B,N;
} BackgroundSky_InOut;

vertex BackgroundSky_InOut BackgroundSky_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BackgroundSky_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.position.z =  out.position.w;
    out.texcoords = in.texcoords;
    out.normal = in.normal;
    
    /*float3x3 tbn = transpose(
        float3x3(
            in.tangent,
            in.bitangent,
            in.normal.xyz
        ));
    
    out.T = tbn[0];
    out.B = tbn[0];
    out.N = tbn[0];*/

    return out;
}

fragment float4 BackgroundSky_fs(BackgroundSky_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    float nxDir = max(0.1, dot(in.normal.xyz, light.Direction.xyz));
    float4 diffuse = light.Color * nxDir;
    diffuse += ambient_light.Color * ambient_light.AmbientIntensity;
    
    return float4( float3(colorMap.sample(colorSampler, in.texcoords.xy).xyz) * diffuse.xyz, 1.0 );
}

// ------------------------------------------------------
// Background Sky  Deferred Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 colorVarying;
    float4 normal;
    float2 texcoords;
    float3 T,B,N;
} BackgroundSkyDeferred_InOut;

vertex BackgroundSkyDeferred_InOut BackgroundSkyDeferred_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BackgroundSkyDeferred_InOut out;
    
    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;

    return out;
}

fragment float4 BackgroundSkyDeferred_fs(BackgroundSkyDeferred_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}


// ------------------------------------------------------
// Basic Geometry Shader PoNoUV Deferred Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} BasicGeometryShaderPoNoUVDeferred_InOut;

vertex BasicGeometryShaderPoNoUVDeferred_InOut BasicGeometryShaderPoNoUVDeferred_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicGeometryShaderPoNoUVDeferred_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 BasicGeometryShaderPoNoUVDeferred_fs(BasicGeometryShaderPoNoUVDeferred_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Basic Geometry Shader PoNoUVTaBi Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} BasicGeometryShaderPoNoUVTaBi_InOut;

vertex BasicGeometryShaderPoNoUVTaBi_InOut BasicGeometryShaderPoNoUVTaBi_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicGeometryShaderPoNoUVTaBi_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 BasicGeometryShaderPoNoUVTaBi_fs(BasicGeometryShaderPoNoUVTaBi_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Basic Geometry Shader PoNoUVTaBi Color Deferred Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} BasicGeometryShaderPoNoUVTaBiColorDeferred_InOut;

vertex BasicGeometryShaderPoNoUVTaBiColorDeferred_InOut BasicGeometryShaderPoNoUVTaBiColorDeferred_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicGeometryShaderPoNoUVTaBiColorDeferred_InOut out;
    
    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;

    return out;
}

fragment float4 BasicGeometryShaderPoNoUVTaBiColorDeferred_fs(BasicGeometryShaderPoNoUVTaBiColorDeferred_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Basic Geometry Shader PoNoUVTaBi Deferred Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} BasicGeometryShaderPoNoUVTaBiDeferred_InOut;

vertex BasicGeometryShaderPoNoUVTaBiDeferred_InOut BasicGeometryShaderPoNoUVTaBiDeferred_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicGeometryShaderPoNoUVTaBiDeferred_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 BasicGeometryShaderPoNoUVTaBiDeferred_fs(BasicGeometryShaderPoNoUVTaBiDeferred_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Basic Geometry Shader PoNoUVTaBi ShadowMap Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} BasicGeometryShaderPoNoUVTaBiShadowMap_InOut;

vertex BasicGeometryShaderPoNoUVTaBiShadowMap_InOut BasicGeometryShaderPoNoUVTaBiShadowMap_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicGeometryShaderPoNoUVTaBiShadowMap_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 BasicGeometryShaderPoNoUVTaBiShadowMap_fs(BasicGeometryShaderPoNoUVTaBiShadowMap_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Basic Particle Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} BasicParticle_InOut;

vertex BasicParticle_InOut BasicParticle_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicParticle_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 BasicParticle_fs(BasicParticle_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Basic Terrain Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} BasicTerrain_InOut;

vertex BasicTerrain_InOut BasicTerrain_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicTerrain_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 BasicTerrain_fs(BasicTerrain_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Basic Terrain Deferred Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 wposition;
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
    float4 ShadowCoord1;
    float4 ShadowCoord2;
    float4 ShadowCoord3;
    float ClipSpacePosZ;
} BasicTerrainDeferred_InOut;

vertex BasicTerrainDeferred_InOut BasicTerrainDeferred_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicTerrainDeferred_InOut out;
    
    //position_p = ModelMatrix * position;
    //normal_p = ModelMatrix * normal;
    //tangent_p = tangent;
    
    //out.LightDirection_tangentspace = /*TBNMatrix * */- dir_light.Direction.xyz;
    //out.EyeDirection_tangentspace =  TBNMatrix * CameraWorldPosition.xyz;
    
    out.wposition = in.position;
    out.position =  uniforms.MVPMatrix * out.wposition;
    out.wposition = uniforms.ModelMatrix * out.wposition;
    out.texcoords = in.texcoords;
    out.ClipSpacePosZ = out.position.z;
    
    out.ShadowCoord1 = uniforms.ShadowMapMVP1 * in.position;
    out.ShadowCoord2 = uniforms.ShadowMapMVP2 * in.position;
    out.ShadowCoord3 = uniforms.ShadowMapMVP3 * in.position;
    
    return out;
}

fragment GBufferDataFragmentOut BasicTerrainDeferred_fs(BasicTerrainDeferred_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & dir_light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<float> colorMap1     [[ texture( TextureIndex1Color ) ]],
                                 texture2d<float> colorMap2     [[ texture( TextureIndex2Color ) ]],
                                 texture2d<float> colorMap3     [[ texture( TextureIndex3Color ) ]],
                                 texture2d<float> colorMap4      [[ texture( TextureIndex4Color ) ]],
                                 texture2d<float> cascade1Map     [[ texture( TextureIndex5Color ) ]],
                                 texture2d<float> cascade2Map     [[ texture( TextureIndex6Color ) ]],
                                 texture2d<float> cascade3Map     [[ texture( TextureIndex7Color ) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear,
                                   address::mirrored_repeat);
    
    GBufferDataFragmentOut out;
    
    
    //vec4 normalTimesLModel = ModelMatrix * o_normal;

    //-------- NORMAL MAPPING BEGIN
    ///vec3 BumpMapNormal = texture(n_texture, texCoord).xyz;
    //BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);

    //vec3 NewNormal;

    //NewNormal = TBNMatrix_p * BumpMapNormal;
    //NewNormal = normalize(NewNormal);
    //-------- NORMAL MAPPING END

    float4 decalsWeights = colorMap1.sample(colorSampler, in.texcoords);

    out.Diffuse = colorMap2.sample(colorSampler, in.texcoords * 512.0) * decalsWeights.x
    + colorMap3.sample(colorSampler, in.texcoords * 128.0) * decalsWeights.y
    + colorMap4.sample(colorSampler, in.texcoords * 128.0) * decalsWeights.z;
    //+ texture( c_texture_2, texCoord * 128.0) * decalsWeights.y + texture( c_texture_3, texCoord * 128.0) * decalsWeights.z );

    //DiffuseOut = decalsWeights;//texture( c_texture_1, texCoord);
    out.Position = in.wposition;
    out.Normal = in.normal;//vec4( NewNormal, 1.0 );
    out.Normal.a = 1.0;
    //out.Position = vec4( WorldPos0, 1.0);
    //SpecularPower =

    texture2d<float> shadow_texture_array[4] =  {cascade1Map, cascade2Map, cascade3Map, cascade3Map};
    float4 shadow_coord_table[4] = {in.ShadowCoord1, in.ShadowCoord2, in.ShadowCoord3, in.ShadowCoord3 };
    //float end_clip_space_table[4] = {uniforms.cascadeEndClipSpace[0], uniforms.cascadeEndClipSpace[1], uniforms.cascadeEndClipSpace[2], uniforms.cascadeEndClipSpace[3] };
    float end_clip_space_table[4] = {10.0, 100.0, 1000.0, 10000.0};
    
    out.Specular = 0.0;
    out.Specular.w = 1.0;
    out.Specular.r = CalcShadowFactor(out.Normal.xyz, dir_light.Direction.xyz, shadow_coord_table, shadow_texture_array, colorSampler, end_clip_space_table, in.ClipSpacePosZ );
    
    return out;
}

// ------------------------------------------------------
// Water Animated Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords1;
    float2 texcoords2;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
    float4 wposition;
} WaterAnimated_InOut;

vertex WaterAnimated_InOut WaterAnimated_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant TimedObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    WaterAnimated_InOut out;
    
    out.T = (uniforms.ModelMatrix * normalize( float4(in.tangent, 1.0 ))).xyz;
    out.B = (uniforms.ModelMatrix * normalize( float4(in.bitangent, 1.0 ))).xyz;
    out.N = (uniforms.ModelMatrix * normalize( in.normal )).xyz;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords1 = in.texcoords + (uniforms.TimeModulator * 0.001);
    out.texcoords2 = in.texcoords - (uniforms.TimeModulator * 0.0001 );// + (cos(uniforms.TimeModulator * M_PI_2_F) * 0.1) * 0.01;
    out.wposition = uniforms.ModelMatrix * in.position;
    
    return out;
}

fragment float4 WaterAnimated_fs(WaterAnimated_InOut in [[stage_in]],
                                 constant TimedObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<float> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<float> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSamplerRepeat(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear,
                                   address::mirrored_repeat);
    
    float4 diffuse = float4(80.0/256.0, 103.0/256.0, 131.0/256.0, 1.0);//colorMap.sample(colorSamplerRepeat, in.texcoords1* 64 ); //
    float4 base_normal = normalMap.sample(colorSamplerRepeat, in.texcoords1* 64 ) * normalMap.sample(colorSamplerRepeat, in.texcoords2* 64 ) ;
    
    float3x3 TBN = float3x3( in.T, in.B, in.N );
    
    float3 normal = ComputeNormalMapping( TBN, float3( base_normal.xyz ) );
    
    float3 eye_world_position = uniforms.ViewMatrix.columns[3].xyz;
    
    diffuse = diffuse * CalcDirectionalLight(light.Color, light.Direction.xyz, normal.xyz, in.wposition.xyz, eye_world_position, 100.0, 1.0 ) + diffuse * ambient_light.Color * ambient_light.AmbientIntensity * 0.3;
    
    //diffuse = CalcDirectionalLight(light.Color, light.Direction.xyz, normal.xyz, in.wposition.xyz, eye_world_position, 100.0, 1.0 );

    return diffuse;
}

// ------------------------------------------------------
// Checkpoint Effect Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} CheckpointEffect_InOut;

vertex CheckpointEffect_InOut CheckpointEffect_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    CheckpointEffect_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 CheckpointEffect_fs(CheckpointEffect_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Deferred Ambiant And Directionnal Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
    float2 ViewRay;
} DeferredAmbiantAndDirectionnal_InOut;

vertex DeferredAmbiantAndDirectionnal_InOut DeferredAmbiantAndDirectionnal_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant DeferredLightObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    DeferredAmbiantAndDirectionnal_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    out.ViewRay.x = in.position.x * uniforms.FOVRatio.z * uniforms.FOVRatio.y;
    out.ViewRay.y = in.position .y * uniforms.FOVRatio.y;
    
    return out;
}

fragment float4 DeferredAmbiantAndDirectionnal_fs(DeferredAmbiantAndDirectionnal_InOut in [[stage_in]],
                                 constant DeferredLightObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<float> ssaoMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<float> diffuseMap     [[ texture(TextureIndex2Color) ]],
                                 texture2d<float> normalMap     [[ texture(TextureIndex3Color) ]],
                                 texture2d<float> specularMap     [[ texture(TextureIndex4Color) ]],
                                 depth2d<float> depthMap[[ texture(TextureIndex5Color) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
        
    float Depth = depthMap.sample( colorSampler, in.texcoords);
    
    float4 world_pos = uniforms.PreviousProjection * float4( in.texcoords.x * 2.0 - 1.0, -(in.texcoords.y * 2.0 - 1.0), Depth, 1.0 ); //
    world_pos /= world_pos.w;
    
    float3 eye_world_position = uniforms.ViewMatrix.columns[3].xyz;

    float4 Color = float4( diffuseMap.sample(colorSampler, in.texcoords ) );
    float4 Normal = float4( normalMap.sample(colorSampler, in.texcoords ) );
    
    float ssao = ssaoMap.sample(colorSampler, in.texcoords ).x;

    float shadow = specularMap.sample(colorSampler, in.texcoords ).x;
    float specular_intensity = specularMap.sample(colorSampler, in.texcoords ).y;

    float4 colorOut = (Color * CalcDirectionalLight( light.Color, light.Direction.xyz, Normal.xyz, world_pos.xyz, eye_world_position, specular_intensity, light.DiffuseIntensity ) * ssao * shadow) + Color * (ambient_light.Color * ambient_light.DiffuseIntensity * ssao);
    colorOut.a = 1.0;
    
    return colorOut;
}

// ------------------------------------------------------
// Deferred Point Light Shader
// ------------------------------------------------------

float2 CalcTexCoords( float2 pos ) {
    
    return pos;
}

typedef struct
{
    float4 position [[position]];
} DeferredPointLight_InOut;

vertex DeferredPointLight_InOut DeferredPointLight_vs(VertexPosNormal in [[stage_in]],
    constant DeferredLightObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
    constant PointLight & point_light [[ buffer(BufferIndexPointLightsConstants) ]] )
{
    DeferredPointLight_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    
    return out;
}

fragment float4 DeferredPointLight_fs(
    DeferredPointLight_InOut in [[stage_in]],
    constant DeferredLightObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
    constant PointLight & point_light [[ buffer(BufferIndexPointLightsConstants) ]],
    texture2d<float> positionMap     [[ texture(TextureIndex1Color) ]],
    texture2d<float> diffuseffMap     [[ texture(TextureIndex2Color) ]],
    texture2d<float> normalMap     [[ texture(TextureIndex3Color) ]],
    texture2d<float> specularMap     [[ texture(TextureIndex4Color) ]],
    depth2d<float> depthMap     [[ texture(TextureIndex5Color) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    float2 tx = (in.position.xy - float2( 0.5, 0.5)) / float2( positionMap.get_width(), positionMap.get_height() );
    float Depth = depthMap.sample( colorSampler, tx);
    
    float4 world_pos = uniforms.PreviousProjection * float4( tx.x * 2.0 - 1.0, -(tx.y * 2.0 - 1.0), Depth, 1.0 ); //TODO:
    world_pos /= world_pos.w;
    
    float4 diffuse = float4( diffuseffMap.sample(colorSampler, tx ) ); //texture( o_texture_1, in.texcoords ).xyz;
    float3 normal = float4( normalMap.sample(colorSampler, tx ) ).xyz; //texture( o_texture_2, in.texcoords ).xyz;
    //float shadow = texture( o_texture_3, tx ).r;
    //float3 ssao = texture( o_texture_4, tx ).xyz;
    float specular_intensity = 1.0; //float4( specularMap.sample(colorSampler, in.texcoords ) ).x;
    
    float3 eye_world_position = uniforms.ViewMatrix.columns[3].xyz;
    
    //TODO: Fetch and use material
    float4 colorOut = diffuse * CalcPointLight( point_light.Color, normalize(normal), world_pos.xyz, eye_world_position, point_light.Position.xyz, specular_intensity, point_light.DiffuseIntensity, point_light.Constant, point_light.Linear, point_light.Exp );
    
    return colorOut;
}

// ------------------------------------------------------
// Deferred Spot Light Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 LightPosition;
} DeferredSpotLight_InOut;

vertex DeferredSpotLight_InOut DeferredSpotLight_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant DeferredLightObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                            constant SpotLight & spot_light [[ buffer(BufferIndexSpotLightsConstants) ]] )
{
    DeferredSpotLight_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    
    return out;
}

fragment float4 DeferredSpotLight_fs(DeferredSpotLight_InOut in [[stage_in]],
                                 constant DeferredLightObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant SpotLight & spot_light [[ buffer(BufferIndexSpotLightsConstants) ]],
                                 texture2d<float> positionMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<float> diffuseffMap     [[ texture(TextureIndex2Color) ]],
                                 texture2d<float> normalMap     [[ texture(TextureIndex3Color) ]],
                                 texture2d<float> specularMap     [[ texture(TextureIndex4Color) ]],
                                 depth2d<float> depthMap     [[ texture(TextureIndex5Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    float2 tx = (in.position.xy - float2( 0.5, 0.5)) / float2( positionMap.get_width(), positionMap.get_height() );
    float Depth = depthMap.sample( colorSampler, tx);
    
    float4 world_pos = uniforms.PreviousProjection * float4( tx.x * 2.0 - 1.0, -(tx.y * 2.0 - 1.0), Depth, 1.0 ); //TODO:
    world_pos /= world_pos.w;
    
    float4 diffuse = float4( diffuseffMap.sample(colorSampler, tx ) ); //texture( o_texture_1, in.texcoords ).xyz;
    float3 normal = float4( normalMap.sample(colorSampler, tx ) ).xyz; //texture( o_texture_2, in.texcoords ).xyz;
    //float shadow = texture( o_texture_3, tx ).r;
    //float3 ssao = texture( o_texture_4, tx ).xyz;
    float specular_intensity = 1.0; //float4( specularMap.sample(colorSampler, in.texcoords ) ).x;
    
    float3 eye_world_position = uniforms.ViewMatrix.columns[3].xyz;
    
    //TODO: Fetch and use material
    float4 colorOut = diffuse * CalcSpotLight( world_pos.xyz, eye_world_position, spot_light, normal, specular_intensity );
    
    return colorOut;
    
    /*float Depth = depthMap.sample( colorSampler, in.texcoords);
    
    float4 world_pos = uniforms.PreviousProjection * float4( in.texcoords.x * 2.0 - 1.0, -(in.texcoords.y * 2.0 - 1.0), Depth, 1.0 ); //
    world_pos /= world_pos.w;
    
    float3 diffuse = float4( diffuseffMap.sample(colorSampler, in.texcoords ) ).xyz; //texture( o_texture_1, in.texcoords ).xyz;
    float3 normal = float4( normalMap.sample(colorSampler, in.texcoords ) ).xyz; //texture( o_texture_2, in.texcoords ).xyz;
    //float shadow = texture( o_texture_3, tx ).r;
    //float3 ssao = texture( o_texture_4, tx ).xyz;
    float specular_intensity = 1.0; //float4( specularMap.sample(colorSampler, in.texcoords ) ).x;
    
    float3 eye_world_position = uniforms.ViewMatrix.columns[3].xyz;

    //TODO: Fetch and use material
    float3 colorOut = diffuse * CalcSpotLight( world_pos.xyz, eye_world_position, spot_light, normal, specular_intensity ).xyz;
    
    return float4( colorOut, 1.0);*/
}

// ------------------------------------------------------
// Fullscreen bloom post process Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 normal;
    float2 texcoords;
} Fullscreenbloompostprocess_InOut;

vertex Fullscreenbloompostprocess_InOut FullscreenBloomPostProcess_vs(VertexPosNormalTex in [[stage_in]],
    constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]] )
    //constant float & BloomThreshold [[ buffer(BufferIndexBloomThresholdConstants) ]] )
{
    Fullscreenbloompostprocess_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 FullscreenBloomPostProcess_fs(Fullscreenbloompostprocess_InOut in [[stage_in]],
    constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
    //constant float & BloomThreshold [[ buffer(BufferIndexBloomThresholdConstants) ]],
    texture2d<float> colorMap     [[ texture(TextureIndex1Color) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    constexpr float4 BloomThreshold = 0.75;
    
    // Look up the original image color.
    float4 colorSample = colorMap.sample(colorSampler, in.texcoords.xy);

    // Adjust it to keep only values brighter than the specified threshold.
    float4 colorOut = clamp( (colorSample - BloomThreshold) / (1.0 - BloomThreshold), float4(0.0), float4(1.0) );
    
    return colorOut;
}

// ------------------------------------------------------
// Fullscreen Combine Post Process Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 normal;
    float2 texcoords;
} FullscreenCombinePostProcess_InOut;

float4 AdjustSaturation(float4 color, float saturation)
{
    // The constants 0.3, 0.59, and 0.11 are chosen because the
    // human eye is more sensitive to green light, and less to blue.
    float grey = dot( float3( color ), float3( 0.3, 0.59, 0.11 ) );
    
    return mix( float4(grey,grey,grey, 1), color, saturation );
}

vertex FullscreenCombinePostProcess_InOut FullscreenCombinePostProcess_vs(VertexPosNormalTex in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    FullscreenCombinePostProcess_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 FullscreenCombinePostProcess_fs(FullscreenCombinePostProcess_InOut in [[stage_in]],
                                constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                texture2d<half> colorMap1     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    constexpr float BaseSaturation = 0.7f;
    constexpr float BloomSaturation = 1.0f;
    constexpr float BaseIntensity = 0.7f;
    constexpr float BloomIntensity = 1.0f;

    // Look up the bloom and original base image colors.
    float4 base = float4(colorMap.sample(colorSampler, in.texcoords.xy));
    float4 bloom1 = float4(colorMap1.sample(colorSampler, in.texcoords.xy));

    // Adjust color saturation and intensity.
    base = AdjustSaturation( base, BaseSaturation ) * BaseIntensity;
    bloom1 = AdjustSaturation( bloom1, BloomSaturation ) * BloomIntensity;

    // Darken down the base image in areas where there is a lot of bloom,
    // to prevent things looking excessively burned-out.
    bloom1 *= (1 - clamp(bloom1, 0.0, 1.0));
    
    // Combine the two images.
    float4 colorOut = bloom1 + base;
    colorOut.a = 1;
    
    return colorOut;
}

// ------------------------------------------------------
// Fullscreen Gaussian Horrizontal Blur Post Process Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 normal;
    float2 texcoords;
} FullscreenGaussianHorrizontalBlurPostProcess_InOut;

vertex FullscreenGaussianHorrizontalBlurPostProcess_InOut FullscreenGaussianHorrizontalBlurPostProcess_vs(
    VertexPosNormalTex in [[stage_in]],
    constant FullscreenGaussianObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]] )
{
    FullscreenGaussianHorrizontalBlurPostProcess_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 FullscreenGaussianHorrizontalBlurPostProcess_fs(FullscreenGaussianHorrizontalBlurPostProcess_InOut in [[stage_in]],
    constant FullscreenGaussianObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
    texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    constexpr float weight[5] = { 0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216 };

    float2 tex_offset = 1.0 / (float2(colorMap.get_width(), colorMap.get_height()) * uniforms.FrameResolution);
    // gets size of single texel
    float2 txc = in.texcoords.xy;// * uniforms.FrameResolution.xy;
    float4 colorOut;

    colorOut.rgb = float4(colorMap.sample(colorSampler,txc)).rgb * weight[0];

    for(int i = 1; i < 5; ++i)
    {
        colorOut.rgb += float4(colorMap.sample(colorSampler,txc + float2(tex_offset.x * i, 0.0))).rgb * weight[i];
        colorOut.rgb += float4(colorMap.sample(colorSampler,txc - float2(tex_offset.x * i, 0.0))).rgb * weight[i];
    }

    colorOut.a = 1;
        
    return colorOut;
}

// ------------------------------------------------------
// Fullscreen Gaussian Vertical Blur Post Process Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 normal;
    float2 texcoords;
} FullscreenGaussianVerticalBlurPostProcess_InOut;

vertex FullscreenGaussianVerticalBlurPostProcess_InOut FullscreenGaussianVerticalBlurPostProcess_vs(
    VertexPosNormalTex in [[stage_in]],
    constant FullscreenGaussianObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]] )
{
    FullscreenGaussianVerticalBlurPostProcess_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 FullscreenGaussianVerticalBlurPostProcess_fs(FullscreenGaussianVerticalBlurPostProcess_InOut in [[stage_in]],
    constant FullscreenGaussianObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
    texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    constexpr float weight[5] = { 0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216 };

    float2 tex_offset = 1.0 / (float2(colorMap.get_width(), colorMap.get_height()) * uniforms.FrameResolution);
    
    float2 txc = in.texcoords.xy;// * uniforms.FrameResolution.xy;
    float4 colorOut;

    colorOut.rgb = float4(colorMap.sample(colorSampler,txc)).rgb * weight[0];

    for(int i = 1; i < 5; ++i)
    {
        colorOut.rgb += float4(colorMap.sample(colorSampler,txc + float2(0.0, tex_offset.y * i))).rgb * weight[i];
        colorOut.rgb += float4(colorMap.sample(colorSampler,txc - float2(0.0, tex_offset.y * i))).rgb * weight[i];
    }

    colorOut.a = colorOut.r * colorOut.g * colorOut.b;
        
    return colorOut;
}

// ------------------------------------------------------
// Fullscreen Speed Blur Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} FullscreenSpeedBlur_InOut;

vertex FullscreenSpeedBlur_InOut FullscreenSpeedBlur_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    FullscreenSpeedBlur_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 FullscreenSpeedBlur_fs(FullscreenSpeedBlur_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Line Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} LineShader_InOut;

vertex LineShader_InOut LineShader_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    LineShader_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 LineShader_fs(LineShader_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Null technique Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 normal;
} NullTechnique_InOut;

vertex NullTechnique_InOut NullTechnique_vs(VertexPosNormal in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    NullTechnique_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    
    return out;
}

fragment float4 NullTechnique_fs(NullTechnique_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 0.0 );
}

// ------------------------------------------------------
// Animation Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 wposition;
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
    float3 LightDirection_tangentspace;
    float3 EyeDirection_tangentspace;
} AnimationShader_InOut;

vertex AnimationShader_InOut AnimationShader_vs(VertexPosNormalTexTanBiWeJoIn in [[stage_in]],
                                            constant AnimatedObjectUniforms & uniforms [[ buffer( BufferIndexUniforms ) ]],
                                            const device float4x4 * jointsMatrix  [[ buffer(SkinningMatrixBuffer) ]] )
{
    AnimationShader_InOut out;
    
    float4x4 blend_result = in.weights.x * jointsMatrix[ int( in.joint_indices.x ) ]+ in.weights.y * jointsMatrix[ int( in.joint_indices.y ) ] + in.weights.z * jointsMatrix[ int( in.joint_indices.z ) ] + in.weights.w * jointsMatrix[ int( in.joint_indices.w ) ];
    
    out.T = (uniforms.ModelMatrix * normalize( float4(in.tangent, 1.0 ))).xyz;
    out.B = (uniforms.ModelMatrix * normalize( float4(in.bitangent, 1.0 ))).xyz;
    out.N = (uniforms.ModelMatrix * normalize( in.normal )).xyz;
    
    //position_p = ModelMatrix * position;
    //normal_p = ModelMatrix * normal;
    //tangent_p = tangent;
    
    //out.LightDirection_tangentspace = /*TBNMatrix * */- dir_light.Direction.xyz;
    //out.EyeDirection_tangentspace =  TBNMatrix * CameraWorldPosition.xyz;
    
    out.wposition = uniforms.attrBindShapeMatrix * in.position * blend_result;
    out.position =  uniforms.MVPMatrix * out.wposition;
    out.wposition = uniforms.ModelMatrix * out.wposition;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 AnimationShader_fs(AnimationShader_InOut in [[stage_in]],
                                 constant AnimatedObjectUniforms & uniforms [[ buffer( BufferIndexUniforms ) ]],
                                 constant DirectionalLight & dir_light [[ buffer( BufferIndexDirectionalLightsConstants ) ]],
                                 constant AmbientLight & ambient_light [[ buffer( BufferIndexAmbientLightConstants ) ]],
                                 constant Material & material [[ buffer( MaterialUniforms ) ]],
                                 texture2d<half> colorMap     [[ texture( TextureIndex1Color ) ]],
                                 texture2d<half> normalMap     [[ texture( TextureIndex2Color ) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    half4 colorSample = colorMap.sample(colorSampler, in.texcoords.xy);
    half4 base_normal = normalMap.sample(colorSampler, in.texcoords.xy);
    
    float3x3 TBN = float3x3( in.T, in.B, in.N );
    
    float3 normal = ComputeNormalMapping( TBN, float3( base_normal.xyz ) );
    float3 eye_world_position = uniforms.ViewMatrix.columns[3].xyz;
    
    float4 color = float4( colorSample ) * CalcDirectionalLight( dir_light.Color, dir_light.Direction.xyz, normal.xyz, in.wposition.xyz, eye_world_position, material.SpecularIntensity, dir_light.DiffuseIntensity );
    
    return color;
}

vertex AnimationShader_InOut AnimationShadowMapShader_vs(VertexPosNormalTexTanBiWeJoIn in [[stage_in]],
                                            constant AnimatedObjectUniforms & uniforms [[ buffer( BufferIndexUniforms ) ]],
                                            const device float4x4 * jointsMatrix  [[ buffer(SkinningMatrixBuffer) ]] )
{
    AnimationShader_InOut out;
    
    float4x4 blend_result = in.weights.x * jointsMatrix[ int( in.joint_indices.x ) ]+ in.weights.y * jointsMatrix[ int( in.joint_indices.y ) ] + in.weights.z * jointsMatrix[ int( in.joint_indices.z ) ] + in.weights.w * jointsMatrix[ int( in.joint_indices.w ) ];
    
    out.wposition = uniforms.attrBindShapeMatrix * in.position * blend_result;
    out.position =  uniforms.MVPMatrix * out.wposition;
    out.wposition = uniforms.ModelMatrix * out.wposition;
 
    return out;
}

fragment float4 AnimationShadowMapShader_fs(AnimationShader_InOut in [[stage_in]],
                                 constant AnimatedObjectUniforms & uniforms [[ buffer( BufferIndexUniforms ) ]],
                                 constant DirectionalLight & dir_light [[ buffer( BufferIndexDirectionalLightsConstants ) ]],
                                 constant AmbientLight & ambient_light [[ buffer( BufferIndexAmbientLightConstants ) ]],
                                 constant Material & material [[ buffer( MaterialUniforms ) ]],
                                 texture2d<half> colorMap     [[ texture( TextureIndex1Color ) ]],
                                 texture2d<half> normalMap     [[ texture( TextureIndex2Color ) ]] )
{
    return float4( in.position.z );
}

// ------------------------------------------------------
// Animation Shader Deferred
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 wposition;
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
    float3 LightDirection_tangentspace;
    float3 EyeDirection_tangentspace;
    float4 ShadowCoord1;
    float4 ShadowCoord2;
    float4 ShadowCoord3;
    float ClipSpacePosZ;
} AnimationShaderDeferred_InOut;

vertex AnimationShaderDeferred_InOut AnimationShaderDeferred_vs(VertexPosNormalTexTanBiWeJoIn in [[stage_in]],
                                            constant AnimatedObjectUniforms & uniforms [[ buffer( BufferIndexUniforms ) ]],
                                            const device float4x4 * jointsMatrix  [[ buffer(SkinningMatrixBuffer) ]] )
{
    AnimationShaderDeferred_InOut out;
    
    float4x4 blend_result = in.weights.x * jointsMatrix[ int( in.joint_indices.x ) ]+ in.weights.y * jointsMatrix[ int( in.joint_indices.y ) ] + in.weights.z * jointsMatrix[ int( in.joint_indices.z ) ] + in.weights.w * jointsMatrix[ int( in.joint_indices.w ) ];
    
    out.T = (uniforms.ModelMatrix * normalize( float4(in.tangent, 1.0 ))).xyz;
    out.B = (uniforms.ModelMatrix * normalize( float4(in.bitangent, 1.0 ))).xyz;
    out.N = (uniforms.ModelMatrix * normalize( in.normal )).xyz;
    
    out.ShadowCoord1 = uniforms.ShadowMapMVP1 * in.position;
    out.ShadowCoord2 = uniforms.ShadowMapMVP2 * in.position;
    out.ShadowCoord3 = uniforms.ShadowMapMVP3 * in.position;
    
    //position_p = ModelMatrix * position;
    //normal_p = ModelMatrix * normal;
    //tangent_p = tangent;
    
    //out.LightDirection_tangentspace = /*TBNMatrix * */- dir_light.Direction.xyz;
    //out.EyeDirection_tangentspace =  TBNMatrix * CameraWorldPosition.xyz;
    
    out.wposition = uniforms.attrBindShapeMatrix * in.position * blend_result;
    out.position =  uniforms.MVPMatrix * out.wposition;
    out.wposition = uniforms.ModelMatrix * out.wposition;
    out.texcoords = in.texcoords;
    out.ClipSpacePosZ = out.position.z;
    
    return out;
}

fragment GBufferDataFragmentOut AnimationShaderDeferred_fs(AnimationShaderDeferred_InOut in [[stage_in]],
                                 constant AnimatedObjectUniforms & uniforms [[ buffer( BufferIndexUniforms ) ]],
                                 constant DirectionalLight & dir_light [[ buffer( BufferIndexDirectionalLightsConstants ) ]],
                                 constant AmbientLight & ambient_light [[ buffer( BufferIndexAmbientLightConstants ) ]],
                                 constant Material & material [[ buffer( MaterialUniforms ) ]],
                                 texture2d<float> colorMap     [[ texture( TextureIndex1Color ) ]],
                                 texture2d<float> normalMap     [[ texture( TextureIndex2Color ) ]],
                                 texture2d<float> cascade1Map     [[ texture( TextureIndex3Color ) ]],
                                 texture2d<float> cascade2Map     [[ texture( TextureIndex4Color ) ]],
                                 texture2d<float> cascade3Map     [[ texture( TextureIndex5Color ) ]])
{
    GBufferDataFragmentOut out;
    
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    float4 colorSample = colorMap.sample(colorSampler, in.texcoords.xy);
    float4 base_normal = normalMap.sample(colorSampler, in.texcoords.xy);
    
    texture2d<float> shadow_texture_array[4] =  {cascade1Map, cascade2Map, cascade3Map, cascade3Map};
    float4 shadow_coord_table[4] = {in.ShadowCoord1, in.ShadowCoord2, in.ShadowCoord3, in.ShadowCoord3 };
    //float end_clip_space_table[4] = {uniforms.cascadeEndClipSpace[0], uniforms.cascadeEndClipSpace[1], uniforms.cascadeEndClipSpace[2], uniforms.cascadeEndClipSpace[3] };
    float end_clip_space_table[4] = {10.0, 100.0, 1000.0, 10000.0};
    
    float3x3 TBN = float3x3( in.T, in.B, in.N );
    
    out.Position = in.wposition;
    out.Diffuse = colorSample;
    out.Normal = float4( ComputeNormalMapping( TBN, float3( base_normal.xyz ) ), 1.0 );
    out.Specular = 0.0;
    out.Specular.w = 1.0;
    out.Specular.r = CalcShadowFactor(out.Normal.xyz, dir_light.Direction.xyz, shadow_coord_table, shadow_texture_array, colorSampler, end_clip_space_table, in.ClipSpacePosZ );
    
    return out;
}

// ------------------------------------------------------
// Color Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} ColorShader_InOut;

vertex ColorShader_InOut ColorShader_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    ColorShader_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 ColorShader_fs(ColorShader_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Shadow map effect Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} ShadowmapEffect_InOut;

vertex ShadowmapEffect_InOut ShadowmapEffect_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    ShadowmapEffect_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 ShadowmapEffect_fs(ShadowmapEffect_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Space Ship Special Effect Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} SpaceShipSpecialEffect_InOut;

vertex SpaceShipSpecialEffect_InOut SpaceShipSpecialEffect_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    SpaceShipSpecialEffect_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 SpaceShipSpecialEffect_fs(SpaceShipSpecialEffect_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// SSAO Effect Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float2 ViewRay;
    float3 T,B,N;
} SSAOEffect_InOut;

vertex SSAOEffect_InOut SSAOEffect_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    SSAOEffect_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 SSAOEffect_fs(SSAOEffect_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

vertex SSAOEffect_InOut SSAOEffectDeferred_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                              const device float4 * SSAOKernel [[ buffer(SSAOKernelConstants) ]],
                                            constant SSAOObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    SSAOEffect_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    out.ViewRay.x = in.position.x * uniforms.SSAOSampleRadFOVRatio.z * uniforms.SSAOSampleRadFOVRatio.y;
    out.ViewRay.y = in.position.y * uniforms.SSAOSampleRadFOVRatio.y;
    
    return out;
}

fragment float4 SSAOEffectDeferred_fs(SSAOEffect_InOut in [[stage_in]],
                                 constant SSAOObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 const device float4 * SSAOKernel [[ buffer(SSAOKernelConstants) ]],
                                 texture2d<float> normalMap     [[ texture(TextureIndex3Color) ]],
                                 depth2d<float> depthMap     [[ texture(TextureIndex4Color) ]],
                                 texture2d<float> randomMap     [[ texture(TextureIndex5Color) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    const int MAX_KERNEL_SIZE = 64;
    const float SSAO_FACTOR = 1.0 / MAX_KERNEL_SIZE;
    const float SSAOSampleRad = 1.1;
    
    const float2 noiseScale = float2(normalMap.get_width()/4.0, normalMap.get_height()/4.0); // screen = 1024*768
    
    float Depth = depthMap.sample( colorSampler, in.texcoords);
    float ViewZ = uniforms.ProjectionMatrix[3][2] / (2 * Depth -1 - uniforms.ProjectionMatrix[2][2]);
    
    float ViewX = in.ViewRay.x * ViewZ;
    float ViewY = in.ViewRay.y * ViewZ;
    
    float3 Pos = float3( ViewX, ViewY, ViewZ );

    float3 randomVec = float3( randomMap.sample(colorSampler, in.texcoords * noiseScale ).xyz);
    
    float3 Normal = normalMap.sample(colorSampler, in.texcoords ).xyz;
    float3 tangent   = normalize(randomVec - Normal * dot(randomVec, Normal));
    float3 bitangent = cross(Normal, tangent);
    float3x3 TBN       = float3x3(tangent, bitangent, Normal);
    
    float4 SSAO = float4(0.0);

    for (int i = 0 ; i < MAX_KERNEL_SIZE ; i++) {
        
        //float3 rnd = (Normal * SSAOKernel[i].xyz);//  * SSAOSampleRad;
        float3 samplePos = Pos.xyz + ( TBN * SSAOKernel[i].xyz ) * SSAOSampleRad;
        float4 offset = float4(samplePos, 1.0); // make it a 4-vector

        offset = uniforms.ProjectionMatrix * offset; // project on the near clipping plane
        offset /= offset.w; // perform perspective divide
        offset.xyz = offset.xyz * 0.5 + 0.5; // transform to (0,1) range

        float dDepth = depthMap.sample( colorSampler, offset.xy);
        float dViewZ = uniforms.ProjectionMatrix[3][2] / (2 * dDepth -1 - uniforms.ProjectionMatrix[2][2]);
        
        if (abs(Pos.z - dViewZ) < SSAOSampleRad) {
            SSAO += step(samplePos.z, dViewZ );
        }
    }

    SSAO = (1.0 - (SSAO * SSAO_FACTOR));

    SSAO = float4(pow(SSAO.r, 2.0));
    
    return float4(SSAO);
}

// ------------------------------------------------------
// Terrain Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} TerrainShader_InOut;

vertex TerrainShader_InOut TerrainShader_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    TerrainShader_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 TerrainShader_fs(TerrainShader_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex2Color) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Ui textured Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    //float4 colorVarying;
} UIShaderTextured_InOut;

vertex UIShaderTextured_InOut UIShaderTextured_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant UIObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    UIShaderTextured_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 UIShaderTextured_fs(UIShaderTextured_InOut in [[stage_in]],
                                 constant UIObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( colorMap.sample( colorSampler, in.texcoords.xy ) );// * in.colorVarying;
}

// ------------------------------------------------------
// Ui colored Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 colorVarying;
} UIShaderColored_InOut;

vertex UIShaderColored_InOut UIShaderColored_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                    constant UIObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    UIShaderColored_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    
    return out;
}

fragment float4 UIShaderColored_fs(UIShaderColored_InOut in [[stage_in]],
                             constant UIObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    return uniforms.geometryColor;
}
