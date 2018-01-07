//
//  CORE_FILESYSTEM_FILE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_FILESYSTEM_FILE.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

CORE_FILESYSTEM_FILE::CORE_FILESYSTEM_FILE() :
    Path(),
    FilePointer( NULL ),
    ItIsOpen( false ),
    ItIsOpenInput( false ),
    ItIsOpenOutput( false ) {
        
#if PLATFORM_ANDROID
    AssetFile = NULL;
#endif
}

CORE_FILESYSTEM_FILE::CORE_FILESYSTEM_FILE( const CORE_FILESYSTEM_PATH path ) :
    FilePointer( NULL ),
    ItIsOpen( false ),
    ItIsOpenInput( false ),
    ItIsOpenOutput( false ) {
    
    Path = path;
        
#if PLATFORM_ANDROID
    AssetFile = NULL;
#endif
}

CORE_FILESYSTEM_FILE::CORE_FILESYSTEM_FILE( const CORE_FILESYSTEM_FILE & other ) :
    FilePointer( NULL ),
    ItIsOpen( false ),
    ItIsOpenInput( false ),
    ItIsOpenOutput( false ),
    Path( other.Path ) {
    
#if PLATFORM_ANDROID
    AssetFile = NULL;
#endif
}

#if !PLATFORM_ANDROID

CORE_FILESYSTEM_FILE::~CORE_FILESYSTEM_FILE() {
    
#if DEBUG
    if ( FilePointer != NULL && ItIsOpen ) {
        
        Close();
    }
#endif
}

bool CORE_FILESYSTEM_FILE::OpenInput() {
    
    FilePointer = fopen( Path.GetPath(), "wb");
    
    if ( !FilePointer ) {
        
        return false;
    }
    
    ItIsOpen = true;
    ItIsOpenInput = true;
    
    return true;
}

bool CORE_FILESYSTEM_FILE::OpenOutput() {

    
    FilePointer = fopen( Path.GetPath(), "rb" );
    
    if ( !FilePointer ) {
        
        return false;
    }
    
    ItIsOpen = true;
    ItIsOpenOutput = true;
    
    return true;
}

int CORE_FILESYSTEM_FILE::InputBytes( const void * bytes, int size ) {
    
    #if DEBUG
        assert( ItIsOpenInput );
    #endif
    
    int bytes_written = (int) fwrite(bytes, 1, size, FilePointer );
    
    if ( bytes_written != size ) {
        
        return -1;
    }
    else {
        return bytes_written;
    }
}

int CORE_FILESYSTEM_FILE::OutputBytes( void * bytes, int size ) {
    
    #if DEBUG
        assert( ItIsOpenOutput );
    #endif
    
    int bytes_read = (int) fread( bytes, 1, size, FilePointer );
    
    if ( bytes_read != size ) {
        
        return -1;
    }
    else {
        return bytes_read;
    }
}

void CORE_FILESYSTEM_FILE::Rewind() {
    
    fseek( FilePointer, 0, SEEK_SET );
}

void CORE_FILESYSTEM_FILE::Seek( long position ) {
    
    fseek( FilePointer, position, SEEK_SET );
}

int CORE_FILESYSTEM_FILE::GetSize() {
    
    int
        file_size;
    
    fseek( FilePointer, 0L, SEEK_END );
    file_size = (int) ftell( FilePointer );
    fseek( FilePointer, 0L, SEEK_SET );
    
    return file_size;
}

FILE * CORE_FILESYSTEM_FILE::GetFilePointer() {
    
    return FilePointer;
}

void CORE_FILESYSTEM_FILE::Close() {
    
    fclose( FilePointer );
    
    ItIsOpen = false;
    ItIsOpenOutput = false;
    ItIsOpenInput = false;
}

#endif

CORE_FILESYSTEM_FILE CORE_FILESYSTEM_FILE::NotFound;
