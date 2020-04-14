//
//  GRAPHIC_RENDERER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_RENDERER__
#define __GAME_ENGINE_REBORN__GRAPHIC_RENDERER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_CAMERA.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "CORE_PARALLEL_LOCK.h"
#include "GRAPHIC_SYSTEM.h"
#include "GRAPHIC_RENDERER_STATE_DESCRIPTOR.h"

#define GRAPHIC_MAX_NUM_CASCADES    8

class GRAPHIC_SHADER_EFFECT;

XS_CLASS_BEGIN( GRAPHIC_RENDERER )

    XS_DEFINE_UNIQUE( GRAPHIC_RENDERER )

    ~GRAPHIC_RENDERER();

    void Initialize() {
        
        #if X_METAL
            InitializeMtl();
            BufferPassIndex = -1;
        
            MetalUniformBufferAddress = GRAPHIC_SYSTEM::GetMtlBufferPointer( MetalUniformBuffer );
        #endif
    }

    void Finalize() {
        
        
    }
    
    void BeginFrame() {
        
        #if X_METAL

            BufferPassIndex = (BufferPassIndex + 1 ) % 3;
            UniformOffset = (512 * 64 * 4 * 10 ) * BufferPassIndex;
            CurrentOffset = 0;
            GRAPHIC_SYSTEM::BeginMtlFrame();
        #endif
    }

    void Render() {
        
        GRAPHIC_SYSTEM::BeginRendering();
            (*RenderCallback)();
        GRAPHIC_SYSTEM::EndRendering();
    }

    void EndFrame() {
        
        #if X_METAL
            GRAPHIC_SYSTEM::EndMtlFrame();
        #endif
    }

    inline void SetCamera( GRAPHIC_CAMERA * camera ) { Camera = camera; };
    inline GRAPHIC_CAMERA * GetCamera() { return Camera; };

    inline void SetShadowMapCamera( int index, GRAPHIC_CAMERA * camera ) { ShadowMapCameraTable[index] = camera; };
    inline const GRAPHIC_CAMERA & GetShadowMapCamera( int index) const { return *ShadowMapCameraTable[ index ]; };

    inline void SetRenderCallback( CORE_HELPERS_CALLBACK * renderCallback ) { RenderCallback = renderCallback; }
    inline void SetDirectionalLight( GRAPHIC_SHADER_LIGHT * light ) { DirectionalLight = light; }
    inline void SetAmbientLight( GRAPHIC_SHADER_LIGHT * light ) { AmbientLight = light; }
    inline void SetPointLight( GRAPHIC_SHADER_LIGHT * light, int light_index ) { PointLightTable.push_back( light ); }
    inline void SetSpotLight( GRAPHIC_SHADER_LIGHT * light, int light_index ) { SpotLightTable.push_back( light ); }
    inline const GRAPHIC_SHADER_LIGHT * GetDirectionalLight() const { return DirectionalLight; }
    inline const GRAPHIC_SHADER_LIGHT * GetPointLight( int index ) const { return PointLightTable[ index ]; }
    inline const GRAPHIC_SHADER_LIGHT * GetSpotLight( int index ) const { return SpotLightTable[ index ]; }
    inline const GRAPHIC_SHADER_LIGHT * GetAmbientLight() const  { return AmbientLight; }

    std::vector< GRAPHIC_SHADER_LIGHT *> & GetSpotLightTable() { return SpotLightTable; }
    std::vector< GRAPHIC_SHADER_LIGHT *> & GetPointLightTable() { return PointLightTable; }

    inline void SetDepthTexture( int index, GRAPHIC_TEXTURE * depth ) { DepthTextureTable[ index ] = depth;}
    inline GRAPHIC_TEXTURE * GetDepthTexture( int index ) const { return DepthTextureTable[ index ]; }

    inline int GetNumCascade() { return NumCascade; }
    inline void SetNumCascade(int num) { NumCascade = num; }

    void EnableScissor( bool enable ) ;
    inline bool IsScissorEnabled() const { return ScissorIsEnabled; }
    inline const CORE_MATH_VECTOR & GetScissorRectangle() const { return ScissorRectangle; }
    inline void SetScissorRectangle( const CORE_MATH_VECTOR & scissor_rectangle ) { ScissorRectangle = scissor_rectangle; }

    inline bool IsColorEnabled() const { return ColorEnabled; }
    inline void EnableColor( bool enable ) { ColorEnabled = enable; }
    inline void SetResizeViewCallback(CORE_HELPERS_CALLBACK_2<int, int> & callback) {ResizeViewCallback = callback; }

    inline bool IsTexturingEnabled() const { return TexturingIsEnabled; }
    inline void SetTexturingIsEnabled( bool enabled ) { TexturingIsEnabled = enabled; }

    inline bool IsLightingEnabled() const { return LightingIsEnabled; }
    inline void SetLightingIsEnabled( bool enabled ) { LightingIsEnabled = enabled; }
    inline bool IsDeferredLightingEnabled() const { return DeferredLightingIsEnabled; }
    inline void SetDeferredLightingIsEnabled( bool enabled ) { DeferredLightingIsEnabled = enabled; }
    inline void SetDeferredSpotIndex( int index ) { DeferredSpotIndex = index; }
    inline void SetDeferredPointIndex( int index ) { DeferredPointIndex = index; }
    inline int GetDeferredSpotIndex() const { return DeferredSpotIndex; }
    inline int GetDeferredPointIndex() const { return DeferredPointIndex; }

    inline bool IsShadowMappingEnabled() const { return ShadowMappingIsEnabled; }
    inline void SetShadowMappingEnabled( bool enabled ) { ShadowMappingIsEnabled = enabled; }


    inline void SetCurrentLightMatrix( const CORE_MATH_MATRIX & matrix ) { CurrentLightMatrix = matrix; }
    inline const CORE_MATH_MATRIX & GetCurrentLightMatrix() { return CurrentLightMatrix; }

    void Resize(int width, int height);

    void ResetDepth();

    const CORE_HELPERS_IDENTIFIER & GetShadowMapMVPName( int cascade_index );

    inline int GetCascadeEnd( int index ) const { return CascadeEnd[ index ]; }
    inline void SetCascadeEnd( int index, float end ) { CascadeEnd[ index ] = end; }
    inline float * GetCascadeEnd() { return CascadeEnd; }
    inline int GetWidth() const {
        
        #if DEBUG
                if ( Width == 0 ) {
                    CORE_RUNTIME_Abort();
                }
        #endif
        return Width;
    }

    inline int GetHeight() const {
#if DEBUG
        if ( Height == 0 ) {
            CORE_RUNTIME_Abort();
        }
#endif
        
        return Height;
    }

    inline void EnableBlend( const GRAPHIC_SYSTEM_BLEND_OPERATION source, const GRAPHIC_SYSTEM_BLEND_OPERATION destination ) {
        
        Descriptor.ItDoesBlending = true;
        
        Descriptor.BlendingSourceOperation = source;
        Descriptor.BlendingDestinationOperation = destination;
    }

    inline void DisableBlend() {
        
        Descriptor.ItDoesBlending = false;
    }

    inline void SetBlendFunction( const GRAPHIC_SYSTEM_BLEND_EQUATION equation ) {
        
        Descriptor.BlendFunction = equation;
    }


    inline void EnableDepthTest() {
        
        Descriptor.ItDoesDepthTest = true;
    }

    inline void DisableDepthTest() {
        
        Descriptor.ItDoesDepthTest = false;
    }

    inline void EnableStencilTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, int ref, unsigned int mask ) {
        
        Descriptor.ItDoesStencilTest = true;
        Descriptor.StencilOperation = operation;
        Descriptor.StencilRef = ref;
        Descriptor.StencilMask = mask;
    }

    inline void SetStencilOperation( const GRAPHIC_POLYGON_FACE face, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_fail, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_pass, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_and_depth_fail ) {
        
        Descriptor.StencilFaceTable[face].StencilPassAction = stencil_pass;;
        Descriptor.StencilFaceTable[face].StencilFailAction = stencil_fail;
        Descriptor.StencilFaceTable[face].StencilAndDepthFailAction = stencil_and_depth_fail;
    }

    inline void DisableStencilTest() {
        
        Descriptor.ItDoesStencilTest = false;
    }

    inline const GRAPHIC_RENDERER_STATE_DESCRIPTOR & GetDescriptor() const { return Descriptor; }
    inline GRAPHIC_RENDERER_STATE_DESCRIPTOR & GetDescriptor() { return Descriptor; }
    inline void SetDescriptor( const GRAPHIC_RENDERER_STATE_DESCRIPTOR & desc ) { return Descriptor = desc; }

