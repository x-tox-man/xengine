//
//  CORE_SCALAR.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_CORE_SCALAR_h
#define GAME_ENGINE_REBORN_CORE_SCALAR_h

#include "CORE_HELPERS_CLASS.h"

union SCALAR {
    char CharacterValue;
    char * CharacterPointer;
    
    bool BinaryValue;
    
    //TODO: signed/unsigned
    int IntegerValue;
    int IntegerArray2[2];
    int IntegerArray3[3];
    int IntegerArray4[4];
    int * IntegerPointer;
    
    //TODO: float/double selection
    float FloatValue;
    float FloatArray2[2];
    float FloatArray3[3];
    float FloatArray4[4];
    float FloatMatrix4x4[16];
    float FloatMatrix3x3[9];
    float FloatMatrix4x3[12];
    float * FloatPointer;
    float Quaternion[4];
    
    double DoubleValue;
};

class CORE_SCALAR {
    
    XS_DEFINE_SERIALIZABLE
    
public:
    SCALAR
        Value;
    int
        ValueIndex;
};



#endif
