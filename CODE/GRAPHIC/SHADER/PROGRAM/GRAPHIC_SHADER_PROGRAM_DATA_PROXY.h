//
//  GRAPHIC_SHADER_PROGRAM_DATA_PROXY.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SHADER_PROGRAM_DATA_PROXY_h
#define GRAPHIC_SHADER_PROGRAM_DATA_PROXY_h

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_PROGRAM.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_SHADER_PROGRAM_DATA_PROXY )

    GRAPHIC_SHADER_PROGRAM_DATA_PROXY();
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY( const GRAPHIC_SHADER_PROGRAM & program );
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY( const GRAPHIC_SHADER_PROGRAM::PTR program );
    ~GRAPHIC_SHADER_PROGRAM_DATA_PROXY();

    void Initialize( GRAPHIC_SHADER_PROGRAM::PTR program );

    void Enable();
    void Disable();

    GRAPHIC_SHADER_ATTRIBUTE & getShaderAttribute( const CORE_HELPERS_IDENTIFIER & identifier ) { return ShaderAttributeTable[identifier]; }
    GRAPHIC_SHADER_PROGRAM::PTR GetProgram() { return Program; }
    void SetProgram( GRAPHIC_SHADER_PROGRAM::PTR program ) { Program = program; }
    void CopyAttributes();

    void setShaderAttribute( const GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
        
        ShaderAttributeTable[attribute.AttributeName].AttributeIndex = attribute.AttributeIndex;
        ShaderAttributeTable[attribute.AttributeName].AttributeName = attribute.AttributeName;
        ShaderAttributeTable[attribute.AttributeName].AttributeValue = attribute.AttributeValue;
    }

protected:

    GRAPHIC_SHADER_PROGRAM::PTR
        Program;
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_SHADER_ATTRIBUTE>
        ShaderAttributeTable;

XS_CLASS_END

#endif /* GRAPHIC_SHADER_PROGRAM_DATA_PROXY_hpp */
