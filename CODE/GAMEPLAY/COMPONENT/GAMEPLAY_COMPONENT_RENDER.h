//
//  GAMEPLAY_COMPONENT_RENDER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "CORE_HELPERS_SCALAR.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "CORE_MATH_SHAPE.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GRAPHIC_MATERIAL.h"
#include "RESOURCE_PROXY.h"
#include "GAMEPLAY_COMPONENT_AABB_NODE.h"

class GAMEPLAY_COMPONENT_ENTITY;

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_RENDER )

    GAMEPLAY_COMPONENT_RENDER();
    ~GAMEPLAY_COMPONENT_RENDER();

    XS_DEFINE_SERIALIZABLE

    //CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Render)

    void Render( GRAPHIC_RENDERER &renderer, GAMEPLAY_COMPONENT_POSITION * component );
    void Render( GRAPHIC_RENDERER &renderer, GAMEPLAY_COMPONENT_POSITION * component, GAMEPLAY_COMPONENT_POSITION * parent );

    inline void SetObject( RESOURCE_PROXY & object ) { ObjectProxy = object; }
    inline void SetEffect( RESOURCE_PROXY & effect ) { EffectProxy = effect; }
    inline void SetShadowMapEffectProxy( RESOURCE_PROXY & effect ) { ShadowMapEffectProxy = effect; }
    inline void SetMaterialCollection( RESOURCE_PROXY & material ) { MaterialProxy = material; }
    inline GAMEPLAY_COMPONENT_AABB_NODE & GetAABBNode() { return AABBNode; }

    void ComputeSize( CORE_MATH_SHAPE & shape );

    inline RESOURCE_PROXY & GetObject() { return ObjectProxy; }
    inline RESOURCE_PROXY & GetEffect() { return EffectProxy; }
    inline RESOURCE_PROXY & GetShadowEffectProxy() { return ShadowMapEffectProxy; }
    inline RESOURCE_PROXY & GetMaterial() { return MaterialProxy; }

    inline void SetScaleFactor( float scale_factor ) { ScaleFactor = scale_factor; }
    inline float GetScaleFactor() const { return ScaleFactor; }

    void Reset( GAMEPLAY_COMPONENT_ENTITY * entity ) {
        
        ObjectProxy.SetResource( NULL );
        ObjectProxy.GetResource< GRAPHIC_OBJECT >();
        EffectProxy.SetResource( NULL );
        EffectProxy.GetResource< GRAPHIC_SHADER_EFFECT >();
        ShadowMapEffectProxy.SetResource( NULL );
        ShadowMapEffectProxy.GetResource< GRAPHIC_SHADER_EFFECT >();
        MaterialProxy.SetResource( NULL );
        MaterialProxy.GetResource< GRAPHIC_MATERIAL_COLLECTION >();
        AABBNode.Left = NULL;
        AABBNode.Right = NULL;
        AABBNode.ZOrderLeft = NULL;
        AABBNode.ZOrderRight = NULL;
        AABBNode.SetEntity( entity );
    }

    static int
        ComponentType;

private :

    RESOURCE_PROXY
        ObjectProxy,    // 3D Object should be able to be used in //
        EffectProxy,    // The Effect
        ShadowMapEffectProxy,
        MaterialProxy;  // The material used by Effect

    //TODO: Local Data For material and shader should be preserved?
        //structure here is faulty, must refine

    GAMEPLAY_COMPONENT_AABB_NODE
        AABBNode;
    float
        ScaleFactor;
    CORE_HELPERS_COLOR
        DiffuseOverride;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__) */
