//
//  AUDIO_SOUND_OSX.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef AUDIO_SOUND_OSX_h
#define AUDIO_SOUND_OSX_h

private :

void * ExtAudioFile;
void * AudioFile;

void Finalize() {
    
    if ( ExtAudioFile ) {
        
        //free( AudioFile );
        //free( ExtAudioFile );
    }
}

public :

void * GetExtAudioFile() { return ExtAudioFile; }
void * GetAudioFile() { return AudioFile; }
void SetExtAudioFile( void * ext_audio_file ) { ExtAudioFile = ext_audio_file; }
void SetAudioFile(void * audio_file) { AudioFile = audio_file; }

private :

#endif /* AUDIO_SOUND_OSX_h */
