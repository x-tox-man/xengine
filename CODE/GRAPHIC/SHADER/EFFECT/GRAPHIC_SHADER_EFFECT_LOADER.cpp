//
//  GRAPHIC_SHADER_EFFECT_LOADER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_APPLICATION.h"
#include "CORE_DATA_STREAM.h"

GRAPHIC_SHADER_EFFECT_LOADER::GRAPHIC_SHADER_EFFECT_LOADER() :
    RESOURCE_LOADER() {
    
}

GRAPHIC_SHADER_EFFECT_LOADER::~GRAPHIC_SHADER_EFFECT_LOADER() {
    
}

GRAPHIC_SHADER_EFFECT * GRAPHIC_SHADER_EFFECT_LOADER::Load( const CORE_FILESYSTEM_PATH & file, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_SHADER_EFFECT::PTR effect = new GRAPHIC_SHADER_EFFECT;
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT_LOADER loading 1");
    effect->GetProgram().SetProgram( new GRAPHIC_SHADER_PROGRAM );
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT_LOADER loading 1?5");
    effect->GetProgram().GetProgram()->Initialize();
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT_LOADER loading 2");
    
    CORE_FILESYSTEM_PATH file_without_extension = file.RemoveExtension();
    
    effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( file_without_extension.GetFileName(), "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ), GRAPHIC_SHADER_Vertex );
    effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( file_without_extension.GetFileName(), "fsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ), GRAPHIC_SHADER_Pixel );
    
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT_LOADER loaded");
    
    return effect;
}

GRAPHIC_SHADER_EFFECT * GRAPHIC_SHADER_EFFECT_LOADER::Load( CORE_DATA_STREAM & stream, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    return NULL;
}

void GRAPHIC_SHADER_EFFECT_LOADER::ReloadResource( GRAPHIC_SHADER_EFFECT * resource_to_reload ) {
    
    //resource_to_reload->GetProgram().GetProgram()->Finalize();
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    
    resource_to_reload->GetProgram().SetProgram( new GRAPHIC_SHADER_PROGRAM );
    resource_to_reload->GetProgram().GetProgram()->Initialize();
    
    resource_to_reload->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( resource_to_reload->GetPath().GetFileName(), "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath(), true ), GRAPHIC_SHADER_Vertex );
    resource_to_reload->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( resource_to_reload->GetPath().GetFileName(), "fsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath(), true ), GRAPHIC_SHADER_Pixel );
    
    resource_to_reload->Initialize( resource_to_reload->GetSahderBind() );
    
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
}
