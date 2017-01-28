//
//  GRAPHIC_RENDERER.h
//  GAME-ENGINE-REBORN
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
    inline void SetPointLight( GRAPHIC_SHADER_LIGHT * light, int light_index ) { PointLightTable[ light_index ] = light; }
    inline void SetSpotLight( GRAPHIC_SHADER_LIGHT * light, int light_index ) { SpotLightTable[ light_index ] = light; }
    inline const GRAPHIC_SHADER_LIGHT & GetDirectionalLight() const { return *DirectionalLight; }
    inline const GRAPHIC_SHADER_LIGHT & GetPointLight( int index ) const { return *PointLightTable[ index ]; }
    inline const GRAPHIC_SHADER_LIGHT & GetSpotLight( int index ) const { return *SpotLightTable[ index ]; }
    inline int GetPassIndex() const { return PassIndex; }
    inline void SetPassIndex(int pass) { PassIndex = pass; }
    inline void SetDepthTexture( GRAPHIC_TEXTURE * depth ) { DepthTexture = depth;}
    inline GRAPHIC_TEXTURE * GetDepthTexture() const { return DepthTexture; }
private :
    
    GRAPHIC_CAMERA * Camera, *ShadowMapCamera;
    CORE_HELPERS_CALLBACK * RenderCallback;
    GRAPHIC_SHADER_LIGHT * DirectionalLight;
    GRAPHIC_SHADER_LIGHT * PointLightTable[4]; // curently shaders have only 2 lights of each type, this is a fixed shader value
    GRAPHIC_SHADER_LIGHT * SpotLightTable[4]; // curently shaders have only 2 lights of each type, this is a fixed shader value
    GRAPHIC_TEXTURE * DepthTexture;
    int LightCount;
    int PassIndex;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_RENDERER__) */
