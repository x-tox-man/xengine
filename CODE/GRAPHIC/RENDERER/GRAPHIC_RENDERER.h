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
#include "CORE_APPLICATION.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_LIGHT.h"

XS_CLASS_BEGIN( GRAPHIC_RENDERER )
    XS_DEFINE_UNIQUE( GRAPHIC_RENDERER )

    ~GRAPHIC_RENDERER();

    void Initialize() {
        
    }

    void Finalize() {
        
    }
    
    void BeginFrame() {
        
    }

    void Render() {
        
        (*RenderCallback)();
    }

    void EndFrame() {
        
    }

    inline void SetCamera( GRAPHIC_CAMERA * camera ) { Camera = camera; };
    inline const GRAPHIC_CAMERA & GetCamera() const { return *Camera; };

    inline void SetShadowMapCamera( GRAPHIC_CAMERA * camera ) { ShadowMapCamera = camera; };
    inline const GRAPHIC_CAMERA & GetShadowMapCamera() const { return *ShadowMapCamera; };

    inline void SetRenderCallback( CORE_HELPERS_CALLBACK * renderCallback ) { RenderCallback = renderCallback; }
    inline void SetDirectionalLight( GRAPHIC_SHADER_LIGHT * light ) { DirectionalLight = light; }
    inline void SetAmbientLight( GRAPHIC_SHADER_LIGHT * light ) { AmbientLight = light; }
    inline void SetPointLight( GRAPHIC_SHADER_LIGHT * light, int light_index ) { PointLightTable[ light_index ] = light; }
    inline void SetSpotLight( GRAPHIC_SHADER_LIGHT * light, int light_index ) { SpotLightTable[ light_index ] = light; }
    inline const GRAPHIC_SHADER_LIGHT * GetDirectionalLight() const { return DirectionalLight; }
    inline const GRAPHIC_SHADER_LIGHT * GetPointLight( int index ) const { return PointLightTable[ index ]; }
    inline const GRAPHIC_SHADER_LIGHT * GetSpotLight( int index ) const { return SpotLightTable[ index ]; }
    inline const GRAPHIC_SHADER_LIGHT * GetAmbientLight() const  { return AmbientLight; }

    inline int GetPassIndex() const { return PassIndex; }
    inline void SetPassIndex(int pass) { PassIndex = pass; }
    inline void SetDepthTexture( GRAPHIC_TEXTURE * depth ) { DepthTexture = depth;}
    inline GRAPHIC_TEXTURE * GetDepthTexture() const { return DepthTexture; }

    void EnableScissor( bool enable ) ;
    inline bool IsScissorEnabled() const { return ScissorIsEnabled; }
    inline const CORE_MATH_VECTOR & GetScissorRectangle() const { return ScissorRectangle; }
    inline void SetScissorRectangle( const CORE_MATH_VECTOR & scissor_rectangle ) { ScissorRectangle = scissor_rectangle; }

    inline bool IsColorEnabled() const { return ColorEnabled; }
    inline void EnableColor( bool enable ) { ColorEnabled = enable; }
    inline void SetResizeViewCallback(CORE_HELPERS_CALLBACK_2<int, int> & callback) {ResizeViewCallback = callback; }

    inline bool IsLightingEnabled() const { return LightingIsEnabled; }
    inline void SetLightingIsEnabled( bool enabled ) { LightingIsEnabled = enabled; }

    inline void SetCurrentLightMatrix( const CORE_MATH_MATRIX & matrix ) { CurrentLightMatrix = matrix; }
    inline const CORE_MATH_MATRIX & GetCurrentLightMatrix() { return CurrentLightMatrix; }

    void Resize(int width, int height);

    void ResetDepth();

private :
    
    GRAPHIC_CAMERA
        * Camera,
        * ShadowMapCamera;
    CORE_HELPERS_CALLBACK
        * RenderCallback;
    CORE_HELPERS_CALLBACK_2<int, int>
        ResizeViewCallback;
    GRAPHIC_SHADER_LIGHT
        * AmbientLight,
        * DirectionalLight,
        * PointLightTable[4], // curently shaders have only 2 lights of each type, this is a fixed shader value
        * SpotLightTable[4]; // curently shaders have only 2 lights of each type, this is a fixed shader value
    GRAPHIC_TEXTURE
        * DepthTexture;
    CORE_MATH_VECTOR
        ScissorRectangle;
    CORE_MATH_MATRIX
        CurrentLightMatrix;
    int
        LightCount,
        PassIndex;
    bool
        ScissorIsEnabled,
        ColorEnabled,
        LightingIsEnabled;
    /*GAMEPLAY_SCENE_RENDER_OPTION
        Option;*/

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_RENDERER__) */
