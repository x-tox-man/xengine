#pragma once

#if __AUDIO_FILE_OGG__
    #define AUDIO_OGG 1
#elif __AUDIO_FILE_MPG__
    #define AUDIO_MPG 1
#elif __AUDIO_FILE_OSX__
    #define AUDIO_FILE_OSX 1
#elif __AUDIO_FILE_IOS__
    #define AUDIO_FILE_IOS 1
#else
    #error "Must define one audiofile type"
#endif

#if __AUDIO_OPENAL__
    #define AUDIO_PLATFORM_OPENAL 1
#elif __AUDIO_OPENSLES__
    #define AUDIO_PLATFORM_OPENSLES 1
#else
    #error "Must define one audio platform"
#endif
