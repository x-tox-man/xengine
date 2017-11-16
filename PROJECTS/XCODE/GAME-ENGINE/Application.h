//
//  Application.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__Application__
#define __GAME_ENGINE_REBORN__Application__

#include "CORE_APPLICATION.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"
#include "GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h"
#include "GRAPHIC_OBJECT_SHAPE_SPHERE.h"
#include "GRAPHIC_OBJECT_SHAPE_LINE.h"
#include "GAMEPLAY_SCENE.h"
#include "CORE_MATH_VECTOR.h"
#include "APPLICATION_MAIN_WINDOW.h"
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
#include "NETWORK_SERVER.h"
#include "NETWORK_CLIENT.h"
#include "APPLICATION_COMMAND_MANAGER.h"
#include "GLOBAL_RESOURCES.h"
#include "GAME.h"

#include "ScriptEntity.h"
#include "ApplicationSoundBank.h"
#include "APPLICATION_COMMAND.h"

#if GRAPHIC_RENDERER_OPENGL
    #define GRAPHIC_RENDER_PLATFORM OPENGL
        #include "GRAPHIC_RENDERER.h"
    #undef GRAPHIC_RENDER_PLATFORM
#endif

#if GRAPHIC_RENDERER_DX_9
    #define GRAPHIC_RENDER_PLATFORM DX_9
        #include "GRAPHIC_RENDERER.h"
    #undef GRAPHIC_RENDER_PLATFORM
#endif

#if GRAPHIC_RENDERER_DX_11
    #define GRAPHIC_RENDER_PLATFORM DX_11
        #include "GRAPHIC_RENDERER.h"
    #undef GRAPHIC_RENDER_PLATFORM
#endif

XS_CLASS_BEGIN_WITH_ANCESTOR( MyTestApp, CORE_APPLICATION )

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( MyTestApp );

    //TODO Define inside state machine
    CORE_FIXED_STATE_MACHINE_DefineEvent( UPDATE_EVENT, float )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( GOTO_LOBBY )

    CORE_FIXED_STATE_MACHINE_DeclareBaseState( X_BASE_STATE, MyTestApp )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState( X_BASE_STATE, INITIAL_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( INITIAL_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( X_BASE_STATE, LOADING_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( LOADING_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( X_BASE_STATE, MENU_STATE );
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( GOTO_LOBBY )
    CORE_FIXED_STATE_MACHINE_EndDefineState( MENU_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( X_BASE_STATE, GAME_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT );
    CORE_FIXED_STATE_MACHINE_EndDefineState( GAME_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_STATE, PAUSE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PAUSE_STATE )

    MyTestApp();
    virtual ~MyTestApp();

    virtual void Initialize() override;
    virtual void Finalize() override;

    virtual void Update( float time_step ) override;
    virtual void Render() override;

    void SetDisplacement( float x, float y, float z ) {
        
        Displacement[0] = x;
        Displacement[1] = y;
        Displacement[2] = z;
    }

    void InitializeGraphics();

    void OnObjectPicked( GAMEPLAY_COMPONENT_ENTITY * entity );

    CORE_FILESYSTEM & GetDefaultFileystem() { return DefaultFileystem; }

    CORE_FIXED_STATE_MACHINE< X_BASE_STATE, MyTestApp > & GetStateMachine() { return StateMachine; }

    NETWORK_SERVER & GetServer() { return Server; }
    NETWORK_CLIENT & GetClient() { return Client; }

    void SetItIsClient( bool is_client ) { ItIsClient = is_client; }
    bool IsClient() const { return ItIsClient; }
    void SetItIsServer( bool is_server ) { ItIsServer = is_server; }
    bool IsServer() const { return ItIsServer; }

    void SetIsMultiplayer( bool is_multi ) { ItIsMultiplayer = is_multi; }
    bool IsMultiplayer() const { return ItIsMultiplayer; }

private :

    CORE_MATH_QUATERNION
        Lookat;
    CORE_FILESYSTEM
        DefaultFileystem;
    CORE_MATH_VECTOR
        Position,
        Displacement,
        PreviousPosition;
    int
        BoneLevel;
    ScriptEntity
        TestEntity;
    CORE_FIXED_STATE_MACHINE< X_BASE_STATE, MyTestApp >
        StateMachine;
    NETWORK_SERVER
        Server;
    NETWORK_CLIENT
        Client;
    bool
        ItIsClient,
        ItIsServer,
        ItIsMultiplayer;
    GAME
         * Game;
    GRAPHIC_CAMERA
        * Camera,
        * LightCamera;
    GRAPHIC_CAMERA_ORTHOGONAL
        * InterfaceCamera,
        * RenderTargetCamera;
    CORE_ABSTRACT_PROGRAM_FACTORY
        * LuaScript;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__Application__) */
