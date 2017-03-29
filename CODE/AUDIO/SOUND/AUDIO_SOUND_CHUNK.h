//
//  AUDIO_SOUND_CHUNK.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef AUDIO_SOUND_CHUNK_hpp
#define AUDIO_SOUND_CHUNK_hpp

#include "CORE_HELPERS_CLASS.h"

#if __AUDIO_OPENAL__
    #include <OpenAL/al.h>
#endif

XS_CLASS_BEGIN( AUDIO_SOUND_CHUNK )

    AUDIO_SOUND_CHUNK();
    ~AUDIO_SOUND_CHUNK();

    void
        * Data;
    int
        Size,
        Index;

    #if __AUDIO_OPENAL__
        ALuint & GetChunkBufferName() { return ChunkBufferName; }
        void SetChunkBufferName( ALuint name ) { ChunkBufferName = name; }
        ALuint ChunkBufferName;
    #endif

XS_CLASS_END

#endif /* AUDIO_SOUND_CHUNK_hpp */
