//
//  CORE_TIMELINE_COMMAND.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 8/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_TIMELINE_COMMAND_h
#define CORE_TIMELINE_COMMAND_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "CORE_DATA_STREAM.h"

class CORE_TIMELINE_COMMAND  {

public :
    
    CORE_TIMELINE_COMMAND();
    virtual ~CORE_TIMELINE_COMMAND();
    
    /*template<typename __BOOL_TYPE__>
    void CustomSerialize(CORE_DATA_STREAM & stream) {
        
        CORE_RUNTIME_Abort();
    }*/
    
    //Let specific implementations do the job
    virtual void Apply() = 0;
    virtual void InnerSerialize(CORE_DATA_STREAM & stream) = 0;
    virtual void InnerDeSerialize(CORE_DATA_STREAM & stream) = 0;
};

#endif /* CORE_TIMELINE_COMMAND_hpp */
