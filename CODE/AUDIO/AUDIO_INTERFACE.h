//
//  AUDIO_INTERFACE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__AUDIO_INTERFACE__
#define __GAME_ENGINE_REBORN__AUDIO_INTERFACE__

#include "CORE_HELPERS_CLASS.h"
#include "AUDIO_RUNTIME_ENVIRONMENT.h"
#include "AUDIO_SOUND.h"
#include "CORE_MATH_VECTOR.h"

template <typename __AUDIO_INTERFACE__>
class AUDIO_INTERFACE {
    
public :

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

    void StopSound( AUDIO_SOUND & sound) {
        
        ( ( __AUDIO_INTERFACE__ * ) this )->StopSound( sound );
    }

    void PauseSound( AUDIO_SOUND & sound) {
        
        ( ( __AUDIO_INTERFACE__ * ) this )->PauseSound( sound );
    }

    void ResumeSound( AUDIO_SOUND & sound) {
        
        ( ( __AUDIO_INTERFACE__ * ) this )->ResumeSound( sound );
    }

    void Update( const float time_step, const CORE_MATH_VECTOR & position ) {
        
        ( ( __AUDIO_INTERFACE__ * ) this )->Update( time_step, position );
    }

    void Suspend() {
        
        ( ( __AUDIO_INTERFACE__ * ) this )->Suspend();
    }

    void Resume() {
        
        ( ( __AUDIO_INTERFACE__ * ) this )->Resume();
    }
    
    void OnSoundIsRead() {
        
        ( ( __AUDIO_INTERFACE__ * ) this )->OnSoundIsRead();
    }

};

#endif /* defined(__GAME_ENGINE_REBORN__AUDIO_INTERFACE__) */
