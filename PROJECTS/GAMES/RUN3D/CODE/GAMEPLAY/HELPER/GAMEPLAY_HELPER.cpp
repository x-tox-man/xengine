//
//  GAMEPLAY_HELPER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 16/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "GAMEPLAY_HELPER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_SCRIPT.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "R3D_RESOURCES.h"
#include "RUN3D_APPLICATION.h"
#include "CORE_FILESYSTEM_FILE_WATCHER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "RESOURCE_IMAGE.h"
#include "PHYSICS_UTILS.h"
#include "CORE_MATH_RAY_SEGMENT.h"

void GAMEPLAY_HELPER::Set3DObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    auto render = entity->GetComponentRender();
    
    render->SetObject( *R3D_RESOURCES::GetInstance().FindResourceProxy( identifier ) );
}

void GAMEPLAY_HELPER::Scale3dObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, float scale ) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    Scale3dComponent( render, scale );
}

void GAMEPLAY_HELPER::Scale3dComponent( GAMEPLAY_COMPONENT_RENDER::PTR render, float scale ) {
    
    render->SetScaleFactor( scale );
}

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR GAMEPLAY_HELPER::Set3DHeighFieldObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    RESOURCE_IMAGE * height_map = (RESOURCE_IMAGE*) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath(identifier.GetIdentifier(), "png", "MAP" ) );
    
    float * heights = (float * ) height_map->GetImageRawData();
    
    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR object = new GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP( heights, height_map->GetImageInfo().Width, height_map->GetImageInfo().Height, 2.0f );
    object->SetHeightScale( 0.05f );
    object->InitializeShape();
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    render->GetObject().SetResource( object );

    return object;
}

void GAMEPLAY_HELPER::Set3DPlane( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & size ) {
    auto
        plan = new GRAPHIC_OBJECT_SHAPE_PLAN;
    
    plan->InitializeShape();
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    render->GetObject().SetResource( plan );
    
    render->GetObject().GetResource< GRAPHIC_OBJECT >()->GetMeshTable()[0]->GetTransform().Scale( size.X(), size.Y(), 1.0f );
}

void GAMEPLAY_HELPER::SetTexture( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const char * texture_name, const CORE_FILESYSTEM_PATH & path, const CORE_HELPERS_IDENTIFIER & identifier  ) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    auto mat = render->GetMaterial().GetResource< GRAPHIC_MATERIAL >();
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( texture_name ), path );
    
    if ( mat == NULL ) {
        RESOURCE_PROXY
            proxy( mat );
        
        render->SetMaterial( proxy );
        
        SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetTexture create mat\n" );
    }
    
    mat->SetTexture( identifier, new GRAPHIC_TEXTURE_BLOCK( text ) );
    SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetTexture ok %s\n", texture_name );
}

void GAMEPLAY_HELPER::SetNormal( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const char * texture_name, const CORE_FILESYSTEM_PATH & path, const CORE_HELPERS_IDENTIFIER & identifier  ) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    auto mat = render->GetMaterial().GetResource< GRAPHIC_MATERIAL >();
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( texture_name ), path );
    
    if ( mat == NULL ) {
        RESOURCE_PROXY
            proxy( mat );
        
        render->SetMaterial( proxy );
        
        SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetTexture create mat\n" );
    }
    
    mat->SetTexture( identifier, new GRAPHIC_TEXTURE_BLOCK( text ) );
    SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetNormal ok %s\n", texture_name );
}

void GAMEPLAY_HELPER::SetDisplacement( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const char * texture_name, const CORE_FILESYSTEM_PATH & path, const
                     CORE_HELPERS_IDENTIFIER & identifier ) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    auto mat = render->GetMaterial().GetResource< GRAPHIC_MATERIAL >();
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( texture_name ), path );
    
    if ( mat == NULL ) {
        RESOURCE_PROXY
        proxy( mat );
        
        render->SetMaterial( proxy );
        
        SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetTexture create mat\n" );
    }
    
    mat->SetTexture( identifier, new GRAPHIC_TEXTURE_BLOCK( text ) );
    SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetNormal ok %s\n", texture_name );
}

