//
//  MULTIPOLY_APPLICATION.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "MULTIPOLY_APPLICATION.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "SPLASH.h"
#include "GLOBAL_RESOURCES.h"
#include "GAME_PLAYER_MODEL.h"
#include "MAIN_MENU_PAGE.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "AUDIO_SYSTEM.h"

MULTIPOLY_APPLICATION::MULTIPOLY_APPLICATION() :
    CORE_APPLICATION(),
    Lookat(),
    DefaultFileystem(),
    Camera( NULL ),
    InterfaceCamera( NULL ),
    Game(),
    NetworkManager() {
    
    #if PLATFORM_OSX
        DefaultFileystem.Initialize( "/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/RESOURCES/" );
    #elif PLATFORM_IOS
        DefaultFileystem.Initialize( "None" );
    #elif PLATFORM_ANDROID
        DefaultFileystem.Initialize( "None" );
    #elif PLATFORM_WINDOWS
        abort();
        DefaultFileystem.Initialize( "C:\\Users\\X\\Documents\\game-engine-clean\\RESOURCES\\" );
    #endif
    
    CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
    
    SERVICE_LOGGER_Error( "ALL APP create 2" );
    
    SetApplicationInstance( *this );
    
    #if !PLATFORM_ANDROID
        AUDIO_SYSTEM::GetInstance().Initialize();
    #endif
        
    SERVICE_LOGGER_Error( "ALL APP create 2,1" );
}

MULTIPOLY_APPLICATION::~MULTIPOLY_APPLICATION() {
    
}

void MULTIPOLY_APPLICATION::Initialize() {
    
    SERVICE_LOGGER_Error( "ALL APP create 2,5" );
    
    InitializeGraphics();
    ResetRandom();
    InitializeGameConfiguration();
    
    SERVICE_LOGGER_Error( "ALL APP create 3" );
    
    AUDIO_SYSTEM::GetInstance().GetBank().RegisterSoundFilePath(
        CORE_FILESYSTEM_PATH::FindFilePath( "rammstein" , "mp3", "SOUNDS" ),
        CORE_HELPERS_IDENTIFIER( "rammstein" ),
        AUDIO_BANK_SOUND_LOAD_OPTION_StartupStreamMusic, "mp3" );
    
    AUDIO_SYSTEM::GetInstance().GetBank().Load();
    
    AUDIO_SYSTEM::GetInstance().PlayMusic( CORE_HELPERS_IDENTIFIER( "rammstein" ) );
    Game.Initialize();
    
    auto startup_splash_page = (GRAPHIC_UI_FRAME *) &APPLICATION_SCREENS_NAVIGATION::GetInstance().InitializeNavigation<SPLASH>( "splash" );
    
    startup_splash_page->Initialize();
    NetworkManager.Initialize();
}

void MULTIPOLY_APPLICATION::Finalize() {
    
    CORE_MEMORY_ObjectSafeDeallocation( Camera );
    CORE_MEMORY_ObjectSafeDeallocation( InterfaceCamera );
    
    Game.Finalize();
    
    NetworkManager.Finalize();
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

void MULTIPOLY_APPLICATION::Update( float time_step ) {
    
    AUDIO_SYSTEM::GetInstance().Update( time_step );
    
    NetworkManager.Update( time_step );
    
    Game.Update( time_step );
    GRAPHIC_UI_SYSTEM::GetInstance().Update( time_step );
}

void MULTIPOLY_APPLICATION::Render() {
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    Game.Render();
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( InterfaceCamera );
    GRAPHIC_UI_SYSTEM::GetInstance().Render(GRAPHIC_RENDERER::GetInstance());
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    
    GLOBAL_RESOURCES::GetInstance().Line->SetPosition( ( ( GAMEPLAY_COMPONENT_SYSTEM_PICKING * ) Game.GetScene().GetUpdatableSystemTable()[2])->GetRay().GetOrigin() );
    GLOBAL_RESOURCES::GetInstance().Line->SetTarget( ( ( GAMEPLAY_COMPONENT_SYSTEM_PICKING * ) Game.GetScene().GetUpdatableSystemTable()[2])->GetRay().GetDirection() );
    GLOBAL_RESOURCES::GetInstance().Line->Render(GRAPHIC_RENDERER::GetInstance());
}


void MULTIPOLY_APPLICATION::InitializeGraphics() {
    
    CORE_MATH_VECTOR
        position(4.0f, 5.0f, 19.0f, 1.0f);
    
    Lookat[0] = -1.0f;
    Lookat[1] = 0.0f;
    Lookat[2] = 0.0f;
    Lookat[3] = 0.0f;
    
    Lookat.Normalize();
    
    Camera = new GRAPHIC_CAMERA( 1.0f, 10000.0f, ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight(), position, Lookat );
    
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() ) );
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight(), CORE_MATH_VECTOR(0.0f, 0.0f), interface_lookat );
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    
    GLOBAL_RESOURCES::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetDirectionalLight( GLOBAL_RESOURCES::GetInstance().DirectionalLight );
    GRAPHIC_RENDERER::GetInstance().SetPointLight( GLOBAL_RESOURCES::GetInstance().PointLightOne, 0 );
    GRAPHIC_RENDERER::GetInstance().SetPointLight( GLOBAL_RESOURCES::GetInstance().PointLightTwo, 1 );
    GRAPHIC_RENDERER::GetInstance().SetSpotLight( GLOBAL_RESOURCES::GetInstance().SpotLightOne, 0 );
    GRAPHIC_RENDERER::GetInstance().SetSpotLight( GLOBAL_RESOURCES::GetInstance().SpotLightTwo, 1 );
}

void MULTIPOLY_APPLICATION::ResetRandom() {
    
    time_t
        rawtime;
    struct tm
        * timeinfo;
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    Seed = (unsigned int) rawtime;
    
    srand( Seed );
}

void MULTIPOLY_APPLICATION::InitializeGameConfiguration() {
    
    APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StopOnStartGivesMoreMoney = false;
    APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StartCellMoney = 200;
    APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StartUpMoney = APPLICATION_PLAYER_BASE_MONEY;
}

