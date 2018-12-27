//
//  RESOURCE_SOUND_MP3_LOADER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 16/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "RESOURCE_SOUND_MP3_LOADER.h"
#include "RESOURCE_SOUND.h"
#include "CORE_FILESYSTEM_FILE.h"

#if PLATFORM_ANDROID
    #include <mpg123.h>
    //#include <out123.h>
#endif
RESOURCE_SOUND_MP3_LOADER::RESOURCE_SOUND_MP3_LOADER() :
    RESOURCE_LOADER< RESOURCE_SOUND >() {
    
}

RESOURCE_SOUND_MP3_LOADER::~RESOURCE_SOUND_MP3_LOADER() {
    
}

RESOURCE_SOUND * RESOURCE_SOUND_MP3_LOADER::Load( const CORE_FILESYSTEM_PATH & path, int resource_load_flag, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    auto ptr = new RESOURCE_SOUND;
    
    SERVICE_LOGGER_Info( "AUDIO_BUFFER_READ START" );
    
    #if PLATFORM_ANDROID
    
    mpg123_init();
    
    int err;
    
    mpg123_handle *mh = mpg123_new(NULL, &err);
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    
    int channels, encoding;
    long rate;
    buffer_size = mpg123_outblock( mh );
    buffer = (unsigned char*) CORE_MEMORY_ALLOCATOR_Allocate( buffer_size * sizeof( unsigned char ) );
    
    SERVICE_LOGGER_Info( "AUDIO_BUFFER_READ %s", path.GetPath() );
    
    CORE_FILESYSTEM_FILE
        file(path);
    
    if ( !file.OpenOutput() ) {
        
        return NULL;
    }
    
    int res = mpg123_open_fd(mh, fileno(file.GetFilePointer()) );
    
    SERVICE_LOGGER_Info( "AUDIO_BUFFER_READ size :  %d err : %d, %d", buffer_size,err, res );
    mpg123_getformat(mh, &rate, &channels, &encoding);
    
    //std::ofstream out("res.txt");
    
    unsigned int counter = 0;
    int totalBtyes = 0;
    
    do {
        res = mpg123_read(mh, buffer, buffer_size, &done);
        
        /*short * tst = reinterpret_cast<short*>(buffer);
        
        SERVICE_LOGGER_Info( "AUDIO_BUFFER_READ read result :  %d done : %d", res, done );
        
        for (auto i = 0; i < buffer_size / 2; i++) {
            
            SERVICE_LOGGER_Info( "AUDIO_BUFFER_READ size :  %d", buffer_size );
        }*/
        
        counter += buffer_size / 2;
        totalBtyes += done;
    }
    while ( res == MPG123_OK);
    
    free(buffer);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    file.Close();
    #endif
    
    SERVICE_LOGGER_Info( "AUDIO_BUFFER_READ END" );
    
    return ptr;
}

RESOURCE_SOUND * RESOURCE_SOUND_MP3_LOADER::Load( CORE_DATA_STREAM & stream, int resource_load_flag, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    auto ptr = new RESOURCE_SOUND;
    return ptr;
}

void RESOURCE_SOUND_MP3_LOADER::ReloadResource( RESOURCE_SOUND * resource_to_reload ) {
    
}
