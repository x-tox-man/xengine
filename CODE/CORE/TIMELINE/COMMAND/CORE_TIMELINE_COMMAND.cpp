//
//  CORE_TIMELINE_COMMAND.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "CORE_TIMELINE_COMMAND.h"

/*template<>
void CORE_TIMELINE_COMMAND::CustomSerialize<std::true_type>(CORE_DATA_STREAM & stream) {
    
    InnerSerialize(stream);
}

template<>
void CORE_TIMELINE_COMMAND::CustomSerialize<std::false_type>(CORE_DATA_STREAM & stream) {
    
    InnerSerialize(stream);
}*/

CORE_TIMELINE_COMMAND::CORE_TIMELINE_COMMAND() {
    
}

CORE_TIMELINE_COMMAND::~CORE_TIMELINE_COMMAND() {
    
}

void CORE_TIMELINE_COMMAND::Apply() {
    
}

void CORE_TIMELINE_COMMAND::InnerSerialize(CORE_DATA_STREAM & stream) {
    
}

void CORE_TIMELINE_COMMAND::InnerDeSerialize(CORE_DATA_STREAM & stream) {
    
}
