//
//  RESOURCE_SOUND.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 16/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef RESOURCE_SOUND_hpp
#define RESOURCE_SOUND_hpp

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "RESOURCE_SOUND_MP3_LOADER.h"

class AUDIO_SOUND;

class RESOURCE_SOUND : public RESOURCE< RESOURCE_SOUND, RESOURCE_SOUND_MP3_LOADER > {
    
    public :
    
    XS_DEFINE_SERIALIZABLE
    
    RESOURCE_SOUND();
    virtual ~RESOURCE_SOUND();
    
    inline void SetSoundRawData( void * raw_data) { RawData = raw_data; }
    inline const void * GetSoundRawData() const { return RawData; }
    
private:
    
    char * Path;
    void * RawData;
    
    XS_CLASS_END

#endif /* RESOURCE_SOUND_hpp */
