//
//  Application.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "Application.h"

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_MEMORY.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "CORE_DATA_STREAM.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "AUDIO_SYSTEM.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATION_BLENDING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "CORE_DATA_LOADER.h"
#include "CORE_MEMORY.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"

#include <time.h>

#if PLATFORM_IOS //ie iOS
    #import <Foundation/Foundation.h>
#elif PLATFORM_ANDROID
    #include <android/asset_manager.h>
#endif

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( MyTestApp )
    //CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( GAMEPLAY_SCENE::PTR, MyTestApp, GetScene )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( MyTestApp )

MyTestApp::MyTestApp() :
    CORE_APPLICATION(),
    Position(),
    Lookat(),
    Camera(),
    LightCamera( NULL ),
    InterfaceCamera(),
    RenderTargetCamera(),
    DefaultFileystem(),
    Displacement( CORE_MATH_VECTOR::Zero ),
    Server(),
    Client(),
    Game( NULL ),
    ItIsClient( false ),
    ItIsServer( false ),
    ItIsMultiplayer( false ),
    LuaScript( NULL ) {
    
    SERVICE_LOGGER_Error( "ALL APP create 1" );
        
    #if PLATFORM_OSX
        DefaultFileystem.Initialize( "/Users/CBE/DevelopProjects/game-engine-clean/RESOURCES/" );
    #elif PLATFORM_IOS
        DefaultFileystem.Initialize( "None" );
    #elif PLATFORM_ANDROID
        //DefaultFileystem.Initialize( "None" );
    #elif PLATFORM_WINDOWS
        DefaultFileystem.Initialize( "C:\\Users\\X\\Documents\\game-engine-clean\\RESOURCES\\" );
    #endif
        
    CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
        
    SERVICE_LOGGER_Error( "ALL APP create 2" );

    SetApplicationInstance( *this );
        
    BoneLevel = 0;
        
    CORE_FIXED_STATE_InitializeState( StateMachine, MyTestApp::INITIAL_STATE, this );
}

MyTestApp::~MyTestApp() {

}


