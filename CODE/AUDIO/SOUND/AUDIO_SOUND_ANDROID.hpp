//
//  AUDIO_SOUND_ANDROID.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef AUDIO_SOUND_ANDROID_h
#define AUDIO_SOUND_ANDROID_h


void Finalize() {
    
}

public:
    inline mpg123_handle * GetMpgHandle() { return MpgHandle; }
    inline void SetMpgHandle( mpg123_handle * handle ) { MpgHandle = handle; }
    inline void SetFile(CORE_FILESYSTEM_FILE * file) { File = file; }
    inline CORE_FILESYSTEM_FILE * GetFile() { return File; }
    inline void SetBufferSize( size_t size ) { BufferSize = size; }
    inline size_t GetBufferSize() { return BufferSize; }

private :
    mpg123_handle
        * MpgHandle;
    CORE_FILESYSTEM_FILE
        * File;
    size_t
        BufferSize;

#endif /* AUDIO_SOUND_ANDROID_h */
