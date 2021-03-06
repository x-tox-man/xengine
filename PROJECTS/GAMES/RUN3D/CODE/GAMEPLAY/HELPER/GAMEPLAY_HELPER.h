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
#include "PHYSICS_COLLISION_TYPE.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"

XS_CLASS_BEGIN( GAMEPLAY_HELPER )

    static void Set3DObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    static GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR Set3DHeighFieldObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    static void Set3DPlane( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & size );
    static void Scale3dObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, float scale );
    static void Scale3dComponent( GAMEPLAY_COMPONENT_RENDER::PTR entity, float scale );

    static void SetEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    static void SetSecondaryEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );
    static void SetShadowmapEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void SetTexture( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const char * texture_name, const CORE_FILESYSTEM_PATH & path, const CORE_HELPERS_IDENTIFIER & identifier = GRAPHIC_SHADER_PROGRAM::ColorTexture );
    static void SetNormal( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const char * texture_name, const CORE_FILESYSTEM_PATH & path, const
                          CORE_HELPERS_IDENTIFIER & identifier = GRAPHIC_SHADER_PROGRAM::NormalTexture );
    static void SetDisplacement( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const char * texture_name, const CORE_FILESYSTEM_PATH & path, const
                      CORE_HELPERS_IDENTIFIER & identifier = GRAPHIC_SHADER_PROGRAM::DisplacementTexture );
    static void SetTextureRepeating(GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_IDENTIFIER & identifier);
    static void SetScript( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_FILESYSTEM_PATH & path );

    static void ConfigureGroundSpring( GAMEPLAY_COMPONENT_ENTITY::PTR entity );

    static void AddToWorld( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToSpecialEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToWorldTransparent( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToMotion( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToScripts( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToAnimations( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void AddToPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity, PHYSICS_COLLISION_TYPE group, PHYSICS_COLLISION_TYPE collides_with, bool enable = false );
    static void AddStaticToPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity, PHYSICS_COLLISION_TYPE group, PHYSICS_COLLISION_TYPE collides_with );

    static void AddToLighting( GAMEPLAY_COMPONENT_ENTITY::PTR entity, GRAPHIC_SHADER_LIGHT * light );

    static void SetPhysicsSphereObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation, float mass );
    static void SetPhysicsBoxObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & half_extent, const CORE_MATH_QUATERNION & orientation, float mass );
    static void SetPhysicsCylinderObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float radius, float height, const CORE_MATH_QUATERNION & orientation, float mass );
    static void SetPhysicsObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass );
    static void SetPhysicsGroundHeightMapObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass );
    static void SetPhysicsFlatGroundObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass, float constant );

    static void SetPhysicsCustomMaterialCallback( GAMEPLAY_COMPONENT_ENTITY::PTR entity );

    static void InitializeCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction, GRAPHIC_CAMERA & camera, const CORE_MATH_VECTOR & up );

    static void GetElevation( GAMEPLAY_COMPONENT_ENTITY::PTR entity, CORE_MATH_VECTOR & out_position, CORE_MATH_VECTOR & out_normal );

    static void EnableEffectSpecial( GAMEPLAY_COMPONENT_ENTITY::PTR entity );
    static void DisableEffectSpecial( GAMEPLAY_COMPONENT_ENTITY::PTR entity );

XS_CLASS_END

#endif /* GAMEPLAY_HELPER_hpp */
