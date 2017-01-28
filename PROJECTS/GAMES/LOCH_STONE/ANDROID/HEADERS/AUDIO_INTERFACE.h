//
//  AUDIO_INTERFACE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_INTERFACE__
#define __GAME_ENGINE_REBORN__AUDIO_INTERFACE__

#include "CORE_HELPERS_CLASS.h"
#include "AUDIO_SOUND.h"

template <typename __AUDIO_INTERFACE__>
XS_CLASS_BEGIN( AUDIO_INTERFACE )

AUDIO_INTERFACE() {
    
}

void Initialize() {
    
    ( ( __AUDIO_INTERFACE__ * ) this )->Initialize();
}

void Finalize() {
    
    ( ( __AUDIO_INTERFACE__ * ) this )->Finalize();
}

void PlaySound( AUDIO_SOUND & sound) {

    ( ( __AUDIO_INTERFACE__ * ) this )->PlaySound( sound );
}

void Update( const float time_step ) {
    
    ( ( __AUDIO_INTERFACE__ * ) this )->Update( time_step );
}

void Suspend() {
    
    ( ( __AUDIO_INTERFACE__ * ) this )->Suspend();
}

void Resume() {
    
    ( ( __AUDIO_INTERFACE__ * ) this )->Resume();
}

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_INTERFACE__) */