CORE_FIXED_STATE_DefineStateEnterEvent( MyTestApp::INITIAL_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( MyTestApp::INITIAL_STATE, UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_ChangeState( ((MyTestApp &) MyTestApp::GetApplicationInstance()).GetStateMachine(), ((MyTestApp &) MyTestApp::GetApplicationInstance()).LOADING_STATE);
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( MyTestApp::INITIAL_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEnterEvent( MyTestApp::LOADING_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( MyTestApp::LOADING_STATE, UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_ChangeState( ((MyTestApp &) MyTestApp::GetApplicationInstance()).GetStateMachine(), ((MyTestApp &) MyTestApp::GetApplicationInstance()).MENU_STATE);
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( MyTestApp::LOADING_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( MyTestApp::MENU_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( MyTestApp::MENU_STATE, UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_ChangeState( ((MyTestApp &) MyTestApp::GetApplicationInstance()).GetStateMachine(), ((MyTestApp &) MyTestApp::GetApplicationInstance()).GAME_STATE);
CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateEvent( MyTestApp::MENU_STATE, GOTO_LOBBY )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( MyTestApp::MENU_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( MyTestApp::GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( MyTestApp::GAME_STATE, UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_ChangeState( ((MyTestApp &) MyTestApp::GetApplicationInstance()).GetStateMachine(), ((MyTestApp &) MyTestApp::GetApplicationInstance()).PAUSE_STATE );
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( MyTestApp::GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()




CORE_FIXED_STATE_DefineStateEnterEvent( MyTestApp::PAUSE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateEvent( MyTestApp::PAUSE_STATE, UPDATE_EVENT )

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( MyTestApp::PAUSE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()

void MyTestApp::Initialize() {
    
    CORE_MATH_MATRIX m;
    m.YRotate(M_PI);
    Lookat.ToMatrix(m.GetRow(0));
    
    Lookat.Normalize();
    
    SERVICE_LOGGER_Error( "ALL APP Inititialize 0.11" );
    
    CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().Initialize();
    CORE_ABSTRACT_RUNTIME_LUA * runtime = (CORE_ABSTRACT_RUNTIME_LUA *) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[ CORE_ABSTRACT_PROGRAM_RUNTIME_Lua ];
    
    CORE_ABSTRACT_PROGRAM_BINDER::GetInstance().BindRuntime<CORE_ABSTRACT_RUNTIME_LUA>( *runtime );
    
    SERVICE_LOGGER_Error( "ALL APP Inititialize 1" );
    
    Position.Set( 0.0f, -50.0f, 0.0f, 1.0f);
    
    AUDIO_SYSTEM::GetInstance().Initialize();
    AUDIO_SYSTEM::GetInstance().GetBank().RegisterSoundFilePath(
        CORE_FILESYSTEM_PATH::FindFilePath( "bell-ringing-05" , "mp3", "AUDIO" ),
        ApplicationSoundBank::BellSound,
        AUDIO_BANK_SOUND_LOAD_OPTION_SoundStartupLoad, "mp3" );
    AUDIO_SYSTEM::GetInstance().GetBank().RegisterSoundFilePath(
        CORE_FILESYSTEM_PATH::FindFilePath( "Rammstein-Du-Hast" , "mp3", "AUDIO" ),
        ApplicationSoundBank::RammsteinSound,
        AUDIO_BANK_SOUND_LOAD_OPTION_StartupStreamMusic, "mp3" );
    AUDIO_SYSTEM::GetInstance().GetBank().RegisterSoundFilePath(
        CORE_FILESYSTEM_PATH::FindFilePath( "sound_bubbles" , "wav", "AUDIO" ),
        ApplicationSoundBank::BubbleSound,
        AUDIO_BANK_SOUND_LOAD_OPTION_SoundStartupLoad, "wav" );
    AUDIO_SYSTEM::GetInstance().GetBank().RegisterSoundFilePath(
        CORE_FILESYSTEM_PATH::FindFilePath( "sound_electric" , "wav", "AUDIO" ),
        ApplicationSoundBank::ElectricSound,
        AUDIO_BANK_SOUND_LOAD_OPTION_SoundStartupLoad, "wav" );
    
    AUDIO_SYSTEM::GetInstance().GetBank().Load();
   
    //TODO : init game later
    Game = new GAME();
    Game->Initialize();

    GAMEPLAY_COMPONENT_MANAGER::GetInstance().Initialize();
    
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    SERVICE_LOGGER_Error( "Camera : %d %d Lookat : %.2f %.2f %.2f %.2f ", ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight(), Lookat.X(), Lookat.Y(), Lookat.Z(), Lookat.W() );
    Camera = new GRAPHIC_CAMERA( 1.0f, 10000.0f, ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight(), Position, Lookat );
    LightCamera = new GRAPHIC_CAMERA_ORTHOGONAL( -256.0f, 256.0f, 256.0f, 256.0f, Position, Lookat );
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    interface_lookat.Normalize();
    
    RenderTargetCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight(), Position, interface_lookat );
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight(), Position, interface_lookat );
    
    InitializeGraphics();

    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( GLOBAL_RESOURCES::GetInstance().DirectionalLight );
    GRAPHIC_RENDERER::GetInstance().SetPointLight( GLOBAL_RESOURCES::GetInstance().PointLightOne, 0 );
    GRAPHIC_RENDERER::GetInstance().SetPointLight( GLOBAL_RESOURCES::GetInstance().PointLightTwo, 1 );
    GRAPHIC_RENDERER::GetInstance().SetSpotLight( GLOBAL_RESOURCES::GetInstance().SpotLightOne, 0 );
    GRAPHIC_RENDERER::GetInstance().SetSpotLight( GLOBAL_RESOURCES::GetInstance().SpotLightTwo, 1 );
    
    /*CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * > * picking_allback =
        new CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * >(
            &Wrapper1< MyTestApp, GAMEPLAY_COMPONENT_ENTITY * , &MyTestApp::OnObjectPicked>, this );
    
    for ( int i = 0; i < 3; i++ ) {
    
        GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
        
        component_entity->SetIndex( ComponentIndex++ );
        
        //should not be done like this
        
        component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position ), GAMEPLAY_COMPONENT_TYPE_Position );
        component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
        component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Physics ), GAMEPLAY_COMPONENT_TYPE_Physics );

        ( ( GAMEPLAY_COMPONENT_RENDER *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject( CubeObject );
        
        GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) Scene->GetRenderableSystemTable()[0];
        
        render_system->AddEntity( component_entity );
        render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
        
        CORE_MATH_VECTOR position( 0.0f + i * 10.0f, 0.0f, -30.0f, 1.0f );
        
        ( ( GAMEPLAY_COMPONENT_SYSTEM_PICKING * ) Scene->GetUpdatableSystemTable()[2])->AddEntity( component_entity );
        ( ( GAMEPLAY_COMPONENT_SYSTEM_PICKING * ) Scene->GetUpdatableSystemTable()[2])->SetOnPickedCallback( picking_allback );
        
        ( ( GAMEPLAY_COMPONENT_PHYSICS *) component_entity->GetComponent(GAMEPLAY_COMPONENT_TYPE_Physics))->ConfigureShapeSphere( position );
        
        bullet_system->AddEntity( component_entity );
        
        component_entity->SetPosition( position );
    }*/
    
    {
        SERVICE_LOGGER_Error( "ALL APP Inititialize 1.9" );
        
        GRAPHIC_FONT_MANAGER::GetInstance().LoadFont(
                                                     CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ),
        CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "fxb", "FONTS/" ),
        CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "png", "FONTS/" ) );
        
        APPLICATION_MAIN_WINDOW & main_window = ( APPLICATION_MAIN_WINDOW & ) APPLICATION_SCREENS_NAVIGATION::GetInstance().InitializeNavigation<APPLICATION_MAIN_WINDOW>("MainWindow");
        
        main_window.GetPlacement().Initialize( NULL,
                                             CORE_MATH_VECTOR::Zero,
                                             CORE_MATH_VECTOR( ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight() ),
                                             GRAPHIC_UI_Center );
        
        SERVICE_NETWORK_SYSTEM::GetInstance().Initialize();
        
        SERVICE_LOGGER_Error( "ALL APP Inititialize 2" );
        
        PreviousPosition = Camera->GetPosition();
        
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "game" , "lua", "SCRIPTS" );
        
        SERVICE_LOGGER_Error( "ALL APP Inititialize 2.22" );
        
        TestEntity.Initialize( path );
        
        GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() ) );
        GRAPHIC_UI_SYSTEM::GetInstance().RegisterView( &main_window, "MainWindow" );
        
        SERVICE_LOGGER_Error( "ALL APP Inititialize 2.23" );
        
        main_window.Initialize();
        /*LuaScript = CORE_ABSTRACT_PROGRAM_MANAGER::GetInstance().LoadProgram(
                                                                             path.GetPath(), CORE_ABSTRACT_PROGRAM_RUNTIME_Lua
                                                                             );*/
        
        //LuaScript->Execute();
        
        runtime->ExecuteCommand( "AUDIO_SYSTEM:GetInstance():PlayMusic( \"RammsteinSound\" )" );
    }
}

void MyTestApp::OnObjectPicked( GAMEPLAY_COMPONENT_ENTITY * entity  ) {
    
    CORE_MATH_VECTOR new_position( rand() % 10, rand() % 10, -30.0f, 1.0f );
    
    APPLICATION_COMMAND_MANAGER::GetInstance().CommandMoveCube( new_position, entity );
}

void MyTestApp::Finalize() {
    
    GAMEPLAY_COMPONENT_ANIMATION::FinalizeStaticMemory();
    GAMEPLAY_COMPONENT_RENDER::FinalizeStaticMemory();
    GAMEPLAY_COMPONENT_POSITION::FinalizeStaticMemory();
    GAMEPLAY_COMPONENT_PHYSICS::FinalizeStaticMemory();

    CORE_MEMORY_ObjectSafeDeallocation( Camera );
    CORE_MEMORY_ObjectSafeDeallocation( LightCamera );
    CORE_MEMORY_ObjectSafeDeallocation( InterfaceCamera );
    CORE_MEMORY_ObjectSafeDeallocation( RenderTargetCamera );
    CORE_MEMORY_ObjectSafeDeallocation( Game );
    
    Server.Finalize();
    Client.Finalize();
    
    APPLICATION_COMMAND_MANAGER::RemoveInstance();
    APPLICATION_SCREENS_NAVIGATION::RemoveInstance();
    AUDIO_SYSTEM::GetInstance().Finalize();
    AUDIO_SYSTEM::RemoveInstance();
    CORE_ABSTRACT_PROGRAM_BINDER::RemoveInstance();
    CORE_ABSTRACT_PROGRAM_MANAGER::RemoveInstance();
    CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::RemoveInstance();
    CORE_HELPERS_IDENTIFIER_SYSTEM::RemoveInstance();
    GAMEPLAY_COMPONENT_MANAGER::RemoveInstance();
    
    GLOBAL_RESOURCES::GetInstance().Finalize();
    GLOBAL_RESOURCES::RemoveInstance();
    
    GRAPHIC_FONT_MANAGER::RemoveInstance();
    GRAPHIC_MESH_MANAGER::RemoveInstance();
    GRAPHIC_PARTICLE_SYSTEM::RemoveInstance();
    GRAPHIC_RENDERER::RemoveInstance();
    GRAPHIC_UI_SYSTEM::RemoveInstance();
    PERIPHERIC_INTERACTION_SYSTEM::RemoveInstance();
    
    SERVICE_NETWORK_SYSTEM::GetInstance().Finalize();
    SERVICE_NETWORK_SYSTEM::RemoveInstance();
    
    DefaultFileystem.Finalize();
}

void MyTestApp::Render() {
    
    CORE_MATH_MATRIX current_mat( &Camera->GetProjectionMatrix()[0] );

    CORE_MATH_MATRIX inv( CORE_MATH_MATRIX::Identity );
    
    current_mat *= Camera->GetViewMatrix();
    current_mat.GetInverse( inv );
    
    #if PLATFORM_OSX
        memcpy(
               (void*) GLOBAL_RESOURCES::GetInstance().BlurEffect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::InverseCurrentModelViewIdentifier ).AttributeValue.Value.FloatMatrix4x4,
               (void*) &inv[0],
               16* sizeof(float) );
    #endif
    
    {
        #if PLATFORM_OSX
            {
                GRAPHIC_RENDERER::GetInstance().SetCamera( LightCamera );
                GRAPHIC_RENDERER::GetInstance().SetPassIndex(1);
                
                GLOBAL_RESOURCES::GetInstance().ShadowMapRenderTarget.Apply();
                Game->GetScene()->Render();
                
                static int c = 0;
                c++;
                if ( c % 100 == 0 ) {
                    
                    //ShadowMapRenderTarget.TargetTexture->SaveTo( CORE_FILESYSTEM_PATH::FindFilePath("rt", "png", "") );
                }
                GLOBAL_RESOURCES::GetInstance().ShadowMapRenderTarget.Discard();
            }
        #endif
        
        {
            
            GRAPHIC_RENDERER::GetInstance().SetPassIndex(0);
            GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
            
            #if PLATFORM_OSX
                GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera(LightCamera);
                GRAPHIC_RENDERER::GetInstance().SetDepthTexture( GLOBAL_RESOURCES::GetInstance().ShadowMapRenderTarget.TargetTexture);
            #endif

            
            Game->GetScene()->Render();
            
            #if PLATFORM_OSX
                GRAPHIC_RENDERER::GetInstance().SetShadowMapCamera( NULL );
                GRAPHIC_RENDERER::GetInstance().SetDepthTexture( NULL );
            #endif
            
        }
        //ShadowMapRenderTarget.Apply();
        
        
        /*GAMEPLAY_COMPONENT_POSITION * component;
        GAMEPLAY_COMPONENT_RENDER * component_grap;
        
        GRAPHIC_SYSTEM::SetPolygonMode( GRAPHIC_SYSTEM_POLYGON_FILL_MODE_Line );
        component = ( GAMEPLAY_COMPONENT_POSITION * ) component_entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        component_grap = ( GAMEPLAY_COMPONENT_RENDER * ) component_entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        
        for (int i = 0; i < NakedGirlObject->GetMeshTable().size(); i++ ) {
            
            GAMEPLAY_COMPONENT_POSITION * component = ( GAMEPLAY_COMPONENT_POSITION * ) component_entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
            
            CubeObject->SetPosition( NakedGirlObject->GetMeshTable()[i]->GetBoundingShape().GetPosition() + component->GetPosition() );
            CubeObject->SetOrientation( NakedGirlObject->GetMeshTable()[i]->GetBoundingShape().GetOrientation() + component->GetOrientation() );
            CubeObject->SetScaleFactor(NakedGirlObject->GetMeshTable()[i]->GetBoundingShape().GetHalfDiagonal() );
            
            CubeObject->Render( GRAPHIC_RENDERER::GetInstance() );
        }
        

        component = ( GAMEPLAY_COMPONENT_POSITION * ) component_entity2->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        component_grap = ( GAMEPLAY_COMPONENT_RENDER * ) component_entity2->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
        
        for (int i = 0; i < component_grap->GetObject()->GetMeshTable().size(); i++ ) {
            
            CubeObject->SetPosition( component_grap->GetObject()->GetMeshTable()[i]->GetBoundingShape().GetPosition() + component->GetPosition() );
            CubeObject->SetOrientation( component->GetOrientation() );
            
            if ( i == 4 ) {
                
                CORE_MATH_MATRIX & tr = component_grap->GetObject()->GetMeshTable()[i]->GetTransform();
                
                tr.ZRotate( 0.02f );
            }
            
            CORE_MATH_MATRIX mat;
            
            component_grap->GetObject()->GetMeshTable()[i]->GetBoundingShape().GetOrientation().ToMatrix( mat.GetRow(0) );
            
            CubeObject->GetMeshTable()[0]->SetTransform( component_grap->GetObject()->GetMeshTable()[i]->GetTransform() * mat );
            
            CubeObject->UpdateGeometry( component_grap->GetObject()->GetMeshTable()[i]->GetBoundingShape().GetPosition(), component_grap->GetObject()->GetMeshTable()[i]->GetBoundingShape().GetHalfDiagonal() );
            
            CubeObject->Render( GRAPHIC_RENDERER::GetInstance() );
        }
        
        GRAPHIC_SYSTEM::SetPolygonMode( GRAPHIC_SYSTEM_POLYGON_FILL_MODE_Full );
        */
        
        //PrimaryRenderTarget.Discard();
    }
    
    GRAPHIC_PARTICLE_SYSTEM::GetInstance().Render(GRAPHIC_RENDERER::GetInstance());
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( InterfaceCamera );
    
    GRAPHIC_UI_SYSTEM::GetInstance().Render( GRAPHIC_RENDERER::GetInstance() );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    GLOBAL_RESOURCES::GetInstance().Line->SetPosition( ( ( GAMEPLAY_COMPONENT_SYSTEM_PICKING * ) Game->GetScene()->GetUpdatableSystemTable()[2])->GetRay().GetOrigin() );
    GLOBAL_RESOURCES::GetInstance().Line->SetTarget( ( ( GAMEPLAY_COMPONENT_SYSTEM_PICKING * ) Game->GetScene()->GetUpdatableSystemTable()[2])->GetRay().GetDirection() );
    GLOBAL_RESOURCES::GetInstance().Line->Render(GRAPHIC_RENDERER::GetInstance());
    
#if PLATFORM_OSX
    GRAPHIC_RENDERER::GetInstance().SetCamera( RenderTargetCamera );
    GRAPHIC_RENDERER::GetInstance().EnableColor( false );
    {
        GLOBAL_RESOURCES::GetInstance().EffectPlan->GetShaderTable()[0] = &GLOBAL_RESOURCES::GetInstance().BloomEffect->GetProgram();
        GLOBAL_RESOURCES::GetInstance().EffectPlan->SetEffect( GLOBAL_RESOURCES::GetInstance().BloomEffect );
        GLOBAL_RESOURCES::GetInstance().TextureBlock->SetTexture( GLOBAL_RESOURCES::GetInstance().PrimaryRenderTarget.TargetTexture );
        
        GLOBAL_RESOURCES::GetInstance().BloomRenderTarget.Apply();
        GLOBAL_RESOURCES::GetInstance().EffectPlan->Render( GRAPHIC_RENDERER::GetInstance() );
        GLOBAL_RESOURCES::GetInstance().BloomRenderTarget.Discard();
    }
    
    {
        GLOBAL_RESOURCES::GetInstance().EffectPlan->GetShaderTable()[0] = &GLOBAL_RESOURCES::GetInstance().HorizontalBlurEffect->GetProgram();
        GLOBAL_RESOURCES::GetInstance().EffectPlan->SetEffect( GLOBAL_RESOURCES::GetInstance().HorizontalBlurEffect );
        GLOBAL_RESOURCES::GetInstance().TextureBlock->SetTexture( GLOBAL_RESOURCES::GetInstance().BloomRenderTarget.TargetTexture );
        
        GLOBAL_RESOURCES::GetInstance().GaussianRenderTarget.Apply();
        GLOBAL_RESOURCES::GetInstance().EffectPlan->Render( GRAPHIC_RENDERER::GetInstance() );
        GLOBAL_RESOURCES::GetInstance().GaussianRenderTarget.Discard();
    }
    
    {
        GLOBAL_RESOURCES::GetInstance().EffectPlan->GetShaderTable()[0] = &GLOBAL_RESOURCES::GetInstance().VerticalBlurEffect->GetProgram();
        GLOBAL_RESOURCES::GetInstance().EffectPlan->SetEffect(
                                                              GLOBAL_RESOURCES::GetInstance().VerticalBlurEffect );
        GLOBAL_RESOURCES::GetInstance().TextureBlock->SetTexture( GLOBAL_RESOURCES::GetInstance().GaussianRenderTarget.TargetTexture );
        
        GLOBAL_RESOURCES::GetInstance().GaussianRenderTarget.Apply();
        GLOBAL_RESOURCES::GetInstance().EffectPlan->Render( GRAPHIC_RENDERER::GetInstance() );
        GLOBAL_RESOURCES::GetInstance().GaussianRenderTarget.Discard();
    }
    
    {
        /*GLOBAL_RESOURCES::GetInstance().EffectPlan->GetShaderTable()[0] = &GLOBAL_RESOURCES::GetInstance().CombineBloomEffect->GetProgram();
        GLOBAL_RESOURCES::GetInstance().EffectPlan->SetEffect( GLOBAL_RESOURCES::GetInstance().CombineBloomEffect );
        GLOBAL_RESOURCES::GetInstance().TextureBlock->SetTexture( GLOBAL_RESOURCES::GetInstance().PrimaryRenderTarget.TargetTexture );
        
        GLOBAL_RESOURCES::GetInstance().EffectPlan->SetSecondTextureBlock( GLOBAL_RESOURCES::GetInstance().AlternateTextureBlock );
        GLOBAL_RESOURCES::GetInstance().EffectPlan->Render( GRAPHIC_RENDERER::GetInstance() );
        GLOBAL_RESOURCES::GetInstance().EffectPlan->SetSecondTextureBlock( NULL );*/
    }
    
    GRAPHIC_RENDERER::GetInstance().EnableColor( true );
#endif
    
    CORE_MATH_MATRIX previous_mat( &Camera->GetProjectionMatrix()[0] );
    
    previous_mat *= Camera->GetViewMatrix();
    
    #if PLATFORM_OSX
        memcpy(
           (void*) GLOBAL_RESOURCES::GetInstance().BlurEffect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PreviousModelViewProjectionIdentifier ).AttributeValue.Value.FloatMatrix4x4,
           (void*) &previous_mat[0],
           16* sizeof(float) );
    #endif
}

void MyTestApp::Update( float time_step ) {
    
    static float acc = 0.0f;
    
    acc += time_step;

    CORE_MATH_QUATERNION q;
    
    q.X(1.0f);
    q.Normalize();
    LightCamera->UpdateCamera(CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 1.0f), q);
    
    Camera->UpdateCamera(Position, Lookat);
    
    GRAPHIC_PARTICLE_SYSTEM::GetInstance().Update(time_step, Position, Lookat);
    UPDATE_EVENT ev(time_step);
    StateMachine.DispatchEvent( ev );
    
    //SERVICE_NETWORK_SYSTEM::GetInstance().Update( false );
    
    if ( ItIsClient ) {
        
        Client.Update( time_step );
    }
    else if ( ItIsServer )
    {
        Server.Update( time_step );
    }
    
    Game->Update( time_step );
    
    CORE_MATH_VECTOR deltaPosition = ( Camera->GetPosition() - PreviousPosition );
    
    PreviousPosition = Camera->GetPosition();
    
    GAMEPLAY_COMPONENT_POSITION * pos = (GAMEPLAY_COMPONENT_POSITION *) GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEntity( 1 )->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    pos->SetOrientation(CORE_MATH_QUATERNION( 0.0f, acc, 0.0, 1.0f ) );
    
    #if PLATFORM_OSX
        memcpy(
            (void*) GLOBAL_RESOURCES::GetInstance().BlurEffect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_EFFECT_SPEEDBLUR::ViewRayIdentifier ).AttributeValue.Value.FloatArray4,
            (void*) &deltaPosition[0],
            4* sizeof(float) );
        
        //printf ( "%f %f %f\n", deltaPosition[0], deltaPosition[1], deltaPosition[2]);
    #endif
    
    static float accumumated_time = 0.0f;
    
    //CORE_MATH_VECTOR light_dir( ( ( GAMEPLAY_COMPONENT_SYSTEM_PICKING * ) Scene->GetUpdatableSystemTable()[2])->GetRay().GetDirection() );
    
    {
        CORE_MATH_VECTOR light_dir( sinf(acc), 0.0f, cosf( acc), 1.0f );
        
        light_dir.Normalize();
        
        GLOBAL_RESOURCES::GetInstance().DirectionalLight->InternalLight.Directional.Direction[0] = -light_dir[0];
        GLOBAL_RESOURCES::GetInstance().DirectionalLight->InternalLight.Directional.Direction[1] = -light_dir[0];
        GLOBAL_RESOURCES::GetInstance().DirectionalLight->InternalLight.Directional.Direction[2] = -light_dir[2];
        
        GLOBAL_RESOURCES::GetInstance().PointLightOne->InternalLight.Point.Position[0] = -5.0f * cosf( acc * 1.33f);
        GLOBAL_RESOURCES::GetInstance().PointLightTwo->InternalLight.Point.Position[0] = 5.0f * cosf( acc* 0.5f);
        
        GLOBAL_RESOURCES::GetInstance().SpotLightOne->InternalLight.Spot.Direction[0] = -light_dir[0];
        GLOBAL_RESOURCES::GetInstance().SpotLightOne->InternalLight.Spot.Direction[1] = -light_dir[0];
        
        GLOBAL_RESOURCES::GetInstance().SpotLightTwo->InternalLight.Spot.Direction[0] = -light_dir[0];
        GLOBAL_RESOURCES::GetInstance().SpotLightTwo->InternalLight.Spot.Direction[1] = -light_dir[0];
    }
    
    CORE_MATH_VECTOR vector = PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetScreenCoordinates();
    CORE_MATH_VECTOR direction(250.0f, 0.0f, 0.0f, 0.0f );
    
    CORE_MATH_MATRIX inverse;
    
    CORE_MATH_QUATERNION rotation_quat;

    CORE_MATH_MATRIX rotation_mat( CORE_MATH_MATRIX::Identity );
    
    rotation_mat.Translate(CORE_MATH_VECTOR(1.0f, 0.0f, 0.0f, 0.0f ));
    rotation_mat.XRotate(M_PI_2);
    
    /*rotation_quat.X( 0.0f );
     rotation_quat.Y( 0.0f );
     rotation_quat.Z( 0.0f );
     rotation_quat.W( 1.0f );*/
    
    if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonClicked() ) {
        
        rotation_mat.XRotate( (vector[1]-0.5f)*2.0f * M_PI_2 );
        rotation_mat.ZRotate( (vector[0]-0.5f)*2.0f * M_PI_2 );
        
        printf( "x: %f   y: %f \n", vector[0], vector[1]);
    }

    rotation_mat.GetInverse(inverse);

    rotation_quat.FromMatrix( &rotation_mat[0] );
    rotation_quat.Normalize();
    
    Lookat[0] = rotation_quat[0];
    Lookat[1] = rotation_quat[1];
    Lookat[2] = rotation_quat[2];
    Lookat[3] = rotation_quat[3];
    
    Lookat.Normalize();
    
    CORE_MATH_VECTOR result( direction * inverse );
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_Z ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] = result[0] * time_step;
        add[1] = result[1] * time_step;
        add[2] = result[2] * time_step;
        
        rot.YRotate(-M_PI_2);
        
        Position += add*rot;
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_S ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        rot.YRotate(-M_PI_2);
        
        Position -= add*rot;
    }
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_A ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] = result[0] * time_step;
        add[1] = result[1] * time_step;
        add[2] = result[2] * time_step;
        
        rot.ZRotate(-M_PI_2);
        
        Position += add*rot;
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_E ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        rot.ZRotate(-M_PI_2);
        
        Position -= add*rot;
    }
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_Q ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        Position -= add*rot;
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_D ) ) {
        
        CORE_MATH_VECTOR add;
        CORE_MATH_MATRIX rot;
        
        add[0] =result[0] * time_step;
        add[1] =result[1] * time_step;
        add[2] =result[2] * time_step;
        
        Position += add*rot;
    }
    
    Position += Displacement * 5.0f;

    Camera->UpdateCamera(Position, Lookat);
    
    Game->GetScene()->Update( time_step );
    
    accumumated_time += time_step;
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetLeftButtonClicked() ) {
        
    }
    
    if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_P ) ) {
        BoneLevel++;
    }
    else if ( PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed(KEYBOARD_KEY_CHAR_M ) )
    {
        BoneLevel--;
    }
    
    if ( BoneLevel > 0 ) {
        
        CORE_MATH_QUATERNION quat(accumumated_time, 0.0f, 0.0f, 0.0f);
        
        quat.Normalize();
        
        quat.ToMatrix( (float* ) ((GRAPHIC_OBJECT_ANIMATED *)GLOBAL_RESOURCES::GetInstance().NakedGirlObject)->GetAnimationController()->GetAnimation( 0 )->GetSkeleton().GetRootSubSkeleton().SubSkelettonTable[0].Joint->GetInterPolatedMatrix() );
    }
    
    GRAPHIC_UI_SYSTEM::GetInstance().Update(time_step);
    
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().Update();
    AUDIO_SYSTEM::GetInstance().Update( time_step );
}

void MyTestApp::InitializeGraphics() {
    
    GLOBAL_RESOURCES::GetInstance().Initialize( Game->GetScene() );
}
