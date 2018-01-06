//
//  APPLICATION.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "APPLICATION.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "AUDIO_SYSTEM.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "TOOLS_LOCALE_SYSTEM.h"
#include "CORE_DATA_UTF8_TEXT.h"

APPLICATION::APPLICATION() :
    CORE_APPLICATION(),
    DefaultFileystem()
{
    
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
}

APPLICATION::~APPLICATION() {
    
}

void APPLICATION::Initialize() {
   
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
}

void APPLICATION::Finalize() {
    
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
    
    DefaultFileystem.Finalize();
}

void APPLICATION::Update( float time_step ) {
    
    GRAPHIC_UI_SYSTEM::GetInstance().Update( time_step );
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().Update();
}

void APPLICATION::Render() {
    
    GRAPHIC_UI_SYSTEM::GetInstance().Render( GRAPHIC_RENDERER::GetInstance() );
}


