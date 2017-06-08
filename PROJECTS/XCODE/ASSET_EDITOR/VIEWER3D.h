//
//  VIEWER3D.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef VIEWER3D_hpp
#define VIEWER3D_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_MATERIAL.h"
#include "GAMEPLAY_CAMERA.h"
#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"

XS_CLASS_BEGIN( VIEWER3D )

    VIEWER3D();
    virtual ~VIEWER3D();

    void Initialize();

    void Render();
    void Update( const float time_step );

    void Load( const char *);
    void SetSelectedEntity( GAMEPLAY_COMPONENT_ENTITY * entity ) { SelectedEntity = entity; }
    inline GAMEPLAY_SCENE * GetScene() { return Scene; }

private :

    void InitializeScene();
    void CreateMesh( GRAPHIC_OBJECT *, GRAPHIC_SHADER_EFFECT * );
    void RenderSelectedObjectBox();
    void Screenshot();

    GAMEPLAY_SCENE
        * Scene;
    GAMEPLAY_CAMERA
        * Camera;
    GAMEPLAY_COMPONENT_ENTITY
        * SelectedEntity;
    GRAPHIC_OBJECT_SHAPE_CUBE
        * CubeObject;
    GRAPHIC_SHADER_EFFECT::PTR
        CubeEffect;
    GRAPHIC_SHADER_LIGHT
        * DirectionalLight,
        * PointLightOne,
        * PointLightTwo,
        * SpotLightOne,
        * SpotLightTwo;
    bool
        TrigerScreenshot;

XS_CLASS_END

#endif /* VIEWER3D_hpp */
