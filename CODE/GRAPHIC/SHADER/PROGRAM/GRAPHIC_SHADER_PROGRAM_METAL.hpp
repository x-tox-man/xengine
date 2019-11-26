//
//  GRAPHIC_SHADER_PROGRAM_METAL.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/08/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SHADER_PROGRAM_METAL_hpp
#define GRAPHIC_SHADER_PROGRAM_METAL_hpp

void LinkTogether( const GRAPHIC_SHADER_BIND shader_bind );
void BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, const CORE_HELPERS_IDENTIFIER & identifier );

private:

void
    * _pipelineState;
void
    *_pipelineStateDescriptor;
void
    * _dynamicUniformBuffer;
uint32_t
    _uniformBufferOffset;
uint8_t
    _uniformBufferIndex;

#endif /* GRAPHIC_SHADER_PROGRAM_METAL_hpp */
