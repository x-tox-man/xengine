//
//  MULTIPOLY_APPLICATION.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef MULTIPOLY_APPLICATION_hpp
#define MULTIPOLY_APPLICATION_hpp

#include "CORE_APPLICATION.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"
#include "GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h"
#include "GRAPHIC_OBJECT_SHAPE_SPHERE.h"
#include "GRAPHIC_OBJECT_SHAPE_LINE.h"
#include "GAMEPLAY_SCENE.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"
#include "CORE_FILESYSTEM.h"
#include "CORE_MEMORY.h"
#include "CORE_PARALLEL.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "SERVICE_NETWORK_LOBBY.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "GRAPHIC_SHADER_EFFECT_SPEEDBLUR.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR.h"
#include "GRAPHIC_OBJECT_ANIMATED.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "GRAPHIC_PARTICLE_SYSTEM.h"
#include "GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY.h"
#include "GRAPHIC_PARTICLE_MODIFIER_GRAVITY.h"
#include "APPLICATION_CONFIGURATION.h"
#include "R3D_RENDER.h"
#include "R3D_GAMEPLAY_GAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( RUN3D_APPLICATION, CORE_APPLICATION )

    RUN3D_APPLICATION();
    virtual ~RUN3D_APPLICATION();

    virtual void Initialize() override;
    virtual void Finalize() override;

    virtual void Update( float time_step ) override;
    virtual void Render() override;

    inline CORE_FILESYSTEM & GetDefaultFileystem() { return DefaultFileystem; }
    inline R3D_GAMEPLAY_GAME & GetGame() { return Game; }

    void SetCamera( GRAPHIC_CAMERA::PTR camera );

private :

    void InitializeGraphics();
    void InitializeGameConfiguration();
    void InitializePhysics();

    CORE_FILESYSTEM
        DefaultFileystem;
    R3D_RENDER
        GameRenderer;
    R3D_GAMEPLAY_GAME
        Game;

XS_CLASS_END

#define R3D_APP_PTR ((RUN3D_APPLICATION *) &RUN3D_APPLICATION::GetApplicationInstance())

#endif /* MULTIPOLY_APPLICATION_hpp */
