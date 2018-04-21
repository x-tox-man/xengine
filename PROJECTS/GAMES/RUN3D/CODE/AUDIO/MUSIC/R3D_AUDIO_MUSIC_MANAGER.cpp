//
//  R3D_AUDIO_MUSIC_MANAGER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_AUDIO_MUSIC_MANAGER.h"
#include "CORE_FILESYSTEM.h"
#include "AUDIO_SYSTEM.h"

R3D_AUDIO_MUSIC_MANAGER::R3D_AUDIO_MUSIC_MANAGER() {
    
}

void R3D_AUDIO_MUSIC_MANAGER::Initialize() {
    
    #if !PLATFORM_ANDROID
        AUDIO_SYSTEM::GetInstance().Initialize();
    #endif
    
    AUDIO_SYSTEM::GetInstance().GetBank().RegisterSoundFilePath(
                                                                CORE_FILESYSTEM_PATH::FindFilePath( "a-tone" , "ogg", "AUDIO" ),
                                                                ATone,
                                                                AUDIO_BANK_SOUND_LOAD_OPTION_SoundStartupLoad, "ogg" );
    
    AUDIO_SYSTEM::GetInstance().GetBank().RegisterSoundFilePath(
                                                                CORE_FILESYSTEM_PATH::FindFilePath( "Rammstein-Du-Hast" , "ogg", "AUDIO" ),
                                                                MusicPulse,
                                                                AUDIO_BANK_SOUND_LOAD_OPTION_StartupStreamMusic, "ogg" );
    
    AUDIO_SYSTEM::GetInstance().GetBank().Load();
}


CORE_HELPERS_IDENTIFIER
    R3D_AUDIO_MUSIC_MANAGER::ElectricSound( "ElectricSound" ),
    R3D_AUDIO_MUSIC_MANAGER::MusicPulse( "MusicPulse" ),
    R3D_AUDIO_MUSIC_MANAGER::ATone( "ATone" );
