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

MULTIPOLY_APPLICATION::MULTIPOLY_APPLICATION() :
    CORE_APPLICATION(),
    Lookat(),
    DefaultFileystem(),
    Camera( NULL ),
    InterfaceCamera( NULL ),
    Game() {
    
    #if PLATFORM_OSX
        DefaultFileystem.Initialize( "/Users/CBE/DevelopProjects/game-engine-clean/PROJECTS/GAMES/MULTIPOLY/RESOURCES/" );
    #elif PLATFORM_IOS
        DefaultFileystem.Initialize( "None" );
    #elif PLATFORM_ANDROID
        //DefaultFileystem.Initialize( "None" );
    #elif PLATFORM_WINDOWS
        abort();
        DefaultFileystem.Initialize( "C:\\Users\\X\\Documents\\game-engine-clean\\RESOURCES\\" );
    #endif
    
    CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
    
    SERVICE_LOGGER_Error( "ALL APP create 2" );
    
    SetApplicationInstance( *this );
}

MULTIPOLY_APPLICATION::~MULTIPOLY_APPLICATION() {
    
}

void MULTIPOLY_APPLICATION::Initialize() {
    
    std::vector< GAME_PLAYER_MODEL > players;
    GAME_PLAYER_MODEL mod, mod2;
    mod.Name = std::string("Christophe");
    mod.Color = CORE_COLOR_Red;
    mod.IsHuman = true;
    
    mod2.Name = std::string("Charlotte");
    mod2.Color = CORE_COLOR_Blue;
    mod2.IsHuman = false;
    
    players.push_back(mod);
    players.push_back(mod2);
    
    InitializeGraphics();
    InitializeRandom();
    InitializeGameConfiguration();
    
    Game.Initialize( players );
    
    auto startup_splash_page = (GRAPHIC_UI_FRAME *) &APPLICATION_SCREENS_NAVIGATION::GetInstance().InitializeNavigation<SPLASH>( "splash" );
    startup_splash_page->Initialize();
}

void MULTIPOLY_APPLICATION::Finalize() {
    
}

void MULTIPOLY_APPLICATION::Update( float time_step ) {
    
    Game.Update( time_step );
    GRAPHIC_UI_SYSTEM::GetInstance().Update( time_step );
}

void MULTIPOLY_APPLICATION::Render() {
    
    CORE_MATH_VECTOR
        position(4.0f, -5.0f, 16.0f, 1.0f);
    
    Lookat[0] = -1.0f;
    Lookat[1] = 0.0f;
    Lookat[2] = 0.0f;
    Lookat[3] = 0.0f;
    
    Lookat.Normalize();
    
    Camera->UpdateCamera(position, Lookat);
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( Camera );
    Game.Render();
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( InterfaceCamera );
    GRAPHIC_UI_SYSTEM::GetInstance().Render(GRAPHIC_RENDERER::GetInstance());
}


void MULTIPOLY_APPLICATION::InitializeGraphics() {
    
    CORE_MATH_VECTOR
        position( 0.0f, 0.0f, 0.0f, 1.0f );
    
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

void MULTIPOLY_APPLICATION::InitializeRandom() {
    
    time_t rawtime;
    struct tm * timeinfo;
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    srand((unsigned int) rawtime);
}

void MULTIPOLY_APPLICATION::InitializeGameConfiguration() {
    
    APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StopOnStartGivesMoreMoney = false;
    APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StartCellMoney = 2000;
    APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StartUpMoney = 20000;
}

