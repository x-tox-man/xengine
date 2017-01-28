//
//  AUDIO_BANK_SOUND_OPTION.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 10/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef AUDIO_BANK_SOUND_LOAD_OPTION_hpp
#define AUDIO_BANK_SOUND_LOAD_OPTION_hpp

struct AUDIO_BANK_SOUND_LOAD_OPTION {
    
    AUDIO_BANK_SOUND_LOAD_OPTION( bool it_loads, bool it_streams, int buffer_lenght = 0 ) {
        
        ItLoadAtStartup = it_loads;
        ItStreams = it_streams;
        MaxBufferLenght = buffer_lenght;
    }
    
    bool ItLoadAtStartup;
    bool ItStreams;
    int MaxBufferLenght;
};

extern AUDIO_BANK_SOUND_LOAD_OPTION AUDIO_BANK_SOUND_LOAD_OPTION_SoundStartupLoad;
extern AUDIO_BANK_SOUND_LOAD_OPTION AUDIO_BANK_SOUND_LOAD_OPTION_SoundDelayedLoad;
extern AUDIO_BANK_SOUND_LOAD_OPTION AUDIO_BANK_SOUND_LOAD_OPTION_StartupStreamMusic;
extern AUDIO_BANK_SOUND_LOAD_OPTION AUDIO_BANK_SOUND_LOAD_OPTION_DelayedStreamMusic;

#endif /* AUDIO_BANK_SOUND_OPTION_hpp */
