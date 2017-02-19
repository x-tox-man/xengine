//
//  GRAPHIC_SHADER_EFFECT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GRAPHIC_SHADER_EFFECT::GRAPHIC_SHADER_EFFECT() :
    Program() {
    
}

GRAPHIC_SHADER_EFFECT::~GRAPHIC_SHADER_EFFECT() {

}

void GRAPHIC_SHADER_EFFECT::Initialize( const GRAPHIC_SHADER_BIND & bind ) {
    
    Bind = bind;
    
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT Initialize 1" );
    
    Program.GetProgram()->LinkTogether( bind );
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT Initialize 2" );
    Program.CopyAttributes();
    
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT Initialize 3" );
    
    BindAttributes();
    
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT Initialize 4" );
}

void GRAPHIC_SHADER_EFFECT::BindAttributes() {

}

void GRAPHIC_SHADER_EFFECT::Apply() {
    
    GetProgram().Enable();
}

void GRAPHIC_SHADER_EFFECT::Release() {
    
}

GRAPHIC_SHADER_EFFECT::PTR GRAPHIC_SHADER_EFFECT::LoadEffectWithVertexAndFragmentPath( const CORE_FILESYSTEM_PATH & vertex_path, const CORE_FILESYSTEM_PATH & fragment_path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    
    GRAPHIC_SHADER_EFFECT::PTR effect = new GRAPHIC_SHADER_EFFECT;
    
    effect->GetProgram().SetProgram( new GRAPHIC_SHADER_PROGRAM );
    
    effect->GetProgram().GetProgram()->Initialize();
    
#if OPENGLES2
    effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( vertex_path.GetFileName(), "vsh", "OPENGLES2" ), GRAPHIC_SHADER_Vertex );
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT_LOADER loading 3");
    effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( fragment_path.GetFileName(), "fsh", "OPENGLES2" ), GRAPHIC_SHADER_Pixel );
#elif OPENGL2PLUS
    effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( vertex_path.GetFileName(), "", "OPENGL2" ), GRAPHIC_SHADER_Vertex );
    effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( fragment_path.GetFileName(), "", "OPENGL2" ), GRAPHIC_SHADER_Pixel );
#else
    CORE_RUNTIME_Abort();
#endif
    
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT_LOADER loaded");
    
    return effect;
}
