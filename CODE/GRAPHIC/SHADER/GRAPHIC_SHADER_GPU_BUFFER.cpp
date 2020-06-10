//
//  GRAPHIC_SHADER_GPU_BUFFER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 23/05/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_GPU_BUFFER.h"
#include "GRAPHIC_SYSTEM.h"

GRAPHIC_SHADER_GPU_BUFFER::GRAPHIC_SHADER_GPU_BUFFER() :
    Buffer( NULL ) {
    
}

GRAPHIC_SHADER_GPU_BUFFER::GRAPHIC_SHADER_GPU_BUFFER( const GRAPHIC_SHADER_GPU_BUFFER & other ) :
    Buffer( NULL ) {
    
    Buffer = other.Buffer;
}

void GRAPHIC_SHADER_GPU_BUFFER::Initialize( unsigned int size ) {
    
    Buffer = GRAPHIC_SYSTEM::CreateMetalDynamicUniformBuffer( size );
}

void * GRAPHIC_SHADER_GPU_BUFFER::GetGPUBufferDataPointer() {
    
    return GRAPHIC_SYSTEM::GetMtlBufferPointer( Buffer );
}
