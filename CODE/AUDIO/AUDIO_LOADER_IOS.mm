//
//  AUDIO_LOADER_IOS.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#import "AUDIO_LOADER_IOS.h"

@implementation XSAudioLoader

- (instancetype)init
{
    self = [super init];
    
    if (self) {
        
    }
    
    return self;
}

-(void *)loadFile:(NSString *)file_name
    withExtention:(NSString *) extention
       yieldsSize:(UInt32 *) outDataSize
     yieldsFormat:(int *) outDataFormat
 yieldsSampleRate:(UInt32 *) outSampleRate {

    return NULL;
}

@end
