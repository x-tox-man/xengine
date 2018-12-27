//
//  RESOURCE_SOUND_MP3_LOADER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 16/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef RESOURCE_SOUND_MP3_LOADER_hpp
#define RESOURCE_SOUND_MP3_LOADER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE_LOADER.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "CORE_FILESYSTEM.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "AUDIO_BANK_SOUND_LOAD_OPTION.h"

class RESOURCE_SOUND;

typedef RESOURCE_LOADER< RESOURCE_SOUND > RESOURCE_LOADER_AUDIO_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR(RESOURCE_SOUND_MP3_LOADER, RESOURCE_LOADER_AUDIO_TYPE )

    RESOURCE_SOUND_MP3_LOADER();
    virtual ~RESOURCE_SOUND_MP3_LOADER();

    virtual RESOURCE_SOUND * Load( const CORE_FILESYSTEM_PATH & file, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty );

    virtual RESOURCE_SOUND * Load( CORE_DATA_STREAM & stream, int resource_load_flag = 0, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier = CORE_HELPERS_UNIQUE_IDENTIFIER::Empty);

    virtual void ReloadResource( RESOURCE_SOUND * resource_to_reload );

XS_CLASS_END


#endif /* RESOURCE_SOUND_MP3_LOADER_hpp */
