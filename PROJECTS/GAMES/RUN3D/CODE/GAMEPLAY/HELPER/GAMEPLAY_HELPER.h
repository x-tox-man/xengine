//
//  GAMEPLAY_HELPER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 16/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef GAMEPLAY_HELPER_hpp
#define GAMEPLAY_HELPER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_CAMERA.h"
#include "GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h"

XS_CLASS_BEGIN( GAMEPLAY_HELPER )

    static void CreateComponent_PositionRenderPhysicsScriptAnimation( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void CreateComponent_PositionRenderScriptAnimation( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void CreateComponent_PositionRenderAnimation( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void CreateComponent_PositionRenderScript( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void CreateComponent_PositionRenderPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void CreateComponent_PositionRender( GAMEPLAY_COMPONENT_ENTITY::PTR entity );

    static void Set3DObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    static GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR Set3DHeighFieldObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    static void SetEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    static void SetTexture( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const char * texture_name, const CORE_FILESYSTEM_PATH & path, const CORE_HELPERS_IDENTIFIER & identifier = GRAPHIC_SHADER_PROGRAM::ColorTexture );

    static void SetScript( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_FILESYSTEM_PATH & path );

    static void AddToWorld( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToScripts( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToAnimations( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddStaticToPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity );

    static void SetPosition( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position );
    static void SetOrientation( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_QUATERNION & orientation );
    static void SetPhysicsSphereObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation, float mass );
    static void SetPhysicsObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass );
    static void SetPhysicsGroundHeightMapObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass );

    static void InitializeCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation, GRAPHIC_CAMERA & camera );

XS_CLASS_END

#endif /* GAMEPLAY_HELPER_hpp */
