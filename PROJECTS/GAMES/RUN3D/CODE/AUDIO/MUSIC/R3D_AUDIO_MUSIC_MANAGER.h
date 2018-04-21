//
//  R3D_AUDIO_MUSIC_MANAGER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_AUDIO_MUSIC_MANAGER_hpp
#define R3D_AUDIO_MUSIC_MANAGER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"

XS_CLASS_BEGIN( R3D_AUDIO_MUSIC_MANAGER )

    R3D_AUDIO_MUSIC_MANAGER();

    void Initialize();

    static CORE_HELPERS_IDENTIFIER
        ElectricSound,
        MusicPulse,
        ATone;

XS_CLASS_END

#endif /* R3D_AUDIO_MUSIC_MANAGER_hpp */
