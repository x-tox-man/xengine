//
//  AUDIO_LOADER_OSX.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_RUNTIME_ENVIRONMENT.h"

#if PLATFORM_OSX

    #import <AVFoundation/AVFoundation.h>
    #import <CoreAudio/CoreAudio.h>
    #include "AUDIO_SOUND.h"

    @interface XSAudioLoader : NSObject

    -(instancetype)init;
    +(void)loadFile:(NSString *)file_name
        withExtention:(NSString *) extention
           yieldsSize:(UInt32 *) outDataSize
         yieldsFormat:(int *) outDataFormat
     yieldsSampleRate:(UInt32 *) outSampleRate
      yieldsFrameSize:(int *) frameSize
    yieldExtAudioFile:(ExtAudioFileRef *) ext_audio_file
        yieldAudioFile:(AudioFileID *) audio_file;

    +(bool)readSample:(AUDIO_SOUND_CHUNK *) chunk
             withSize:(int) size
           withFrames:(int) frames
        withFrameSize:(int) frameSize
         withChannels:(int) channelsPerFrame
             fromFile:(ExtAudioFileRef *) file;

    +(void)closeAudioFile:(ExtAudioFileRef*) file
            withAudioFile:(AudioFileID*) audio_file;
    @end

#endif
