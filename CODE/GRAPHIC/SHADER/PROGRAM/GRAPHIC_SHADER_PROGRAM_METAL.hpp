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
inline void * GetMtlPipelineDescriptor() { return _pipelineStateDescriptor; }
void * GetMtlCachedPipelineState( const GRAPHIC_RENDERER & renderer );

private:

void
    *_pipelineStateDescriptor;
std::map< GRAPHIC_RENDERER_STATE_DESCRIPTOR, void * >
    MetalPipelineStateCache;

#endif /* GRAPHIC_SHADER_PROGRAM_METAL_hpp */
