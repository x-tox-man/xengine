//
//  CORE_HELPERS_SCALAR.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_SCALAR.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_SCALAR )
    XS_DEFINE_ClassMember( "Value", SCALAR, Value )
    XS_DEFINE_ClassMember( "ValueIndex", int, ValueIndex )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_CLASS_SERIALIZER_TemplateScalar( SCALAR )
