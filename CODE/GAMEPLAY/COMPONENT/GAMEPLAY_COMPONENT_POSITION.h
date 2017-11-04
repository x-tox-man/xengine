//
//  GAMEPLAY_COMPONENT_POSITION.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_POSITION__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_POSITION__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_RAY.h"
#include "CORE_HELPERS_OBSERVABLE.h"
#include "CORE_MATH_POSE.h"

class GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION;

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT_POSITION();
    virtual ~GAMEPLAY_COMPONENT_POSITION();

    XS_DEFINE_OBSERVABLE( GAMEPLAY_COMPONENT_POSITION )

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GAMEPLAY_COMPONENT_POSITION );

    friend class GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION;

    void * operator new(size_t size);
    void operator delete  ( void* ptr );

    CORE_HELPERS_FACTORY_Element( GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Position )

    struct INTERNAL_ARRAY{
        int LastIndex;
        GAMEPLAY_COMPONENT_POSITION * MemoryArray;
    };

    inline const CORE_MATH_VECTOR & GetPosition() const { return Pose.GetPosition(); }
    inline CORE_MATH_VECTOR & GetPosition() { return Pose.GetPosition(); }

    inline void SetPositionOffset( const CORE_MATH_VECTOR & offset ) { PositionOffset = offset; }
    inline CORE_MATH_VECTOR & GetPositionOffset() { return PositionOffset; }

    inline CORE_MATH_QUATERNION & GetOrientation() { return Pose.GetOrientation(); }
    inline const CORE_MATH_QUATERNION & GetOrientation() const { return Pose.GetOrientation(); }

    inline CORE_MATH_VECTOR & GetVelocity() { return Velocity; }
    inline CORE_MATH_QUATERNION & GetSpin() { return Spin; }

    inline void SetPosition( const CORE_MATH_VECTOR & position ) { Pose.SetPosition( position ); /*NotifyObservers();*/ }
    inline void SetOrientation( const CORE_MATH_QUATERNION & orientation ) { Pose.SetOrientation( orientation ); /*NotifyObservers();*/ }

    bool Intersects( const CORE_MATH_RAY & ray );

    virtual GAMEPLAY_COMPONENT * GetComponentAt( int index, int offset ) override {
        
        return (GAMEPLAY_COMPONENT *) &(*InternalVector)[index].MemoryArray[offset];
    }

    static void Clear();
    static void SaveToStream( CORE_DATA_STREAM & stream );
    static void LoadFromStream( CORE_DATA_STREAM & stream );

    static int
        LastIndex,
        LastOffset;

private :

    CORE_MATH_VECTOR
        PositionOffset,
        Velocity;
    CORE_MATH_QUATERNION
        Spin;
    CORE_MATH_POSE
        Pose;
    static std::vector< INTERNAL_ARRAY >
        * InternalVector;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_POSITION__) */