void GAMEPLAY_HELPER::SetTextureRepeating(GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_IDENTIFIER & identifier) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    auto mat = render->GetMaterial().GetResource< GRAPHIC_MATERIAL >();
    
    GRAPHIC_SYSTEM::SetTextureOptions( mat->GetTexture( identifier )->GetTexture(), GRAPHIC_TEXTURE_FILTERING_Linear, GRAPHIC_TEXTURE_WRAP_RepeatMirror, CORE_COLOR_Transparent );
}

void GAMEPLAY_HELPER::SetEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    render->SetEffect( *R3D_RESOURCES::GetInstance().FindResourceProxy( identifier ) );
    
    auto mat = new GRAPHIC_MATERIAL;
    
    RESOURCE_PROXY
        proxy( mat );
    
    render->SetMaterial( proxy );
}

void GAMEPLAY_HELPER::SetSecondaryEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    //TODO : create another component or entity to render this one
    
    //abort();
    /*GAMEPLAY_COMPONENT_HANDLE handle_r;
    
    handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    
    entity->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Light );
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Light );
    GAMEPLAY_COMPONENT_RENDER::PTR render1 = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    render->SetObject( render1->GetObject() );
    render->SetEffect( *R3D_RESOURCES::GetInstance().FindResourceProxy( identifier ) );
    
    auto mat = new GRAPHIC_MATERIAL;
    
    RESOURCE_PROXY
            proxy( mat );
    
    render->SetMaterial( proxy );*/
}

void GAMEPLAY_HELPER::SetShadowmapEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    static CORE_HELPERS_UNIQUE_IDENTIFIER identifier( "SHADER::ShadowMapEffect");
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    render->SetShadowmapEffect( *R3D_RESOURCES::GetInstance().FindResourceProxy( identifier ) );
}

void GAMEPLAY_HELPER::SetScript( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_FILESYSTEM_PATH & path ) {
    
    CORE_ABSTRACT_PROGRAM_LUA * program = new CORE_ABSTRACT_PROGRAM_LUA();
    
    CORE_ABSTRACT_RUNTIME_LUA * runtime = new CORE_ABSTRACT_RUNTIME_LUA;
    runtime->Initialize();
    
    CORE_ABSTRACT_PROGRAM_BINDER::GetInstance().BindRuntime<CORE_ABSTRACT_RUNTIME_LUA>( *runtime );
    
#if DEBUG
    CORE_FILESYSTEM_FILE_WATCHER * watcher =  new CORE_FILESYSTEM_FILE_WATCHER;
    
    CORE_HELPERS_CALLBACK *callback = new CORE_HELPERS_CALLBACK( &Wrapper< CORE_ABSTRACT_PROGRAM_LUA, &CORE_ABSTRACT_PROGRAM_LUA::Reload>, (void *) program );
    
    int l = (int) strlen( path.GetPath() );
    
    char * vsh_path = (char*) CORE_MEMORY_ALLOCATOR::Allocate ( l+1 );
    
    
    strncpy(vsh_path, path.GetPath(), l);
    vsh_path[l] = '\0';
    vsh_path[strlen(vsh_path) - 3 ] ='l';
    vsh_path[strlen(vsh_path) - 2 ] ='u';
    vsh_path[strlen(vsh_path) - 1 ] ='a';
    
    
    watcher->Setup( path.GetPath(), *callback );
#endif
    
    program->Load( path.GetPath(), *runtime );
    
    GAMEPLAY_COMPONENT_SCRIPT::PTR script = (GAMEPLAY_COMPONENT_SCRIPT::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Script );

    script->SetScript( program );
}

void GAMEPLAY_HELPER::AddToWorld( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    R3D_APP_PTR->GetGame()->GetScene().GetRenderableSystemTable()[1]->AddEntity( entity );
}

