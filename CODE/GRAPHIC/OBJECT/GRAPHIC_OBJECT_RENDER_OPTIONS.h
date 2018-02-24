//
//  GRAPHIC_OBJECT_RENDER_OPTIONS.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_OBJECT_RENDER_OPTIONS_hpp
#define GRAPHIC_OBJECT_RENDER_OPTIONS_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_VECTOR.h"

XS_CLASS_BEGIN( GRAPHIC_OBJECT_RENDER_OPTIONS )

    GRAPHIC_OBJECT_RENDER_OPTIONS();
    ~GRAPHIC_OBJECT_RENDER_OPTIONS();

    inline const CORE_MATH_VECTOR & GetPosition() const { return Position; }
    inline CORE_MATH_VECTOR & GetPosition() { return Position; }
    inline void SetPosition( const CORE_MATH_VECTOR & position ) { Position = position; }
    inline void SetOrientation( const CORE_MATH_QUATERNION & orientation ) { Orientation = orientation; }

    inline const CORE_MATH_VECTOR & GetScaleFactor() const { return ScaleFactor; }
    inline CORE_MATH_VECTOR & GetScaleFactor() { return ScaleFactor; }
    inline void SetScaleFactor( const CORE_MATH_VECTOR & scale_factor ) { ScaleFactor = scale_factor; };

    inline const CORE_MATH_QUATERNION & GetOrientation() const { return Orientation; }
    inline CORE_MATH_QUATERNION & GetOrientation() { return Orientation; }

    inline void SetParent( GRAPHIC_OBJECT_RENDER_OPTIONS * parent ) { Parent = parent; }
    inline GRAPHIC_OBJECT_RENDER_OPTIONS * GetParent() const { return Parent; }
    inline void SetTexturing( bool texturing ) { Texturing = texturing; }
    inline bool IsTexturingEnabled() const { return Texturing; }

private:

    CORE_MATH_QUATERNION
        Orientation;
    CORE_MATH_VECTOR
        Position,
        ScaleFactor;
    GRAPHIC_OBJECT_RENDER_OPTIONS
        * Parent;
    bool
        Texturing;

XS_CLASS_END

#endif /* GRAPHIC_OBJECT_RENDER_OPTIONS_hpp */
