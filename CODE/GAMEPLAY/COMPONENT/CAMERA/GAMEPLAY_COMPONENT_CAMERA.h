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

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_CAMERA )

    GAMEPLAY_COMPONENT_CAMERA();
    ~GAMEPLAY_COMPONENT_CAMERA();

    //CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_CAMERA, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Camera)

    void Initialize( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction, const CORE_MATH_VECTOR & up );

    inline const CORE_MATH_VECTOR & GetPosition() { return Camera.GetPosition(); }
    void UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction );

    inline GRAPHIC_CAMERA & GetCamera() { return Camera; }

    static int
        ComponentType;

private:

    GRAPHIC_CAMERA
        Camera;

XS_CLASS_END

#endif /* GAMEPLAY_CAMERA_hpp */
