//
//  CORE_FILESYSTEM_FILE_ANDROID.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_FILESYSTEM_FILE.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_FILESYSTEM.h"
#include "SERVICE_LOGGER.h"

#if PLATFORM_ANDROID

#include <android/asset_manager.h>
#include <jni.h>

static int android_read(void* cookie, char* buf, int size) {
    return AAsset_read((AAsset*)cookie, buf, size);
}

static int android_write(void* cookie, const char* buf, int size) {
    return -1; // can't provide write access to the apk
}

static fpos_t android_seek(void* cookie, fpos_t offset, int whence) {
    return AAsset_seek((AAsset*)cookie, offset, whence);
}

static int android_close(void* cookie) {
    AAsset_close((AAsset*)cookie);
    return 0;
}

CORE_FILESYSTEM_FILE::~CORE_FILESYSTEM_FILE() {
    
}

bool CORE_FILESYSTEM_FILE::OpenInput() {
 
    
    SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH OpenInput forbidden %s", Path.GetPath() );
    CORE_RUNTIME_Abort();
    
    AssetFile = AAssetManager_open( CORE_FILESYSTEM::GetDefaultFilesystem().GetAndroidAssetManager(), Path.GetPath(), AASSET_MODE_UNKNOWN );
    
    if( !AssetFile) {
        
        return false;
    }
    
    FilePointer = funopen( AssetFile, android_read, android_write, android_seek, android_close );
}

int CORE_FILESYSTEM_FILE::OpenFileDescriptor() {
    
    off_t start, length;
    return AAsset_openFileDescriptor(AssetFile, &start, &length);

}

bool CORE_FILESYSTEM_FILE::OpenOutput() {
    
    //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH OpenOutput %s", Path.GetPath() );
    
    AssetFile = AAssetManager_open( CORE_FILESYSTEM::GetDefaultFilesystem().GetAndroidAssetManager(), Path.GetPath(), AASSET_MODE_UNKNOWN );
    FilePointer = funopen( AssetFile, android_read, android_write, android_seek, android_close );
    
    ItIsOpen = true;
    ItIsOpenOutput = true;
    
    return AssetFile != NULL;
}

int CORE_FILESYSTEM_FILE::InputBytes( const void * bytes, int size ) {
    
    //TODO : not permitted on asset dir
    CORE_RUNTIME_Abort();
    
    return -1;
}

int CORE_FILESYSTEM_FILE::OutputBytes( void * bytes, int size ) {
    

    return AAsset_read( AssetFile, bytes, size );
}

void CORE_FILESYSTEM_FILE::Close() {
    
    AAsset_close( AssetFile );
    
    ItIsOpen = false;
    ItIsOpenOutput = false;
    
    FilePointer = NULL;
    AssetFile = NULL;
}

void CORE_FILESYSTEM_FILE::Rewind() {
    
    AAsset_seek( AssetFile, 0, SEEK_SET );
}

int CORE_FILESYSTEM_FILE::GetSize() {
    
    return AAsset_getLength( AssetFile );
}

FILE * CORE_FILESYSTEM_FILE::GetFilePointer() {
    
    return FilePointer;
}

#endif
