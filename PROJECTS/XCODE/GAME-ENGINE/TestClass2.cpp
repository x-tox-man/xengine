//
//  TestClass2.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 29/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "TestClass2.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( TestClass2 )
    XS_DEFINE_ClassMember( "TestInnerClass", TestClass, TestInnerClass )
    XS_DEFINE_ClassMember( "TestInnerClassPtr", TestClass, &TestInnerClassPtr )
    XS_DEFINE_ClassMember( "TestInt", int, TestInt )
    XS_DEFINE_ClassMember( "TestChar", char, TestChar )
    XS_DEFINE_ClassMemberArray( "TestCharArray", char, TestCharArray, (int) strlen(TestCharArray) )
    XS_DEFINE_ClassMember( "TestFloat", float, TestFloat )
    XS_DEFINE_ClassMember( "TestVector", std::vector< TestClass >, TestVector )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( TestClass3 )
    XS_DEFINE_ClassMember( "TestInnerClass", TestClass, TestInnerClass )
    XS_DEFINE_ClassMember( "TestInnerClassPtr", TestClass, &TestInnerClassPtr )
    XS_DEFINE_ClassMember( "TestInt", int, TestInt )
    XS_DEFINE_ClassMember( "TestChar", char, TestChar )
    XS_DEFINE_ClassMemberArray( "TestCharArray", char, (char**) &TestCharArray, (int) strlen(TestCharArray) )
    XS_DEFINE_ClassMember( "TestFloat", float, TestFloat )
    XS_DEFINE_ClassMember( "TestVector", std::vector< TestClass >, TestVector )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( TestClass )

TestClass2::~TestClass2() {
    
    CORE_MEMORY_ALLOCATOR_Free( TestCharArray );
}
