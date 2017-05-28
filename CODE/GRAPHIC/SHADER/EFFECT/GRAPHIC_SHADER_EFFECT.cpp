//
//  GRAPHIC_SHADER_EFFECT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_SYSTEM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_SHADER_EFFECT )
    XS_DEFINE_ClassMember( GRAPHIC_SHADER_BIND, Bind )
    XS_DEFINE_ClassMember( GRAPHIC_MATERIAL::PTR, Material )
XS_END_INTERNAL_MEMORY_LAYOUT


GRAPHIC_SHADER_EFFECT::GRAPHIC_SHADER_EFFECT() :
    Program(),
    Bind(),
    Material( NULL ) {
    
}

GRAPHIC_SHADER_EFFECT::~GRAPHIC_SHADER_EFFECT() {

}

void GRAPHIC_SHADER_EFFECT::Initialize( const GRAPHIC_SHADER_BIND & bind ) {
    
    Bind = bind;
    
    //SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT Initialize 1" );
    
    Program.GetProgram()->LinkTogether( bind );
    //SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT Initialize 2" );
    Program.CopyAttributes();
    
    //SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT Initialize 3" );
    
    BindAttributes();
    
    //SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT Initialize 4" );
}

void GRAPHIC_SHADER_EFFECT::BindAttributes() {

}

void GRAPHIC_SHADER_EFFECT::Apply(GRAPHIC_RENDERER & renderer ) {
    
    GetProgram().Enable();
    Material->Apply(renderer, &GetProgram() );
}

void GRAPHIC_SHADER_EFFECT::Discard() {
    
    GetProgram().Disable();
}

void GRAPHIC_SHADER_EFFECT::Release() {
    
    abort();
}

GRAPHIC_SHADER_EFFECT::PTR GRAPHIC_SHADER_EFFECT::LoadEffectWithVertexAndFragmentPath( const CORE_FILESYSTEM_PATH & vertex_path, const CORE_FILESYSTEM_PATH & fragment_path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_SHADER_EFFECT::PTR effect = new GRAPHIC_SHADER_EFFECT;
    
    effect->GetProgram().SetProgram( new GRAPHIC_SHADER_PROGRAM );
    
    effect->GetProgram().GetProgram()->Initialize();
    
    effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( vertex_path.GetFileName(), "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ), GRAPHIC_SHADER_Vertex );
    effect->GetProgram().GetProgram()->LoadPartial( CORE_FILESYSTEM_PATH::FindFilePath( fragment_path.GetFileName(), "fsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ), GRAPHIC_SHADER_Pixel );
    
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_EFFECT_LOADER loaded");
    
    return effect;
}

GRAPHIC_SHADER_EFFECT::PTR GRAPHIC_SHADER_EFFECT::LoadEffectWithVertexAndFragmentPathAndMaterial( const CORE_FILESYSTEM_PATH & vertex_path, const CORE_FILESYSTEM_PATH & fragment_path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const char * material_name ) {
    
    GRAPHIC_SHADER_EFFECT::PTR effect = LoadEffectWithVertexAndFragmentPath( vertex_path, fragment_path, identifier );
    
    GRAPHIC_MATERIAL::PTR material = new GRAPHIC_MATERIAL( material_name );
    
    effect->SetMaterial( material );
    
    return effect;
}
