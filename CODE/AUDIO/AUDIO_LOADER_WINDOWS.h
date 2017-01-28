//
//  AUDIO_LOADER_WINDOWS.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 25/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef AUDIO_LOADER_WINDOWS_H
#define AUDIO_LOADER_WINDOWS_H

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include <stdio.h>
#include <assert.h>
#include <mmiscapi.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include <wmsdk.h>

#pragma comment(lib, "msacm32.lib") 
#pragma comment(lib, "wmvcore.lib") 
#pragma comment(lib, "winmm.lib") 
#pragma intrinsic(memset,memcpy,memcmp)

#ifdef _DEBUG
#define mp3Assert(function) assert((function) == 0)
#else 
    #define mp3Assert(function) function
#endif

XS_CLASS_BEGIN(AUDIO_LOADER_WINDOWS )

	AUDIO_LOADER_WINDOWS();

    HRESULT OpenFromFile( TCHAR* inputFileName );
    HRESULT OpenFromMemory( BYTE* mp3InputBuffer, DWORD mp3InputBufferSize );
    double GetPosition();
    double GetDuration();
    void Close();
    void Play();

    private:

        HWAVEOUT hWaveOut;
        DWORD bufferLength;
        double durationInSecond;
        BYTE* soundBuffer;

XS_CLASS_END

#endif