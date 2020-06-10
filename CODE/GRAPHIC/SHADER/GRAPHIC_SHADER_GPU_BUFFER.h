//
//  GRAPHIC_SHADER_GPU_BUFFER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 23/05/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SHADER_GPU_BUFFER_hpp
#define GRAPHIC_SHADER_GPU_BUFFER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_BUFFER.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_SHADER_GPU_BUFFER )

    GRAPHIC_SHADER_GPU_BUFFER();
    void Initialize( unsigned int size );


    GRAPHIC_SHADER_GPU_BUFFER & operator = (const GRAPHIC_SHADER_GPU_BUFFER & other) {
        
        Buffer = other.Buffer;
        return *this;
    }

    void * GetGPUBufferDataPointer();
    inline void * GetGPUBufferPointer() { return Buffer; }

private :

    void
        * Buffer;

XS_CLASS_END

#endif /* GRAPHIC_SHADER_GPU_BUFFER_hpp */