void GAMEPLAY_HELPER::AddToSpecialEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    R3D_APP_PTR->GetGame()->GetScene().GetRenderableSystemTable()[3]->AddEntity( entity );
}

void GAMEPLAY_HELPER::AddToWorldTransparent( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    R3D_APP_PTR->GetGame()->GetScene().GetRenderableSystemTable()[2]->AddEntity( entity );
}

void GAMEPLAY_HELPER::AddToScripts( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_SCRIPT::PTR script = (GAMEPLAY_COMPONENT_SCRIPT::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Script );
    
    if ( script != NULL ) {
        
        script->GetScript()->Execute();
        R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[3]->AddEntity( entity );
    }
}

void GAMEPLAY_HELPER::AddToAnimations( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
   
    R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[1]->AddEntity( entity );
}

void GAMEPLAY_HELPER::AddToPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity, PHYSICS_COLLISION_TYPE group, PHYSICS_COLLISION_TYPE collides_with, bool enable ) {
    
    ( ( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * ) R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[4])->AddEntity(entity, group, collides_with );
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    comp->Enable( enable );
    //comp->GetBulletRigidBody()->setCollisionFlags( btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK );
}

void GAMEPLAY_HELPER::AddToMotion( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    ( ( GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION * ) R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[0])->AddEntity( entity );
}

void GAMEPLAY_HELPER::AddStaticToPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity, PHYSICS_COLLISION_TYPE group, PHYSICS_COLLISION_TYPE collides_with ) {
    
    ((GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION *) R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[4])->AddStaticEntity( entity, group, collides_with );
}

void GAMEPLAY_HELPER::SetPhysicsSphereObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation, float mass ) {
    
    auto render = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
#if DEBUG
    assert( render != NULL && pos != NULL );
#endif
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    pos->SetPosition( position );
    
    if ( comp ) {
        
        comp->ConfigureShapeSphere( position, orientation );
        comp->SetMass( mass );
    }
}

void GAMEPLAY_HELPER::SetPhysicsBoxObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & half_extent, const CORE_MATH_QUATERNION & orientation, float mass ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto render = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
#if DEBUG
    assert( comp != NULL && render != NULL );
#endif
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    pos->SetPosition( position );
    
    comp->ConfigureShapeBox( position, half_extent, orientation );
    comp->SetMass( mass );
}

void GAMEPLAY_HELPER::SetPhysicsCylinderObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float radius, float height, const CORE_MATH_QUATERNION & orientation, float mass ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto render = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
#if DEBUG
    assert( comp != NULL && render != NULL );
#endif
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    pos->SetPosition( position );
    
    comp->ConfigureShapeCylinder(position, radius, height, orientation );
    comp->SetMass( mass );
}

void GAMEPLAY_HELPER::SetPhysicsObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto render = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
#if DEBUG
    assert( comp != NULL && render != NULL );
#endif
    
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    pos->SetPosition( position );
    auto triangle_mesh = comp->CreateBvhTriangleMesh( render->GetObject().GetResource< GRAPHIC_OBJECT >() );
    comp->BulletConfigureBvhTriangleMeshShape( position, triangle_mesh );
    comp->SetMass( mass );
}

void GAMEPLAY_HELPER::SetPhysicsGroundHeightMapObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto render = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
#if DEBUG
    assert( comp != NULL && render != NULL );
#endif
    
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR object = render->GetObject().GetResource<GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP>();
    
    comp->ConfigureHeightMap( position, object->GetXWidth(), object->GetYWidth(), (const void *)object->GetHeights(), object->GetLength(), object->GetHeightScale() );
    comp->SetMass( mass );
}

void GAMEPLAY_HELPER::SetPhysicsFlatGroundObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass, float constant ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
#if DEBUG
    assert( comp != NULL );
#endif
    
    comp->ConfigureShapePlane( position, constant );
    comp->SetMass( mass );
}

