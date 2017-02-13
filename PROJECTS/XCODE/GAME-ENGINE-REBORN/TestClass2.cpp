//
//  TestClass2.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "TestClass2.h"
#include "CORE_DATA_STREAM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( TestClass2 )
    XS_DEFINE_ClassMember( TestClass, TestInnerClass )
    XS_DEFINE_ClassMember( TestClass, &TestInnerClassPtr )
    XS_DEFINE_ClassMember( int, TestInt )
    XS_DEFINE_ClassMember( char, TestChar )
    XS_DEFINE_ClassMemberArray( char, TestCharArray, (int) strlen(TestCharArray) )
    XS_DEFINE_ClassMember( float, TestFloat )
    XS_DEFINE_ClassMember( std::vector< TestClass >, TestVector )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( TestClass )

TestClass2::~TestClass2() {
    
    CORE_MEMORY_ALLOCATOR_Free( TestCharArray );
}
