//
//  CORE_FILESYSTEM_FILE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_FILESYSTEM_FILE__
#define __GAME_ENGINE_REBORN__CORE_FILESYSTEM_FILE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

#if PLATFORM_ANDROID
    #include <android/asset_manager.h>
    #include <jni.h>
#endif

XS_CLASS_BEGIN_WITH_COPY( CORE_FILESYSTEM_FILE )

CORE_FILESYSTEM_FILE();
CORE_FILESYSTEM_FILE( const CORE_FILESYSTEM_PATH path );

~CORE_FILESYSTEM_FILE();

bool OpenInput();
bool OpenOutput();

int InputBytes( const void * bytes, int size );
int OutputBytes( void * bytes, int size );
void Rewind();
FILE * GetFilePointer();
CORE_FILESYSTEM_PATH GetPath() { return Path; }
int GetSize();

void Close();

bool IsOpen() { return ItIsOpen; }
bool IsOpenInput() { return ItIsOpenInput; }
bool IsOpenOutput() { return ItIsOpenOutput; }

static CORE_FILESYSTEM_FILE NotFound;

private :

CORE_FILESYSTEM_PATH Path;
FILE * FilePointer;
bool ItIsOpen;
bool ItIsOpenInput;
bool ItIsOpenOutput;

#if PLATFORM_ANDROID
    #include "CORE_FILESYSTEM_FILE_ANDROID.hpp"
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_FILESYSTEM_FILE__) */
