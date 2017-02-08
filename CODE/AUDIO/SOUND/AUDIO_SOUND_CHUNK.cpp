//
//  AUDIO_SOUND_CHUNK.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "AUDIO_SOUND_CHUNK.h"

AUDIO_SOUND_CHUNK::AUDIO_SOUND_CHUNK() :
    Data( NULL ),
    Size( 0 ),
    Index( 0 ) {
    
}

AUDIO_SOUND_CHUNK::~AUDIO_SOUND_CHUNK() {
    
    if ( Data ) {
        
        free( Data );
        Data = NULL;
    }
}
