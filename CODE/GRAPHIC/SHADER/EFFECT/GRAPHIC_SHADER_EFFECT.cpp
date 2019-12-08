//
//  GRAPHIC_SHADER_EFFECT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_SYSTEM.h"
#include "GRAPHIC_MATERIAL_COLLECTION.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_SHADER_EFFECT )
    XS_DEFINE_ClassMember( "Bind", GRAPHIC_SHADER_BIND, Bind )
    XS_DEFINE_ClassMember( "MaterialCollection", GRAPHIC_MATERIAL_COLLECTION::PTR, MaterialCollection )
XS_END_INTERNAL_MEMORY_LAYOUT


GRAPHIC_SHADER_EFFECT::GRAPHIC_SHADER_EFFECT() :
    GRAPHIC_SHADER_EFFECT_RESOURCE_ANCESTOR(),
    Program(),
    Bind(),
    MaterialCollection( new GRAPHIC_MATERIAL_COLLECTION() ) {
    
}

GRAPHIC_SHADER_EFFECT::GRAPHIC_SHADER_EFFECT( const GRAPHIC_SHADER_EFFECT & other ) :
    GRAPHIC_SHADER_EFFECT_RESOURCE_ANCESTOR(),
    Program( other.Program ),
    Bind( other.Bind ),
    MaterialCollection( other.MaterialCollection ) {
    
}

GRAPHIC_SHADER_EFFECT::~GRAPHIC_SHADER_EFFECT() {
    
    CORE_MEMORY_ObjectSafeDeallocation( MaterialCollection);
}

void GRAPHIC_SHADER_EFFECT::Initialize( const GRAPHIC_SHADER_BIND & bind ) {
    
    Bind = bind;
    
#if DEBUG
    assert( Program.GetShaderAttributeTable().size() == 0 );
#endif
    
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

void GRAPHIC_SHADER_EFFECT::BindAttribute( GRAPHIC_SHADER_ATTRIBUTE &shader_attribute, const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    Program.GetProgram()->BindAttribute( shader_attribute, identifier);
}

void GRAPHIC_SHADER_EFFECT::Apply(GRAPHIC_RENDERER & renderer, bool does_lighting, bool does_texturing ) {
    
    GetProgram().Enable( renderer );
    
    MaterialCollection->Apply(renderer, &GetProgram(), does_lighting, does_texturing );
    
    if ( GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::FrameResolution ).AttributeIndex >= 0 ) {
        
        GRAPHIC_SYSTEM_ApplyVector( GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::FrameResolution ).AttributeIndex, 2, GetProgram().GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::FrameResolution ).AttributeValue.Value.FloatArray2 );
    }
}

void GRAPHIC_SHADER_EFFECT::SelectMaterial( const char * material_name ) {
    
    auto material = MaterialCollection->GetMaterialForName( material_name );
    if ( material )
        material->ApplyTexture( &Program );
    else
        MaterialCollection->GetDefaultMaterial()->ApplyTexture( &Program );
}

void GRAPHIC_SHADER_EFFECT::Discard() {
    
    GetProgram().Disable();
}

void GRAPHIC_SHADER_EFFECT::Release() {
    
    CORE_RUNTIME_Abort();
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
    
    effect->GetMaterialCollection()->LoadMaterialForName( material_name );
    
    return effect;
}

void GRAPHIC_SHADER_EFFECT::UpdateMatrix( GRAPHIC_RENDERER & renderer, GRAPHIC_SHADER_ATTRIBUTE & attribute, const float * matrix ) {
    
    if ( attribute.AttributeIndex >= 0 ) {
        
        GRAPHIC_SYSTEM_ApplyMatrix( attribute.AttributeIndex, 1, 1, matrix );
    }
}

void GRAPHIC_SHADER_EFFECT::UpdateFloatArray( GRAPHIC_RENDERER & renderer, GRAPHIC_SHADER_ATTRIBUTE & attribute, unsigned int count, float * array) {
    
    if ( attribute.AttributeIndex >= 0 ) {
        
        GRAPHIC_SYSTEM_ApplyVector( attribute.AttributeIndex, count, array );
    }
}

void GRAPHIC_SHADER_EFFECT::UpdateFloat( GRAPHIC_RENDERER & renderer, GRAPHIC_SHADER_ATTRIBUTE & attribute, const float value) {
    
    if ( attribute.AttributeIndex >= 0 ) {
        
        GRAPHIC_SYSTEM_ApplyFloat( attribute.AttributeIndex, value )
    }
}
