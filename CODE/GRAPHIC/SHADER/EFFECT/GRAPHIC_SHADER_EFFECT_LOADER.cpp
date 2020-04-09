//
//  GRAPHIC_SHADER_EFFECT_LOADER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_APPLICATION.h"
#include "CORE_DATA_STREAM.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_RENDERER_STATE_DESCRIPTOR.h"

GRAPHIC_SHADER_EFFECT_LOADER::GRAPHIC_SHADER_EFFECT_LOADER() :
    RESOURCE_LOADER() {
    
}

GRAPHIC_SHADER_EFFECT_LOADER::~GRAPHIC_SHADER_EFFECT_LOADER() {
    
}

GRAPHIC_SHADER_EFFECT * GRAPHIC_SHADER_EFFECT_LOADER::Load( const CORE_FILESYSTEM_PATH & file, int resource_load_flag, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_SHADER_EFFECT::PTR effect = new GRAPHIC_SHADER_EFFECT;
    effect->GetProgram().SetProgram( new GRAPHIC_SHADER_PROGRAM );
    effect->GetProgram().GetProgram()->Initialize();
    
    CORE_FILESYSTEM_PATH file_without_extension = file.RemoveExtension();
    
    //0 is default so we must ensure our vertex and fragment are loaded, specific case will be handled crappily
    if ( resource_load_flag == 0 || resource_load_flag & GRAPHIC_SHADER_LOAD_OPTION_Vertex ) {
        
        effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( file_without_extension.GetFileName(), "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ), GRAPHIC_SHADER_Vertex );
    }
    
    if ( resource_load_flag == 0 || resource_load_flag & GRAPHIC_SHADER_LOAD_OPTION_Fragment ) {
        effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( file_without_extension.GetFileName(), "fsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ), GRAPHIC_SHADER_Pixel );
    }
    
    if ( resource_load_flag & GRAPHIC_SHADER_LOAD_OPTION_Tesselate ) {
        
        effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( file_without_extension.GetFileName(), "csh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ), GRAPHIC_SHADER_HullControlShader );
        effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( file_without_extension.GetFileName(), "esh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ), GRAPHIC_SHADER_TessellateEvaluation );
    }
    
    return effect;
}

GRAPHIC_SHADER_EFFECT * GRAPHIC_SHADER_EFFECT_LOADER::Load( CORE_DATA_STREAM & stream, int resource_load_flag, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    return NULL;
}

void GRAPHIC_SHADER_EFFECT_LOADER::ReloadResource( GRAPHIC_SHADER_EFFECT * resource_to_reload ) {

    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
    
    resource_to_reload->GetProgram().SetProgram( new GRAPHIC_SHADER_PROGRAM );
    resource_to_reload->GetProgram().GetProgram()->Initialize();
    
    resource_to_reload->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( resource_to_reload->GetPath().GetFileName(), "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath(), true ), GRAPHIC_SHADER_Vertex );
    resource_to_reload->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( resource_to_reload->GetPath().GetFileName(), "fsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath(), true ), GRAPHIC_SHADER_Pixel );
    
    /*resource_to_reload->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( resource_to_reload->GetPath().GetFileName(), "csh", GRAPHIC_SYSTEM::GetShaderDirectoryPath(), true ), GRAPHIC_SHADER_HullControlShader );
    resource_to_reload->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( resource_to_reload->GetPath().GetFileName(), "esh", GRAPHIC_SYSTEM::GetShaderDirectoryPath(), true ), GRAPHIC_SHADER_TessellateEvaluation );*/
    
    resource_to_reload->GetProgram().GetShaderAttributeTable().clear();
    resource_to_reload->Initialize( resource_to_reload->GetShaderBind() );
    
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
}
