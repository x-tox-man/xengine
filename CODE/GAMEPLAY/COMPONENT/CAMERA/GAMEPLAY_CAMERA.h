//
//  GAMEPLAY_CAMERA.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_CAMERA_hpp
#define GAMEPLAY_CAMERA_hpp

#include "GRAPHIC_CAMERA.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

class GAMEPLAY_COMPONENT_POSITION;

XS_CLASS_BEGIN(GAMEPLAY_CAMERA )

    GAMEPLAY_CAMERA();
    ~GAMEPLAY_CAMERA();

    void Initialize( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );

    inline const CORE_MATH_VECTOR & GetPosition() { return Camera->GetPosition(); }
    void UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & rotation_quat );

    inline GRAPHIC_CAMERA * GetCamera() { return Camera; }
    inline GAMEPLAY_COMPONENT_ENTITY * GetEntity() { return Entity; }

    void NotifyPropertyChanged(GAMEPLAY_COMPONENT_POSITION *);

private:

    GAMEPLAY_COMPONENT_ENTITY
        * Entity;
    GRAPHIC_CAMERA
        * Camera;

XS_CLASS_END

#endif /* GAMEPLAY_CAMERA_hpp */
