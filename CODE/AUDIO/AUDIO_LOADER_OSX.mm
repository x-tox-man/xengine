//
//  AUDIO_LOADER_OSX.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#import "AUDIO_LOADER_OSX.h"
#include <OpenAL/al.h>

@implementation XSAudioLoader

- (instancetype)init
{
    self = [super init];
    
    if (self) {
        
    }
    
    return self;
}

+(void) loadFile:(NSString *)file_name
   withExtention:(NSString *) extention
      yieldsSize:(UInt32 *) outDataSize
    yieldsFormat:(int *) outDataFormat
yieldsSampleRate:(UInt32 *) outSampleRate
yieldsFrameSize:(int *) frameSize
yieldExtAudioFile:(ExtAudioFileRef * ) ext_audio_file
yieldAudioFile:(AudioFileID * ) audio_file {

    OSStatus err;
    
    AudioStreamBasicDescription         *outFormat;
    AudioStreamBasicDescription         inFormat;
    AudioChannelLayout                  *outChannelLayout;
    AudioChannelLayout                  channelLayout;
    AudioFileID							outAudioFile;
    ExtAudioFileRef                     outExtAudioFile;
    UInt32                              thePropertySize;
    SInt64                              theFileLengthInFrames = 0;
    
    outFormat = &inFormat;
    outChannelLayout = &channelLayout;
    
    AudioFileTypeID file_type;
    
    outExtAudioFile = NULL;
    
    if ( [extention isEqualToString:@"mp3"] ) {
        
        file_type = kAudioFileMP3Type;
    }
    else if ( [extention isEqualToString:@"wav"] ) {

        file_type = kAudioFileWAVEType;
    }
    else {

        abort();
    }
    
    
    err = ExtAudioFileOpenURL( (__bridge CFURLRef)([NSURL URLWithString:file_name]), &outExtAudioFile);
    
#if DEBUG
    assert( err == 0 );
#endif
    
    err = AudioFileOpenURL( (__bridge CFURLRef)([NSURL URLWithString:file_name]), kAudioFileReadPermission, file_type, &outAudioFile);
    
#if DEBUG
    assert( err == 0 );
#endif
    
    thePropertySize = sizeof(inFormat);
    
    err = AudioFileGetProperty(outAudioFile, kAudioFilePropertyDataFormat, &thePropertySize, &inFormat);
    
#if DEBUG
    assert( err == 0 );
#endif
    
    err = ExtAudioFileGetProperty(outExtAudioFile, kExtAudioFileProperty_FileDataFormat, &thePropertySize, outFormat);
    
    //int channels_per_frame = outFormat->mChannelsPerFrame;
    
    #if DEBUG
        assert( err == 0 );
    #endif
    
    if ( false ) { // mono
        
        outChannelLayout->mChannelLayoutTag = kAudioChannelLayoutTag_Mono;
    }
    else {
        
        outChannelLayout->mChannelLayoutTag = kAudioChannelLayoutTag_Stereo;
    }
    
    if ( [extention isEqualToString:@"mp3"] ) {
        
        outChannelLayout->mChannelBitmap = 0;
        outChannelLayout->mNumberChannelDescriptions = 0;
        outChannelLayout->mChannelDescriptions[0].mChannelFlags = 0;
        outChannelLayout->mChannelDescriptions[0].mChannelLabel = 0;
        
        outFormat->mSampleRate = outFormat->mSampleRate;
        outFormat->mFormatID = kAudioFormatLinearPCM;
        outFormat->mChannelsPerFrame = 2;
        outFormat->mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
        outFormat->mFramesPerPacket	= 1;
        outFormat->mBitsPerChannel = 16;
        outFormat->mBytesPerPacket	= 1;
        outFormat->mBytesPerFrame	= 1;
        
        err = ExtAudioFileSetProperty(outExtAudioFile, kExtAudioFileProperty_ClientDataFormat, thePropertySize, outFormat);
        err = ExtAudioFileSetProperty(outExtAudioFile, kExtAudioFileProperty_ClientChannelLayout, sizeof(AudioChannelLayout), outChannelLayout);
    }
    
    *frameSize = 1;
    
#if DEBUG
    assert( err == 0 );
#endif
    
    //UInt32 frames;
    //UInt32 * frames_ptr = &frames;
    
    // Get the total frame count
    thePropertySize = sizeof(theFileLengthInFrames);
    
    err = ExtAudioFileGetProperty(outExtAudioFile, kExtAudioFileProperty_FileLengthFrames, &thePropertySize, &theFileLengthInFrames);
    
    // Read all the data into memory
    UInt32 theFramesToRead = (UInt32)theFileLengthInFrames;
    UInt32 dataSize = theFramesToRead * outFormat->mBytesPerFrame;
    
    if( outFormat->mBytesPerFrame == 0 ) {
        
        dataSize = theFramesToRead * thePropertySize * outFormat->mChannelsPerFrame / 8;
    }
    
    if(err == noErr)
    {
        // success
        *outDataSize = dataSize;
        
        if ( outFormat->mBitsPerChannel == 16 ) {
            
            if ( outFormat->mChannelsPerFrame == 2 ) {
                
                *outDataFormat = AL_FORMAT_STEREO16;
            }
            else {
                
                *outDataFormat = AL_FORMAT_MONO16;
            }
        }
        else {
            
            if ( outFormat->mChannelsPerFrame == 2) {
                
                *outDataFormat = AL_FORMAT_STEREO8;
            }
            else {
                *outDataFormat = AL_FORMAT_MONO8;
            }
        }
        
        *outSampleRate = outFormat->mSampleRate;
    }
    
#if DEBUG
    assert( err == 0 );
#endif
    
    *ext_audio_file = outExtAudioFile;
    *audio_file = outAudioFile;
}

+(bool)readSample:(AUDIO_SOUND_CHUNK *) chunk
         withSize:(int) size
       withFrames:(int) frames
    withFrameSize:(int) frameSize
     withChannels:(int) channelsPerFrame
         fromFile:(ExtAudioFileRef *) file {
    
    //NSError * error;
    OSStatus err;
    
    AudioBufferList theDataBuffer;
    
    UInt32 frames_to_read = 0;
    int size_to_read = 0;
    
    if ( size ) {
        
        frames_to_read = size / frameSize;
        size_to_read = size;
    }
    else if ( frames ) {
        
        frames_to_read = frames;
        size_to_read = frames * frameSize * channelsPerFrame;
    }
    
    chunk->Size = size_to_read;
    
    chunk->Data = malloc( size_to_read );
    
    #if DEBUG
        assert( chunk->Data != NULL );
    #endif
    
    theDataBuffer.mNumberBuffers = 1;
    theDataBuffer.mBuffers[0].mDataByteSize = size_to_read;
    theDataBuffer.mBuffers[0].mNumberChannels = channelsPerFrame;
    theDataBuffer.mBuffers[0].mData = chunk->Data;
    
    //abort();
    //frames_to_read is always halved why?
    
    err = ExtAudioFileRead( *file, &frames_to_read, &theDataBuffer );
    
    #if DEBUG
        assert( err == 0 );
    #endif
    
    return frames_to_read == 0;
}

+(void)closeAudioFile:(ExtAudioFileRef *) file
        withAudioFile:(AudioFileID *) audio_file{
    
    #if __AUDIO_OPENAL__
        OSStatus err = ExtAudioFileDispose( *file );
        
        delete file;
        
    #if DEBUG
        assert( err == 0 );
    #endif
        
        err = AudioFileClose( *audio_file );
        
        delete audio_file;
        
        #if DEBUG
            assert( err == 0 );
        #endif
    #endif
}

@end
