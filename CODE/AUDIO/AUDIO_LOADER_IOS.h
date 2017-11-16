//
//  AUDIO_LOADER_IOS.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//


    #import <AVFoundation/AVFoundation.h>
    #import <OpenAL/al.h>

    @interface XSAudioLoader : NSObject

    -(instancetype)init;
    -(void *)loadFile:(NSString *)file_name
        withExtention:(NSString *) extention
           yieldsSize:(UInt32 *) outDataSize
         yieldsFormat:(int *) outDataFormat
     yieldsSampleRate:(UInt32 *) outSampleRate;

    @end
