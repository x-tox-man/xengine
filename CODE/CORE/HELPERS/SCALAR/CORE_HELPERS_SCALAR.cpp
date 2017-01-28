//
//  CORE_HELPERS_SCALAR.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_SCALAR.h"
#include "CORE_DATA_STREAM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_SCALAR )
    XS_DEFINE_ClassMember( SCALAR, Value )
    XS_DEFINE_ClassMember( int, ValueIndex )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_CLASS_SERIALIZER_TemplateScalar( SCALAR )
