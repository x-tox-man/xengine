//
//  ApplicationSoundBank.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/11/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "ApplicationSoundBank.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( ApplicationSoundBank )
    //CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( CORE_HELPERS_IDENTIFIER, ApplicationSoundBank, GetSoundIdentifier)
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( ApplicationSoundBank )

ApplicationSoundBank::ApplicationSoundBank() {
    
}

ApplicationSoundBank::~ApplicationSoundBank() {

}

const CORE_HELPERS_IDENTIFIER & GetSoundIdentifier( int sound_id ) {
    
    switch ( sound_id) {
        case 0:
            return ApplicationSoundBank::BellSound;
            break;
            
        case 1:
            return ApplicationSoundBank::BubbleSound;
            break;
            
        case 2:
            return ApplicationSoundBank::ElectricSound;
            break;
            
        default:
            return ApplicationSoundBank::RammsteinSound;
    }
}

const CORE_HELPERS_IDENTIFIER
    ApplicationSoundBank::BellSound( "BellSound" ),
    ApplicationSoundBank::BubbleSound( "BubbleSound" ),
    ApplicationSoundBank::ElectricSound( "ElectricSound" ),
    ApplicationSoundBank::RammsteinSound( "RammsteinSound" );
