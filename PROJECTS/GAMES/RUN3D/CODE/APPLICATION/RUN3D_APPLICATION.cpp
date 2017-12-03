//
//  RUN3D_APPLICATION.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "RUN3D_APPLICATION.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "AUDIO_SYSTEM.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "R3D_RESOURCES.h"
#include "btBulletDynamicsCommon.h"
#include "PHYSICS_COLLISION_FILTER.h"
#include "R3D_UI_FRAME.h"

RUN3D_APPLICATION::RUN3D_APPLICATION() :
    CORE_APPLICATION(),
    DefaultFileystem(),
    GameRenderer(),
    Game() {
    
    #if PLATFORM_OSX
        DefaultFileystem.Initialize( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/" );
    #elif PLATFORM_IOS
        DefaultFileystem.Initialize( "None" );
    #elif PLATFORM_ANDROID
        DefaultFileystem.Initialize( "None" );
    #elif PLATFORM_WINDOWS
        DefaultFileystem.Initialize( "C:\\Users\\X\\Documents\\xengine\\RESOURCES\\" );
    #endif
    
    CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
    
    SetApplicationInstance( *this );
    
    #if !PLATFORM_ANDROID
        AUDIO_SYSTEM::GetInstance().Initialize();
    #endif
}

RUN3D_APPLICATION::~RUN3D_APPLICATION() {
    
}

void RUN3D_APPLICATION::Initialize() {
    
    InitializeGraphics();
    
    InitializeGameConfiguration();
    
    InitializePhysics();
    
    CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().Initialize();
    CORE_ABSTRACT_RUNTIME_LUA * runtime = (CORE_ABSTRACT_RUNTIME_LUA *) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[ CORE_ABSTRACT_PROGRAM_RUNTIME_Lua ];
    
    CORE_ABSTRACT_PROGRAM_BINDER::GetInstance().BindRuntime<CORE_ABSTRACT_RUNTIME_LUA>( *runtime );
    
    Game.Initialize();
    
    AUDIO_SYSTEM::GetInstance().GetBank().Load();
    
    auto frame = new R3D_UI_FRAME;
    frame->Initialize();
    GRAPHIC_UI_SYSTEM::GetInstance().RegisterView( frame, "main" );
}

void RUN3D_APPLICATION::Finalize() {
    
    Game.Finalize();
    
    AUDIO_SYSTEM::GetInstance().Finalize();
    AUDIO_SYSTEM::RemoveInstance();
    CORE_ABSTRACT_PROGRAM_BINDER::RemoveInstance();
    CORE_ABSTRACT_PROGRAM_MANAGER::RemoveInstance();
    CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::RemoveInstance();
    CORE_HELPERS_IDENTIFIER_SYSTEM::RemoveInstance();
    GAMEPLAY_COMPONENT_MANAGER::RemoveInstance();
    
    GRAPHIC_FONT_MANAGER::RemoveInstance();
    GRAPHIC_MESH_MANAGER::RemoveInstance();
    GRAPHIC_PARTICLE_SYSTEM::RemoveInstance();
    GRAPHIC_RENDERER::RemoveInstance();
    PERIPHERIC_INTERACTION_SYSTEM::RemoveInstance();
    
    //SERVICE_NETWORK_SYSTEM::GetInstance().Finalize();
    //SERVICE_NETWORK_SYSTEM::RemoveInstance();
    
    DefaultFileystem.Finalize();
}

void RUN3D_APPLICATION::Update( float time_step ) {
    
    static float acc = 0.0f;
    const float step = 1.0f / 60.0f;
    
    AUDIO_SYSTEM::GetInstance().Update( time_step );
    
    acc += time_step;

    while ( acc > step) {
        acc -= step;
        
        Game.Update( step );
        
        GRAPHIC_PARTICLE_SYSTEM::GetInstance().Update( time_step, CORE_MATH_VECTOR(), CORE_MATH_QUATERNION() );
    }
    
    GRAPHIC_UI_SYSTEM::GetInstance().Update( time_step );
}

void RUN3D_APPLICATION::Render() {
    
    GameRenderer.Render( GRAPHIC_RENDERER::GetInstance() );
}

void RUN3D_APPLICATION::InitializeGraphics() {
    
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    
    R3D_RESOURCES::GetInstance().Initialize();
    
    GRAPHIC_UI_SYSTEM::GetInstance().Initialize();
    
    GameRenderer.Initialize();
}

void RUN3D_APPLICATION::InitializeGameConfiguration() {
    
}

void RUN3D_APPLICATION::InitializePhysics() {

}

void RUN3D_APPLICATION::SetCamera( GRAPHIC_CAMERA::PTR camera ) {
    
    GameRenderer.SetCamera( camera );
}

