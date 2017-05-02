//
//  ApplicationSoundBank.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef ApplicationSoundBank_hpp
#define ApplicationSoundBank_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"

XS_CLASS_BEGIN( ApplicationSoundBank )

CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( ApplicationSoundBank );

    ApplicationSoundBank();
    ~ApplicationSoundBank();

    const CORE_HELPERS_IDENTIFIER & GetSoundIdentifier( int sound_id );

    const static CORE_HELPERS_IDENTIFIER
        BellSound,
        BubbleSound,
        ElectricSound,
        RammsteinSound;

XS_CLASS_END


#endif /* ApplicationSoundBank_hpp */