private :
    
    GRAPHIC_CAMERA
        * Camera,
        * ShadowMapCameraTable[ GRAPHIC_MAX_NUM_CASCADES ];
    CORE_HELPERS_CALLBACK
        * RenderCallback;
    CORE_HELPERS_CALLBACK_2<int, int>
        ResizeViewCallback;
    GRAPHIC_SHADER_LIGHT
        * AmbientLight,
        * DirectionalLight;
    std::vector< GRAPHIC_SHADER_LIGHT *>
        SpotLightTable,
        PointLightTable;
    GRAPHIC_TEXTURE
        * DepthTextureTable[ GRAPHIC_MAX_NUM_CASCADES ];
    CORE_MATH_VECTOR
        ScissorRectangle;
    CORE_MATH_MATRIX
        CurrentLightMatrix;
    GRAPHIC_RENDERER_STATE_DESCRIPTOR
        Descriptor;
    int
        LightCount,
        NumCascade,
        Width,
        Height,
        DeferredSpotIndex,
        DeferredPointIndex;
    bool
        ScissorIsEnabled,
        ColorEnabled,
        LightingIsEnabled,
        DeferredLightingIsEnabled,
        TexturingIsEnabled,
        ShadowMappingIsEnabled;
    float
        CascadeEnd[ GRAPHIC_MAX_NUM_CASCADES ];

    #if X_METAL
    public:

        inline void * GetOffsetPointer( unsigned int index) { return ( (uint8_t *) MetalUniformBufferAddress) + UniformOffset + index; }
        inline void OffsetPointer( unsigned int offset ) { CurrentOffset  += offset; }
        inline unsigned int GetCurrentOffset() const { return CurrentOffset; }
        inline void MtlApplyCurrentOffset() { UniformOffset += CurrentOffset + (256 - (CurrentOffset % 256)); CurrentOffset = 0; }

        void InitializeMtl() {
            // TODO: enabled when all init is finished
            MetalUniformBuffer = GRAPHIC_SYSTEM::CreateMetalDynamicUniformBuffer( 512 * 64 * 4 * 10 * 3 );
            
            UniformOffset = 0;
            BufferPassIndex = 0;
        }

        void
            * MetalUniformBuffer,
            * MetalUniformBufferAddress;
        unsigned int
            UniformOffset,
            CurrentOffset,
            BufferPassIndex;
    #endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_RENDERER__) */
