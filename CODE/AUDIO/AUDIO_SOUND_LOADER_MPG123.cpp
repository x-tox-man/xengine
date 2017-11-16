//
//  AUDIO_SOUND_LOADER_MPG123.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 18/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "AUDIO_SOUND_LOADER_MPG123.h"
#include "AUDIO_SOUND.h"
#include "AUDIO_SOUND_CHUNK.h"

#ifdef AUDIO_MPG
    #include <mpg123.h>

    void MPG_123_Init() {
        
        mpg123_init();
    }

    void MPG_123_Open( const CORE_FILESYSTEM_PATH & path, AUDIO_SOUND & sound) {
        
        int
            error;
        mpg123_handle
            * mh = mpg123_new( NULL, &error );
        size_t
            buffer_size;
        
        int
            channels,
            encoding;
        long
            rate;
        
        buffer_size = mpg123_outblock( mh );
        
        SERVICE_LOGGER_Info( "MPG_123 Open %s", path.GetPath() );
        
        CORE_FILESYSTEM_FILE
            * file = new CORE_FILESYSTEM_FILE(path);
        
        /*
         int
         FrameSize,
         Channels,
         Frequency;
         */
        
        if ( !file->OpenOutput() ) {
            
            return;
        }
        
        int res = mpg123_open_fd(mh, file->OpenFileDescriptor() );
        SERVICE_LOGGER_Info( "MPG_123 error : %s", mpg123_plain_strerror(res) );
        
        res = mpg123_getformat(mh, &rate, &channels, &encoding);
        SERVICE_LOGGER_Info( "MPG_123 error : %s", mpg123_plain_strerror(res) );
        
        sound.SetMpgHandle( mh );
        
        
        sound.SetFile( file );
        sound.SetChannels( 2 );
        sound.SetFrequency( rate );
        sound.SetIsMono( false );
        sound.SetIsCompressed( false );
        sound.SetBufferWidth( 16 );
        sound.SetBufferSize( buffer_size );
        sound.SetFrameSize( 16 );
    
        SERVICE_LOGGER_Info( "MPG_123 : rate %d, channels : %d, encoding %d, buffersize %d", (int) rate, (int) channels, (int) encoding, (int) buffer_size );
    }

    void MPG_123_Read( AUDIO_SOUND & sound, int chunk_index ) {
        
        int
            result;
        size_t
            done,
            buffer_size = sound.GetBufferSize();
        unsigned
            int counter = 0;
        int
            totalBtyes = 0;
        void
            * buffer = CORE_MEMORY_ALLOCATOR_Allocate( buffer_size * sizeof( unsigned char ) );
        
        AUDIO_SOUND_CHUNK * chunk = sound.GetSoundChunksTable()[ chunk_index ];
        
        result = mpg123_read(sound.GetMpgHandle(), (unsigned char*) buffer, buffer_size, &done);
        
        chunk->Data = buffer;
        chunk->Size = buffer_size;
        SERVICE_LOGGER_Info( "MPG_123 index : %d -  data : %d size : handle : %d,  %d, result : %d, done %d", chunk_index, *(int*) chunk->Data, *(int*)sound.GetMpgHandle(), buffer_size, result, done );
        SERVICE_LOGGER_Info( "MPG_123 error : %s", mpg123_plain_strerror(result) );
        
        /*do {
         
            
            /*short * tst = reinterpret_cast<short*>(buffer);
             
             SERVICE_LOGGER_Info( "AUDIO_BUFFER_READ read result :  %d done : %d", res, done );
             
             for (auto i = 0; i < buffer_size / 2; i++) {
             
             
             }*/
            /*SERVICE_LOGGER_Info( "MPG_123 before decode");
            result = mpg123_decode(sound.GetMpgHandle(),
                             (const unsigned char *) 	in_buffer,
                             buffer_size * sizeof( unsigned char ),
                             (unsigned char *)out_buffer,
                             buffer_size * sizeof( unsigned char )*1000,
                             &done
                            );
            
            chunk->Data = out_buffer;
            chunk->Size = buffer_size;
            
            SERVICE_LOGGER_Info( "MPG_123 size :  handle : %d,  %d, result : %d, done %d", *(int*)sound.GetMpgHandle(), buffer_size, result, done );
            SERVICE_LOGGER_Info( "MPG_123 error : %s", mpg123_plain_strerror(result) );
            
            counter += buffer_size / 2;
            totalBtyes += done;
        }
        while ( result == MPG123_OK);*/
    }

    void MPG_123_Close( AUDIO_SOUND & sound ) {
        
        SERVICE_LOGGER_Info( "MPG_123 close");
        mpg123_close(sound.GetMpgHandle());
        mpg123_delete(sound.GetMpgHandle());
        mpg123_exit();
        sound.GetFile()->Close();
    }

#endif
