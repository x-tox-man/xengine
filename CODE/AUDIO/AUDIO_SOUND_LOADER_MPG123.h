//
//  AUDIO_SOUND_LOADER_MPG123.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 18/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef AUDIO_SOUND_LOADER_MPG123_hpp
#define AUDIO_SOUND_LOADER_MPG123_hpp

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "RESOURCE_SOUND.h"
#include "CORE_FILESYSTEM_FILE.h"

class AUDIO_SOUND;

#ifdef AUDIO_MPG
    void MPG_123_Init();
    void MPG_123_Open( const CORE_FILESYSTEM_PATH & path, AUDIO_SOUND & sound );
    void MPG_123_Read( AUDIO_SOUND & sound, int chunk_index );
    void MPG_123_Close( AUDIO_SOUND & sound );
#endif

#endif /* AUDIO_SOUND_LOADER_MPG123_hpp */
