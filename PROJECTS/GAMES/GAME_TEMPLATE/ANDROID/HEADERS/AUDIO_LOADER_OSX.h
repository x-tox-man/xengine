//
//  AUDIO_LOADER_OSX.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_RUNTIME_ENVIRONMENT.h"

#if PLATFORM_OSX

    #import <AVFoundation/AVFoundation.h>
    #import <CoreAudio/CoreAudio.h>

    @interface XSAudioLoader : NSObject

    -(instancetype)init;
    -(void *)loadFile:(NSString *)file_name
        withExtention:(NSString *) extention
           yieldsSize:(UInt32 *) outDataSize
         yieldsFormat:(int *) outDataFormat
     yieldsSampleRate:(UInt32 *) outSampleRate;

    @end

#endif
