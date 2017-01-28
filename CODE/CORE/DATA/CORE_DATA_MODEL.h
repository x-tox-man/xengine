//
//  CORE_DATA_MODEL.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_DATA_MODEL_hpp
#define CORE_DATA_MODEL_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_HELPERS_OBSERVABLE.h"

XS_CLASS_BEGIN(CORE_DATA_MODEL)

CORE_DATA_MODEL();

XS_DEFINE_OBSERVABLE(CORE_DATA_MODEL)

XS_CLASS_END

#define MODEL_ACCESS( __TYPE__, __NAME__ ) \
    __TYPE__ __NAME__; \
    const __TYPE__ & Get##__NAME__() const { return __NAME__; } \
    __TYPE__ & Get##__NAME__() { return __NAME__; } \
    void Set##__NAME__( const __TYPE__ & val ) { __NAME__ = val; }

#endif /* CORE_DATA_MODEL_hpp */
