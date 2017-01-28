//
//  LOCH_STONE_APPLICATION.cpp
//  LochStone
//
//  Created by Christophe Bernard on 23/08/15.
//  Copyright (c) 2015 XFriends. All rights reserved.
//

#include "LOCH_STONE_APPLICATION.h"


#include "CORE_RUNTIME_ENVIRONMENT.h"

#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "CORE_MEMORY.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "AUDIO_SYSTEM.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "CORE_DATA_STREAM.h"

#include <time.h>

#if PLATFORM_IOS //ie iOS
#import <Foundation/Foundation.h>
#elif PLATFORM_ANDROID
#include <android/asset_manager.h>
#endif

#define RENDER_CALLBACK_ID 0

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( LOCH_STONE_APPLICATION )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( GAMEPLAY_SCENE::PTR, LOCH_STONE_APPLICATION, GetScene )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( LOCH_STONE_APPLICATION )

LOCH_STONE_APPLICATION::LOCH_STONE_APPLICATION() :
    CORE_APPLICATION(),
    Scene(NULL),
    Position(),
    Lookat(),
    Camera(),
    MainWindow(),
    InterfaceCamera(),
    DefaultFileystem() {
    
    #if PLATFORM_OSX
        DefaultFileystem.Initialize( "/Users/CBE/DevelopProjects/game-engine/RESOURCES/" );
    #elif PLATFORM_IOS
        DefaultFileystem.Initialize( "" );
    #elif PLATFORM_ANDROID
        DefaultFileystem.Initialize( "RESOURCES" );
    #endif
}

void LOCH_STONE_APPLICATION::Initialize() {
    
    Lookat.X(0.0f);
    Lookat.Y(0.0f);
    Lookat.Z(0.0f);
    Lookat.W(1.0f);
    Lookat.Normalize();
    
    CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
    
    Position.Set( 0.0f, 0.0f, 30.0f, 1.0f);
    
    AUDIO_SOUND sound;
    
    AUDIO_SYSTEM::GetInstance().Initialize();
    
    Scene = new GAMEPLAY_SCENE();
    
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    
    Scene->InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    GAMEPLAY_COMPONENT_MANAGER::GetInstance().Initialize();
    
    CORE_HELPER_CALLBACK * myCallback = new CORE_HELPER_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 10000.0f, ApplicationWindow->getWidth(), ApplicationWindow->getHeight(), Position, Lookat );
    
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, -1.0f, 0.0f, 0.0f );
    
    interface_lookat.Normalize();
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, ApplicationWindow->getWidth(), ApplicationWindow->getHeight(), Position, interface_lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    GRAPHIC_RENDERER::GetInstance().Initialize();
    
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    
    InitializeGraphics();
    
    CORE_HELPERS_IDENTIFIER file_identifier( "test2" );
    
    AUDIO_SYSTEM::GetInstance().Initialize();
    AUDIO_SYSTEM::GetInstance().PlaySound( file_identifier );
    
    MainWindow.SetShape( plan_object );
    MainWindow.GetPlacement().SetSize( CORE_MATH_VECTOR( ApplicationWindow->getWidth(), ApplicationWindow->getHeight(), 0.0f, 0.0f ) );
    MainWindow.Initialize();
}

void LOCH_STONE_APPLICATION::OnObjectPicked( GAMEPLAY_COMPONENT_ENTITY * entity  ) {
    
}

void LOCH_STONE_APPLICATION::Finalize() {
    
    DefaultFileystem.Finalize();
}

void LOCH_STONE_APPLICATION::Render() {
    
    static clock_t t = clock();
    
    clock_t time_offset = clock() - t;
    
    t+= time_offset;
    
    float time_step = 0.033f;
    
    Update( time_step );
}

void LOCH_STONE_APPLICATION::Update( float time_step ) {
    
    CORE_MATH_VECTOR direction;
    CORE_MATH_MATRIX inverse;
    
    direction = CORE_MATH_VECTOR::Zero;
    
    direction.Set( 0.0f, 0.0f, 75.0f, 0.0f );
    
    static float accumumated_time = 0.0f;
    
    CORE_MATH_QUATERNION rotation_quat;
    CORE_MATH_MATRIX rotation_mat( CORE_MATH_MATRIX::Identity );
    
    rotation_quat.X( 0.0f );
    rotation_quat.Y( 0.0f );
    rotation_quat.Z( 0.0f );
    rotation_quat.W( 1.0f );
    
    CORE_MATH_VECTOR vector;
    
    vector = PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetScreenCoordinates();
    
    Lookat[0] = rotation_quat[0];
    Lookat[1] = rotation_quat[1];
    Lookat[2] = rotation_quat[2];
    Lookat[3] = rotation_quat[3];
    
    Lookat.Normalize();
    
    CORE_MATH_VECTOR result(direction * rotation_mat);
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_Z ) ) {
        
        CORE_MATH_VECTOR add;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        Position += add;
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_S ) ) {
        
        CORE_MATH_VECTOR add;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        Position -= add;
    }
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_A ) ) {
        
        Position.Set( Position[0], Position[1] + time_step * 75.0f, Position[2], 1.0f);
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_E ) ) {
        
        Position.Set( Position[0], Position[1] - time_step * 75.0f, Position[2], 1.0f);
    }
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_Q ) ) {
        
        Position.Set( Position[0] + time_step * 75.0f, Position[1], Position[2], 1.0f);
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_D ) ) {
        
        Position.Set( Position[0] - time_step * 75.0f, Position[1], Position[2], 1.0f );
    }
    
    Camera->UpdateCamera(Position, Lookat);
    
    Scene->Update( time_step );
    
    accumumated_time += time_step;
    
    if ( accumumated_time > 3.0f ) {
        
        accumumated_time = 0.0f;
    }
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonClicked() ) {
        
    }
    
    MainWindow.Update( time_step );
    Scene->Render();
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( InterfaceCamera );
    
    MainWindow.Render( GRAPHIC_RENDERER::GetInstance() );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().Update();
    AUDIO_SYSTEM::GetInstance().Update( time_step );
}

void LOCH_STONE_APPLICATION::InitializeGraphics() {
    
}