//
//  AUDIO_MP3_LOADER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 25/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "AUDIO_LOADER.h"
#include "AUDIO_SOUND.h"

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "RESOURCE_SOUND.h"

#if PLATFORM_OSX
    #include "AUDIO_LOADER_OSX.h"
#elif PLATFORM_IOS
    #include "AUDIO_LOADER_IOS.h"
#elif PLATFORM_WINDOWS
	#include "AUDIO_LOADER_WINDOWS.h"
#elif PLATFORM_ANDROID
    #include "AUDIO_LOADER_ANDROID.h"
    #include "AUDIO_SOUND_LOADER_MPG123.h"
#else
    #error 1
#endif

#if __AUDIO_OPENAL__
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
#endif

void AUDIO_LOADER_Open( const CORE_FILESYSTEM_PATH & file_path, const char * extension, AUDIO_SOUND & sound, const AUDIO_BANK_SOUND_LOAD_OPTION & option ) {
    
    #if PLATFORM_ANDROID && defined AUDIO_MPG
        MPG_123_Open( file_path, sound );
    #elif PLATFORM_IOS && __AUDIO_OPENAL__
    
    #elif PLATFORM_OSX && __AUDIO_OPENAL__
        UInt32 size,
            samplerate;
        int
            format,
            frame_size;
    
    ExtAudioFileRef *file_ref = new ExtAudioFileRef;
    AudioFileID *file_id = new AudioFileID;
    
        [XSAudioLoader loadFile:[NSString stringWithCString:file_path.GetPath() encoding:NSASCIIStringEncoding]
                  withExtention:[NSString stringWithCString:extension encoding:NSASCIIStringEncoding]
                     yieldsSize:&size
                   yieldsFormat:&format
               yieldsSampleRate:&samplerate
                yieldsFrameSize:&frame_size
              yieldExtAudioFile:(ExtAudioFileRef * )file_ref
                 yieldAudioFile:(AudioFileID * ) file_id];
    
        sound.SetFrequency( samplerate );
        sound.SetIsCompressed( true );
        sound.SetIsMono( format == AL_FORMAT_MONO16 || format == AL_FORMAT_MONO8 );
        sound.SetBufferWidth(( format == AL_FORMAT_MONO16 || format == AL_FORMAT_STEREO16 ) ? 16 : 8 );
        sound.SetSize( size );
        sound.SetFrameSize( frame_size );
        sound.SetChannels( sound.IsMono() ? 1 : 2 );
    
        sound.SetExtAudioFile( file_ref );
        sound.SetAudioFile( file_id );
    #endif
}

bool AUDIO_LOADER_ReadChunk( AUDIO_SOUND & sound, int chunk_index ) {
    
    bool file_is_at_end = false;
    
    #if PLATFORM_OSX && __AUDIO_OPENAL__
    
        int frames = 100000;
        int size = 0;
        
        if ( sound.GetSoundChunksTable().size() == 1 ) {
            
            frames = 0;
            size = sound.GetSize();
        }
        file_is_at_end = [XSAudioLoader readSample:sound.GetSoundChunksTable()[ chunk_index ]
                         withSize:size
                       withFrames:frames
                    withFrameSize:sound.GetFrameSize()
                     withChannels:sound.GetChannels()
                         fromFile:(ExtAudioFileRef * ) sound.GetExtAudioFile()];
    #elif PLATFORM_IOS && __AUDIO_OPENAL__
    
    #else
        MPG_123_Read( sound , chunk_index);
    #endif
    
    return file_is_at_end;
}

void AUDIO_LOADER_Close( AUDIO_SOUND & sound ) {
    
    #if PLATFORM_OSX
        [XSAudioLoader closeAudioFile:(ExtAudioFileRef * ) sound.GetExtAudioFile()
                        withAudioFile:(AudioFileID * ) sound.GetAudioFile() ];
    #elif PLATFORM_IOS && __AUDIO_OPENAL__
    #elif PLATFORM_ANDROID && defined AUDIO_MPG
        MPG_123_Close( sound );
    #endif
}
