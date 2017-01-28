//
//  TestClass2.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__TestClass2__
#define __GAME_ENGINE_REBORN__TestClass2__

#include "CORE_HELPERS_CLASS.h"
#include "TestClass.h"
#include "CORE_MEMORY.h"

#include <vector>

XS_CLASS_BEGIN( TestClass2 )

TestClass2() :
    TestInt( 24 ),
    TestInnerClass(),
    TestInnerClassPtr(),
    TestChar( 'c' ),
    TestCharArray(),
    TestFloat( 1.1234f ),
    TestVector()
{
    TestCharArray = (char *) CORE_MEMORY_ALLOCATOR::Allocate( 8 );
    strcpy( TestCharArray, "coucoute\0" );
}

void Initialize() {
    
    TestInnerClassPtr = new TestClass;
}

XS_DEFINE_SERIALIZABLE

public:

int TestInt;
TestClass TestInnerClass;
TestClass::PTR TestInnerClassPtr;
char TestChar;
char * TestCharArray;
float TestFloat;
std::vector< TestClass > TestVector;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__TestClass2__) */
