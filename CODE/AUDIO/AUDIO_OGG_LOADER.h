#pragma once

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "RESOURCE_SOUND.h"
#include "CORE_FILESYSTEM_FILE.h"

class AUDIO_SOUND;

#ifdef AUDIO_OGG
    void OGG_Init();
    void OGG_Open( const CORE_FILESYSTEM_PATH & path, AUDIO_SOUND & sound );
    void OGG_Read( AUDIO_SOUND & sound, int chunk_index );
    void OGG_Close( AUDIO_SOUND & sound );
#endif