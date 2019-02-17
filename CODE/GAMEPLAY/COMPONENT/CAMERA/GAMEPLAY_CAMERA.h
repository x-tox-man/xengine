//
//  GAMEPLAY_CAMERA.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_CAMERA_hpp
#define GAMEPLAY_CAMERA_hpp

#include "GRAPHIC_CAMERA.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

class GAMEPLAY_COMPONENT_POSITION;

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( GAMEPLAY_CAMERA, GAMEPLAY_COMPONENT_ENTITY )

    GAMEPLAY_CAMERA();
    virtual ~GAMEPLAY_CAMERA();

    void Initialize( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction, const CORE_MATH_VECTOR & up );

    inline const CORE_MATH_VECTOR & GetPosition() { return Camera->GetPosition(); }
    void UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction );

    inline GRAPHIC_CAMERA * GetCamera() { return Camera; }

    void NotifyPropertyChanged(GAMEPLAY_COMPONENT_POSITION *);

    virtual GAMEPLAY_COMPONENT_ENTITY * Clone() const override {
        
        return new GAMEPLAY_CAMERA( *this );
    }

private:

    GRAPHIC_CAMERA
        * Camera;

XS_CLASS_END

#endif /* GAMEPLAY_CAMERA_hpp */
