//
//  OPTIONS_PAGE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "OPTIONS_PAGE.h"

OPTION_PAGE::OPTION_PAGE() :
    GRAPHIC_UI_FRAME(),
    Presenter() {
    
    Presenter.Initialize( (GRAPHIC_UI_FRAME*) this );
}

OPTION_PAGE::~OPTION_PAGE() {
    
}

void OPTION_PAGE::Initialize() {
    
}

void OPTION_PAGE::Update( const float ) {
    
}
