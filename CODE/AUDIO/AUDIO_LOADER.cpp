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

#if AUDIO_OGG
    #include "AUDIO_OGG_LOADER.h"
#elif PLATFORM_OSX
    #include "AUDIO_LOADER_OSX.h"
#elif PLATFORM_IOS
    //#include "AUDIO_LOADER_IOS.h"
#elif PLATFORM_WINDOWS
    //#include "lame.h"
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

//lame_global_flags *gfp = lame_init();

void AUDIO_LOADER_Reset( AUDIO_SOUND & sound ) {
    
    #if AUDIO_OGG
        OGG_Reset( sound );
    #elif AUDIO_FILE_IOS
    //TODO
    #else
        #error "Must use AUDIO_OGG"
    #endif
}

void AUDIO_LOADER_Open( const CORE_FILESYSTEM_PATH & file_path, const char * extension, AUDIO_SOUND & sound, const AUDIO_BANK_SOUND_LOAD_OPTION & option ) {
    
    #if AUDIO_OGG
        OGG_Open( file_path, sound );
    #elif PLATFORM_ANDROID && defined AUDIO_MPG
        MPG_123_Open( file_path, sound );
    
    #elif PLATFORM_WINDOWS && __AUDIO_OPENAL__
    
    /*CORE_FILESYSTEM_FILE
        * file = new CORE_FILESYSTEM_FILE( file_path );

        if ( !file->OpenOutput() ) {

            return;
        }

        sound.Hip = hip_decode_init();
        sound.SetFile( file );

        void * bytes=malloc( 4096 );
        sound.GetFile()->OutputBytes( bytes, 4096 );
        file->Rewind();
        

        short
            pcm_l[ 40240 ],
            pcm_r[ 40240 ];

        mp3data_struct mp3data;
        lame_set_decode_only( gfp, 1 );
        lame_set_in_samplerate( gfp, 44100 );
        lame_set_VBR( gfp, vbr_default );
        //lame_set_mode(lame, MONO);
        lame_init_params( gfp );

        int size = hip_decode_headers( sound.Hip, (unsigned char *) bytes, 4096, pcm_l, pcm_r, &mp3data );

        if ( size ) {
            sound.GetFile()->OutputBytes( bytes, size );
        }
        else {
            sound.GetFile()->OutputBytes( bytes, 128 );
            sound.GetFile()->OutputBytes( bytes, size );
            size = hip_decode_headers( sound.Hip, ( unsigned char * ) bytes, 4096, pcm_l, pcm_r, &mp3data );
        }

        sound.SetFrequency( mp3data.samplerate );
        sound.SetIsCompressed( true );
        sound.SetIsMono( mp3data.stereo == 1 );
        sound.SetBufferWidth( mp3data.stereo * mp3data.framesize  );
        sound.SetSize( mp3data.totalframes );
        sound.SetFrameSize( mp3data.framesize );
        sound.SetChannels( sound.IsMono() ? 1 : 2 );

        free( bytes );*/

    #elif PLATFORM_IOS
    
    #elif PLATFORM_OSX
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
    
    if ( sound.GetSoundChunksTable()[chunk_index]->Data != NULL ) {
        
        free( sound.GetSoundChunksTable()[chunk_index]->Data );
        sound.GetSoundChunksTable()[chunk_index]->Data = NULL;
    }
    
    #if AUDIO_OGG
        file_is_at_end = OGG_Read(sound, chunk_index );
    #elif PLATFORM_OSX && __AUDIO_OPENAL__
    
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
        //#error "cannot use PLATFORM_IOS && __AUDIO_OPENAL__ in this configuration"
    #elif PLATFORM_ANDROID
        MPG_123_Read( sound , chunk_index);
    #elif PLATFORM_WINDOWS
        #error "TODO implement"
    #else
        #error "Must define one audio platform"
    #endif
    
    return file_is_at_end;
}

void AUDIO_LOADER_Close( AUDIO_SOUND & sound ) {
    
    #if AUDIO_OGG
        OGG_Close( sound );
    #elif PLATFORM_OSX
        [XSAudioLoader closeAudioFile:(ExtAudioFileRef * ) sound.GetExtAudioFile()
                        withAudioFile:(AudioFileID * ) sound.GetAudioFile() ];
    #elif PLATFORM_IOS && __AUDIO_OPENAL__

    #elif PLATFORM_WINDOWS && __AUDIO_OPENAL__
        
    #elif PLATFORM_ANDROID && defined AUDIO_MPG
        MPG_123_Close( sound );
    #endif
}
