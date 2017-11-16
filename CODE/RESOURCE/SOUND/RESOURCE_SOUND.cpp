//
//  RESOURCE_SOUND.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 16/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "RESOURCE_SOUND.h"
#include "AUDIO_SOUND.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( RESOURCE_SOUND )

XS_END_INTERNAL_MEMORY_LAYOUT

RESOURCE_SOUND::RESOURCE_SOUND() :
    RESOURCE< RESOURCE_SOUND, RESOURCE_SOUND_MP3_LOADER >(),
    Path(),
    RawData() {
    
}

RESOURCE_SOUND::~RESOURCE_SOUND() {
    
}
