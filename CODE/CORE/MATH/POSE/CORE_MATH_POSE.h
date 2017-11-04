//
//  CORE_MATH_POSE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_POSE__
#define __GAME_ENGINE_REBORN__CORE_MATH_POSE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_QUATERNION.h"

XS_CLASS_BEGIN_WITH_COPY( CORE_MATH_POSE )

CORE_MATH_POSE();

XS_DEFINE_SERIALIZABLE

    ~CORE_MATH_POSE();

    void FromMatrix( const CORE_MATH_MATRIX & matrix );
    void FromMatrix( const float * mat );

    void ToMatrix( CORE_MATH_MATRIX & matrix ) const;
    void ToMatrix( float * matrix ) const;
    void Lerp( const CORE_MATH_POSE & other, CORE_MATH_POSE & result, float percentage );

    inline CORE_MATH_VECTOR & GetPosition() { return Position; }
    inline CORE_MATH_QUATERNION & GetOrientation() { return Orientation; }
    inline const CORE_MATH_VECTOR & GetPosition() const { return Position; }
    inline const CORE_MATH_QUATERNION & GetOrientation() const { return Orientation; }

    inline void SetPosition( const CORE_MATH_VECTOR & position ) { Position = position; }
    inline void SetOrientation( const CORE_MATH_QUATERNION & orientation ) { Orientation = orientation; }

    CORE_MATH_POSE & operator *= ( const CORE_MATH_POSE & other);
    CORE_MATH_POSE & operator = ( const CORE_MATH_POSE & other);
    friend CORE_MATH_POSE operator * ( const CORE_MATH_POSE & lhs, const CORE_MATH_POSE & rhs);
    friend inline CORE_MATH_POSE operator + ( const CORE_MATH_POSE & lhs, const CORE_MATH_POSE & rhs);
    friend inline bool operator == ( const CORE_MATH_POSE & lhs, const CORE_MATH_POSE & rhs);

    void CopyFrom( const CORE_MATH_POSE & other );

private :

    CORE_MATH_VECTOR
        Position;
    CORE_MATH_QUATERNION
        Orientation;

XS_CLASS_END

CORE_MATH_POSE operator * ( const CORE_MATH_POSE & lhs, const CORE_MATH_POSE & rhs);

inline CORE_MATH_POSE operator + ( const CORE_MATH_POSE & lhs, const CORE_MATH_POSE & rhs) {
    
    CORE_MATH_POSE pose;
    
    pose.SetPosition( lhs.GetPosition() + rhs.GetPosition() );
    pose.SetOrientation( lhs.GetOrientation() * rhs.GetOrientation() );
    
    pose.GetPosition().W(1.0f);
    
    return pose;
}

inline bool operator == ( const CORE_MATH_POSE & lhs, const CORE_MATH_POSE & rhs) {
    
    return lhs.GetOrientation() == rhs.GetOrientation() && lhs.GetPosition() == rhs.GetPosition();
}

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_POSE__) */