void GAMEPLAY_HELPER::InitializeCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & direction, GRAPHIC_CAMERA & camera, const CORE_MATH_VECTOR & up ) {
    
    camera.Reset( 1.0f, 1500.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), position, direction,
                 up );
}

void GAMEPLAY_HELPER::GetElevation( GAMEPLAY_COMPONENT_ENTITY::PTR entity, CORE_MATH_VECTOR & out_position, CORE_MATH_VECTOR & out_normal ) {
    
    CORE_MATH_VECTOR
        elevation;
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    auto bullet = R3D_APP_PTR->GetGame()->GetBulletSystem();
    const CORE_MATH_QUATERNION &
        q = pos->GetOrientation();
    CORE_MATH_MATRIX
        m;
    CORE_MATH_RAY_SEGMENT
        ray;
    
    q.ToMatrix( &m[0] );
    
    CORE_MATH_VECTOR orr = CORE_MATH_VECTOR( 0.0f, -10.0f, 0.0f , 0.0f) * m;
    
    ray.SetOrigin( pos->GetPosition() );
    ray.SetDestination( pos->GetPosition() + orr );
    
    if ( PHYSICS_UTILS::FindCollisionInRayFromWorld( bullet->GetDynamicsWorld(), elevation, out_normal, ray ) ) {
        
        out_position =  pos->GetPosition() - elevation;
    }
    else {
        
        out_position = CORE_MATH_VECTOR::Zero;
    }
}

void GAMEPLAY_HELPER::SetPhysicsCustomMaterialCallback( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    comp->GetBulletRigidBody()->setCollisionFlags( comp->GetBulletRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT );
}

void GAMEPLAY_HELPER::ConfigureGroundSpring( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    btCollisionShape* emptyShape = new btEmptyShape();
    
    auto pMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3( pos->GetPosition().X(), pos->GetPosition().Y(), pos->GetPosition().Z() - 0.1f)));
    
    btVector3 inertia(0, 0, 0);
    comp->GetBulletRigidBody()->getCollisionShape()->calculateLocalInertia( 0.5f, inertia );
    
    auto empty_body_object = new btRigidBody( 0.5f, pMotionState2, emptyShape, inertia );
    empty_body_object->setActivationState(DISABLE_DEACTIVATION);
    empty_body_object->setCollisionFlags(empty_body_object->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    
    auto spring_constraint = new btGeneric6DofSpring2Constraint( *comp->GetBulletRigidBody(), *empty_body_object, btTransform( btQuaternion::getIdentity(), { 0.0f, 0.0f, -0.1f} ), btTransform( btQuaternion::getIdentity(), { 0.0f, 0.0f, 0.05f } ) );
    
    spring_constraint->setLinearLowerLimit( { 0.0f, 0.0f, .15f} );
    spring_constraint->setLinearUpperLimit( { 0.0f, 0.0f, .5f} );
    
    spring_constraint->enableSpring( 1, true );
    spring_constraint->setStiffness( 1, 1.0f );
    spring_constraint->setDamping( 1, 0.0f );
    spring_constraint->setEquilibriumPoint();
    
    auto bullet = ( ( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * ) R3D_APP_PTR->GetGame()->GetScene().GetUpdatableSystemTable()[4]);
    bullet->GetDynamicsWorld()->addConstraint( spring_constraint, true );
}

void GAMEPLAY_HELPER::AddToLighting( GAMEPLAY_COMPONENT_ENTITY::PTR entity, GRAPHIC_SHADER_LIGHT * light ) {
    
    entity->GetComponentLight()->SetLight( light );
    R3D_APP_PTR->GetGame()->GetScene().GetRenderableSystemTable()[0]->AddEntity( entity );
}

void GAMEPLAY_HELPER::EnableEffectSpecial( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    R3D_APP_PTR->GetGame()->GetScene().GetRenderableSystemTable()[2]->AddEntity( entity );
}

void GAMEPLAY_HELPER::DisableEffectSpecial( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    R3D_APP_PTR->GetGame()->GetScene().GetRenderableSystemTable()[2]->RemoveEntity( entity );
}
