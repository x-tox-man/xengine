//
//  AUDIO_BANK_SOUND.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 10/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "AUDIO_BANK_SOUND.h"

AUDIO_BANK_SOUND::AUDIO_BANK_SOUND( const AUDIO_BANK_SOUND_LOAD_OPTION & option ) {
    
    Option = &option;
    
    Sound = new AUDIO_SOUND();
}

AUDIO_BANK_SOUND::AUDIO_BANK_SOUND( const AUDIO_BANK_SOUND & other ) {
    
}

AUDIO_BANK_SOUND::~AUDIO_BANK_SOUND() {

    if ( Sound ) {
        
        delete Sound;
        Sound = NULL;
    }
}
