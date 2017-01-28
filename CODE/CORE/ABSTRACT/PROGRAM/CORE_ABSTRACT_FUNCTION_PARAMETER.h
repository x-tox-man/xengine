//
//  CORE_ABSTRACT_FUNCTION_PARAMETER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/01/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_ABSTRACT_FUNCTION_PARAMETER_h
#define CORE_ABSTRACT_FUNCTION_PARAMETER_h

#include "CORE_HELPERS_CLASS.h"

class CORE_ABSTRACT_FUNCTION_PARAMETER {
    
public:
    virtual ~CORE_ABSTRACT_FUNCTION_PARAMETER() = 0;
};

template <typename __TYPE__ >
class CORE_ABSTRACT_FUNCTION_INSTANCE_PARAMETER : public CORE_ABSTRACT_FUNCTION_PARAMETER {
    
public:
    
    CORE_ABSTRACT_FUNCTION_INSTANCE_PARAMETER( __TYPE__ parameter ) {
        
        Member = parameter;
    }
    
    virtual ~CORE_ABSTRACT_FUNCTION_INSTANCE_PARAMETER() {
        
    }
    
    __TYPE__ GetMember() {
        
        return Member;
    };

private:
    __TYPE__ Member;
};

#endif /* CORE_ABSTRACT_FUNCTION_PARAMETER_h */
