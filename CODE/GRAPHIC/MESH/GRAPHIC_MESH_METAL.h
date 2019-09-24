//
//  GRAPHIC_MESH_METAL.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/07/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

public :

inline void * GetMTKVertexBuffer() const { return VertexBuffer; }
inline void * GetMTKIndexBuffer() const { return IndexBuffer; }
inline void * GetMTKMtlVertexDescriptor() const { return MtlVertexDescriptor; }
inline void SetMTKVertexBuffer( void * buffer ) { VertexBuffer = buffer; }
inline void SetMTKIndexBuffer( void * buffer ) { IndexBuffer = buffer; }
inline void SetMTKMtlVertexDescriptor( void * descriptor ) { MtlVertexDescriptor = descriptor; }

private :

void
    * VertexBuffer,
    * IndexBuffer,
    * MtlVertexDescriptor;

