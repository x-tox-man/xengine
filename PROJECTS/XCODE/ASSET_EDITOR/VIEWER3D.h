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

XS_CLASS_BEGIN( VIEWER3D )

    VIEWER3D();
    virtual ~VIEWER3D();

    void Initialize();

    void Render();
    void Update( const float time_step );

    void Load( const char *);

private :

    void InitializeScene();
    void CreateMesh( GRAPHIC_OBJECT *, GRAPHIC_SHADER_EFFECT * );

    GAMEPLAY_SCENE
        * Scene;
    GRAPHIC_CAMERA
        * Camera;
    GRAPHIC_SHADER_LIGHT
        * DirectionalLight,
        * PointLightOne,
        * PointLightTwo,
        * SpotLightOne,
        * SpotLightTwo;

XS_CLASS_END

#endif /* VIEWER3D_hpp */
