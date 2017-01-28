//
//  CORE_APPLICATION.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/11/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "CORE_APPLICATION.h"

CORE_APPLICATION::~CORE_APPLICATION() {

}

void CORE_APPLICATION::Initialize() {
    
    CORE_RUNTIME_Abort();
}

void CORE_APPLICATION::Finalize() {
    
    CORE_RUNTIME_Abort();
}

void CORE_APPLICATION::Render() {
    
    CORE_RUNTIME_Abort();
}

void CORE_APPLICATION::Update( float time_step ) {
    
    CORE_RUNTIME_Abort();
}

void CORE_APPLICATION::setApplicationCallback( CORE_HELPERS_CALLBACK & callback, int callbackId )
{
    
}

CORE_APPLICATION * CORE_APPLICATION::Instance = NULL;