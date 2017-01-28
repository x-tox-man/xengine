//
//  TestClass.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__TestClass__
#define __GAME_ENGINE_REBORN__TestClass__

#include "CORE_HELPERS_CLASS.h"

template <typename __SPECIALIZED__ >
class TestTemplate {
    
public:
    
    float Initialize() {
        
        return __SPECIALIZED__::Initialize();
    }
    
    virtual float test() {
        
        return 0.0f;
    }
};

class TestTemplateSpecialized : public TestTemplate< TestTemplateSpecialized > {
    
public:
    
    static float Initialize() {
        
        float test = 0.1f;
        
        for ( int i = 0; i < 10; i++ ) {
            
            test += 0.1f * i;
        }
        
        return test;
    }
    
    virtual float test() {
        
        float test = 0.1f;
        
        for ( int i = 0; i < 10; i++ ) {
            
            test += 0.1f * i;
        }
        
        return test;
    }
};

XS_CLASS_BEGIN_WITH_COPY( TestClass )

TestClass() :
    TestInt( 26 ) {
    
}

TestClass & operator = ( const TestClass & other ) {
    
    TestInt = other.TestInt;
    
    return *this;
}

XS_DEFINE_SERIALIZABLE

public:

int
    TestInt;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__TestClass__) */
