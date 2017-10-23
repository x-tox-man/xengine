//
//  GRAPHIC_SHADER_PROGRAM_DATA_PROXY.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_PROGRAM_DATA_PROXY.h"

GRAPHIC_SHADER_PROGRAM_DATA_PROXY::GRAPHIC_SHADER_PROGRAM_DATA_PROXY() :
    Program( NULL ),
    ShaderAttributeTable() {
    
}

GRAPHIC_SHADER_PROGRAM_DATA_PROXY::GRAPHIC_SHADER_PROGRAM_DATA_PROXY( const GRAPHIC_SHADER_PROGRAM_DATA_PROXY & other) :
    Program( other.Program ),
    ShaderAttributeTable() {
    
    CopyAttributes();
}

GRAPHIC_SHADER_PROGRAM_DATA_PROXY::~GRAPHIC_SHADER_PROGRAM_DATA_PROXY() {
    
}

GRAPHIC_SHADER_PROGRAM_DATA_PROXY::GRAPHIC_SHADER_PROGRAM_DATA_PROXY( const GRAPHIC_SHADER_PROGRAM::PTR program ) :
    Program( program ),
    ShaderAttributeTable() {

}

void GRAPHIC_SHADER_PROGRAM_DATA_PROXY::Initialize( GRAPHIC_SHADER_PROGRAM::PTR program ) {

    Program = program;
}

void GRAPHIC_SHADER_PROGRAM_DATA_PROXY::Enable() {
    
    Program->Enable();
}

void GRAPHIC_SHADER_PROGRAM_DATA_PROXY::Disable() {
    
    Program->Disable();
}

void GRAPHIC_SHADER_PROGRAM_DATA_PROXY::CopyAttributes() {
    
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_SHADER_ATTRIBUTE>::iterator  it = Program->GetShaderAttributeTable().begin();
    
    while( it != Program->GetShaderAttributeTable().end() ) {
        
        setShaderAttribute( it->second );
        it++;
    }
}
