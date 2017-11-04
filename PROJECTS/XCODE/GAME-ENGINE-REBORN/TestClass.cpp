//
//  TestClass.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "TestClass.h"
#include "CORE_DATA_STREAM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( TestClass )
    XS_DEFINE_ClassMember( "TestInt", int, TestInt )
XS_END_INTERNAL_MEMORY_LAYOUT

TestClass::TestClass( const TestClass & other ) {
    
}

TestClass::~TestClass() {
    
}
