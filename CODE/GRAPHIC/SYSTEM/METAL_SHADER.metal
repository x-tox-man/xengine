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
    float2 texcoords [[attribute(VertexAttributeTexcoords)]];
    float3 tangent [[attribute(VertexAttributeTangent)]];
    float3 bitangent [[attribute(VertexAttributeBitangent)]];
} VertexPosNormalTexTanBi;

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
    float AmbientIntensity;
    float DiffuseIntensity;
    float Exp;
    float Linear;
    float Constant;
} SpotLight;

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
    
    out.position = transpose(uniforms.MVPMatrix) * in.position;
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} BasicTerrainDeferred_InOut;

vertex BasicTerrainDeferred_InOut BasicTerrainDeferred_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    BasicTerrainDeferred_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 BasicTerrainDeferred_fs(BasicTerrainDeferred_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
} DeferredAmbiantAndDirectionnal_InOut;

vertex DeferredAmbiantAndDirectionnal_InOut DeferredAmbiantAndDirectionnal_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    DeferredAmbiantAndDirectionnal_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 DeferredAmbiantAndDirectionnal_fs(DeferredAmbiantAndDirectionnal_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Deferred Point Light Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} DeferredPointLight_InOut;

vertex DeferredPointLight_InOut DeferredPointLight_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    DeferredPointLight_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 DeferredPointLight_fs(DeferredPointLight_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Deferred Spot Light Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} DeferredSpotLight_InOut;

vertex DeferredSpotLight_InOut DeferredSpotLight_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    DeferredSpotLight_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 DeferredSpotLight_fs(DeferredSpotLight_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Fullscreen bloom post process Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} Fullscreenbloompostprocess_InOut;

vertex Fullscreenbloompostprocess_InOut Fullscreenbloompostprocess_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    Fullscreenbloompostprocess_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 Fullscreenbloompostprocess_fs(Fullscreenbloompostprocess_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Fullscreen Combine Post Process Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} FullscreenCombinePostProcess_InOut;

vertex FullscreenCombinePostProcess_InOut FullscreenCombinePostProcess_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    FullscreenCombinePostProcess_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 FullscreenCombinePostProcess_fs(FullscreenCombinePostProcess_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Fullscreen Gaussian Horrizontal Blur Post Process Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} FullscreenGaussianHorrizontalBlurPostProcess_InOut;

vertex FullscreenGaussianHorrizontalBlurPostProcess_InOut FullscreenGaussianHorrizontalBlurPostProcess_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    FullscreenGaussianHorrizontalBlurPostProcess_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 FullscreenGaussianHorrizontalBlurPostProcess_fs(FullscreenGaussianHorrizontalBlurPostProcess_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Fullscreen Gaussian Vertical Blur Post Process Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} FullscreenGaussianVerticalBlurPostProcess_InOut;

vertex FullscreenGaussianVerticalBlurPostProcess_InOut FullscreenGaussianVerticalBlurPostProcess_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    FullscreenGaussianVerticalBlurPostProcess_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 FullscreenGaussianVerticalBlurPostProcess_fs(FullscreenGaussianVerticalBlurPostProcess_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} NullTechnique_InOut;

vertex NullTechnique_InOut NullTechnique_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    NullTechnique_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 NullTechnique_fs(NullTechnique_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
}

// ------------------------------------------------------
// Animation Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float2 texcoords;
    float4 colorVarying;
    float4 normal;
    float3 T,B,N;
} AnimationShader_InOut;

vertex AnimationShader_InOut AnimationShader_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    AnimationShader_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 AnimationShader_fs(AnimationShader_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 constant AmbientLight & ambient_light [[ buffer(BufferIndexAmbientLightConstants) ]],
                                 constant DirectionalLight & light [[ buffer(BufferIndexDirectionalLightsConstants) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]],
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( 1.0 );
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
                                 texture2d<half> normalMap     [[ texture(TextureIndex1Normal) ]])
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
    float4 colorVarying;
} Uitextured_InOut;

vertex Uitextured_InOut Uitextured_vs(VertexPosNormalTexTanBi in [[stage_in]],
                                            constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    Uitextured_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    out.texcoords = in.texcoords;
    
    return out;
}

fragment float4 Uitextured_fs(Uitextured_InOut in [[stage_in]],
                                 constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                                 texture2d<half> colorMap     [[ texture(TextureIndex1Color) ]] )
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);
    
    return float4( colorMap.sample( colorSampler, in.texcoords.xy ) ) * in.colorVarying;
}

// ------------------------------------------------------
// Ui colored Shader
// ------------------------------------------------------

typedef struct
{
    float4 position [[position]];
    float4 colorVarying;
} UiColored_InOut;

vertex UiColored_InOut UiColored_vs(VertexPosNormalTex in [[stage_in]],
                                    constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    UiColored_InOut out;

    out.position = uniforms.MVPMatrix * in.position;
    
    return out;
}

fragment float4 UiColored_fs(UiColored_InOut in [[stage_in]],
                             constant ObjectUniforms & uniforms [[ buffer(BufferIndexUniforms) ]])
{
    return float4( in.colorVarying );
}
