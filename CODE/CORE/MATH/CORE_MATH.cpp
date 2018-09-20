//
//  CORE_MATH.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 17/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH.h"

bool MATH_IsRougthlyEqual( const float first, const float second ) {
    
    return fabs(first - second) < TOLERANCE;
}

bool MATH_IsRougthlyEqual( const CORE_MATH_VECTOR & first, const CORE_MATH_VECTOR & second ) {
    
    for (int i =0; i< 4; i++) {
        
        if ( !MATH_IsRougthlyEqual( first[i], second[i]) ) {
            
            return false;
        }
    }
    
    return true;
}

bool MATH_IsRougthlyEqual( const CORE_MATH_QUATERNION & first, const CORE_MATH_QUATERNION & second ) {
    
    if( first == second ) {
        
        return true;
    }
    else {
        
        for (int i =0; i< 4; i++) {
            
            if ( !MATH_IsRougthlyEqual( first[i], second[i]) ) {
                
                return false;
            }
        }
    }
    
    
    return true;
}


bool MATH_IsRougthlyEqual( const CORE_MATH_MATRIX & first, const CORE_MATH_MATRIX & second ) {
    
    for (int i =0; i< 16; i++) {
        
        if ( !MATH_IsRougthlyEqual( first[i], second[i]) ) {
            
            return false;
        }
    }
    
    return true;
}

bool MATH_IsRougthlyEqual( const CORE_MATH_POSE & first, const CORE_MATH_POSE & second ) {
    
    return MATH_IsRougthlyEqual(first.GetPosition(), second.GetPosition() ) && MATH_IsRougthlyEqual(first.GetOrientation(), second.GetOrientation() );
}

float CORE_MATH_ToRadians( float degrees ) {
    
    return degrees * DEG_TO_RAD;
}
