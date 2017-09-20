//
//  GAMEPLAY_HELPER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 16/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "GAMEPLAY_HELPER.h"
#include "GAMEPLAY_COMPONENT_HANDLE.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_SCRIPT.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "R3D_RESOURCES.h"
#include "RUN3D_APPLICATION.h"
#include "CORE_FILESYSTEM_FILE_WATCHER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "RESOURCE_IMAGE.h"

void GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysicsScriptAnimation( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r, handle_sc, handle_an, handle_ph;
    
    handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    handle_p.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->InitializeObservable();
    handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    handle_an.Create< GAMEPLAY_COMPONENT_ANIMATION >( GAMEPLAY_COMPONENT_TYPE_Animation );
    handle_sc.Create< GAMEPLAY_COMPONENT_SCRIPT >( GAMEPLAY_COMPONENT_TYPE_Script );
    handle_ph.Create< GAMEPLAY_COMPONENT_PHYSICS >( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    entity->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
    entity->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
    entity->SetCompononent( handle_an, GAMEPLAY_COMPONENT_TYPE_Animation );
    entity->SetCompononent( handle_sc, GAMEPLAY_COMPONENT_TYPE_Script );
    entity->SetCompononent( handle_ph, GAMEPLAY_COMPONENT_TYPE_Physics );
}

void GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r, handle_ph;
    
    handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    handle_p.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->InitializeObservable();
    handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    handle_ph.Create< GAMEPLAY_COMPONENT_PHYSICS >( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    entity->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
    entity->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
    entity->SetCompononent( handle_ph, GAMEPLAY_COMPONENT_TYPE_Physics );
}

void GAMEPLAY_HELPER::CreateComponent_PositionRenderScriptAnimation( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r, handle_sc, handle_an;
    
    handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    handle_p.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->InitializeObservable();
    handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    handle_an.Create< GAMEPLAY_COMPONENT_ANIMATION >( GAMEPLAY_COMPONENT_TYPE_Animation );
    handle_sc.Create< GAMEPLAY_COMPONENT_SCRIPT >( GAMEPLAY_COMPONENT_TYPE_Script );
    
    entity->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
    entity->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
    entity->SetCompononent( handle_an, GAMEPLAY_COMPONENT_TYPE_Animation );
    entity->SetCompononent( handle_sc, GAMEPLAY_COMPONENT_TYPE_Script );
}

void GAMEPLAY_HELPER::CreateComponent_PositionRenderAnimation( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r, handle_an;
    
    handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    handle_p.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->InitializeObservable();
    handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    handle_an.Create< GAMEPLAY_COMPONENT_ANIMATION >( GAMEPLAY_COMPONENT_TYPE_Animation );
    
    entity->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
    entity->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
    entity->SetCompononent( handle_an, GAMEPLAY_COMPONENT_TYPE_Animation );
}

void GAMEPLAY_HELPER::CreateComponent_PositionRenderScript( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r, handle_sc;
    
    handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    handle_p.GetComponent< GAMEPLAY_COMPONENT_POSITION >()->InitializeObservable();
    handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    handle_sc.Create< GAMEPLAY_COMPONENT_SCRIPT >( GAMEPLAY_COMPONENT_TYPE_Script );
    
    entity->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
    entity->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
    entity->SetCompononent( handle_sc, GAMEPLAY_COMPONENT_TYPE_Script );
}

void GAMEPLAY_HELPER::CreateComponent_PositionRender( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_COMPONENT_HANDLE handle_p, handle_r;
    
    handle_p.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    handle_r.Create< GAMEPLAY_COMPONENT_RENDER >( GAMEPLAY_COMPONENT_TYPE_Render );
    
    entity->SetCompononent( handle_p, GAMEPLAY_COMPONENT_TYPE_Position );
    entity->SetCompononent( handle_r, GAMEPLAY_COMPONENT_TYPE_Render );
}


void GAMEPLAY_HELPER::Set3DObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    render->SetObject( *R3D_RESOURCES::GetInstance().FindResourceProxy( identifier ) );
}

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR GAMEPLAY_HELPER::Set3DHeighFieldObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    RESOURCE_IMAGE * height_map = (RESOURCE_IMAGE*) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath(identifier.GetIdentifier(), "png", "MAP" ) );
    
    float * heights = (float * ) height_map->GetImageRawData();
    
    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR object = new GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP( heights, height_map->GetImageInfo().Width, height_map->GetImageInfo().Height, 2.0f );
    object->SetHeightScale( 0.1f );
    object->InitializeShape();
    
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    render->GetObject().SetResource( object );

    return object;
}

void GAMEPLAY_HELPER::SetTexture( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const char * texture_name, const CORE_FILESYSTEM_PATH & path, const CORE_HELPERS_IDENTIFIER & identifier  ) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    auto mat = render->GetEffect().GetResource< GRAPHIC_SHADER_EFFECT >()->GetMaterial();
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( texture_name ), path );
    
    mat->SetTexture( identifier, new GRAPHIC_TEXTURE_BLOCK( text ) );
}
void GAMEPLAY_HELPER::SetEffect( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    
    render->SetEffect( *R3D_RESOURCES::GetInstance().FindResourceProxy( identifier ) );
    
    auto mat = new GRAPHIC_MATERIAL;
    
    render->GetEffect().GetResource< GRAPHIC_SHADER_EFFECT >()->SetMaterial( mat );
}

void GAMEPLAY_HELPER::SetScript( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_FILESYSTEM_PATH & path ) {
    
    CORE_ABSTRACT_PROGRAM_LUA * program = new CORE_ABSTRACT_PROGRAM_LUA();
    CORE_ABSTRACT_RUNTIME_LUA * runtime = (CORE_ABSTRACT_RUNTIME_LUA *) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[ CORE_ABSTRACT_PROGRAM_RUNTIME_Lua ];
    
#if DEBUG
    CORE_FILESYSTEM_FILE_WATCHER * watcher =  new CORE_FILESYSTEM_FILE_WATCHER;
    
    CORE_HELPERS_CALLBACK *callback = new CORE_HELPERS_CALLBACK( &Wrapper< CORE_ABSTRACT_PROGRAM_LUA, &CORE_ABSTRACT_PROGRAM_LUA::Reload>, (void *) program );
    
    int l = (int) strlen( path.GetPath() );
    
    char * vsh_path = (char*) CORE_MEMORY_ALLOCATOR::Allocate ( l+1 );
    
    
    strncpy(vsh_path, path.GetPath(), l);
    vsh_path[l] = '\0';
    vsh_path[strlen(vsh_path) - 3 ] ='f';
    vsh_path[strlen(vsh_path) - 2 ] ='s';
    vsh_path[strlen(vsh_path) - 1 ] ='h';
    
    
    watcher->Setup( path.GetPath(), *callback );
#endif
    
    program->Load( path.GetPath(), *runtime );
    program->Execute();
    
    GAMEPLAY_COMPONENT_SCRIPT::PTR script = (GAMEPLAY_COMPONENT_SCRIPT::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Script );

    if ( script == NULL ) {
        
        GAMEPLAY_COMPONENT_HANDLE handle;
        
        handle.Create< GAMEPLAY_COMPONENT_SCRIPT >( GAMEPLAY_COMPONENT_TYPE_Script );
        
        entity->SetCompononent(handle, GAMEPLAY_COMPONENT_TYPE_Script );
    }

    script->SetScript( program );
}

void GAMEPLAY_HELPER::AddToWorld( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    R3D_APP_PTR->GetGame().GetScene().GetRenderableSystemTable()[0]->AddEntity( entity->GetHandle(), entity );
}

void GAMEPLAY_HELPER::AddToScripts( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    R3D_APP_PTR->GetGame().GetScene().GetUpdatableSystemTable()[3]->AddEntity(entity->GetHandle(), entity );
}

void GAMEPLAY_HELPER::AddToAnimations( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
   
    R3D_APP_PTR->GetGame().GetScene().GetUpdatableSystemTable()[1]->AddEntity(entity->GetHandle(), entity );
}

void GAMEPLAY_HELPER::AddToPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    R3D_APP_PTR->GetGame().GetScene().GetUpdatableSystemTable()[4]->AddEntity(entity->GetHandle(), entity );
}

void GAMEPLAY_HELPER::AddStaticToPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    ((GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION *) R3D_APP_PTR->GetGame().GetScene().GetUpdatableSystemTable()[4])->AddStaticEntity(entity->GetHandle(), entity );
}

void GAMEPLAY_HELPER::SetPosition( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position ) {
    
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    pos->SetPosition( position );
}

void GAMEPLAY_HELPER::SetOrientation( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_QUATERNION & orientation ) {
    
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    pos->SetOrientation( orientation );
    comp->SetOrientation( orientation );
}

void GAMEPLAY_HELPER::SetPhysicsSphereObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation, float mass ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto render = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    pos->SetPosition( position );
    
    comp->ConfigureShapeSphere( position, orientation );
    comp->SetMass( mass );
}

void GAMEPLAY_HELPER::SetPhysicsObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto render = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    pos->SetPosition( position );
    
    comp->BulletConfigureBvhTriangleMeshShape( position, render->GetObject().GetResource< GRAPHIC_OBJECT >() );
    comp->SetMass( mass );
}

void GAMEPLAY_HELPER::SetPhysicsGroundHeightMapObject( GAMEPLAY_COMPONENT_ENTITY::PTR entity, const CORE_MATH_VECTOR & position, float mass ) {
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto render = (GAMEPLAY_COMPONENT_RENDER *) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    auto pos = ( GAMEPLAY_COMPONENT_POSITION::PTR) entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP::PTR object = render->GetObject().GetResource<GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP>();
    
    comp->ConfigureHeightMap( position, object->GetXWidth(), object->GetYWidth(), (const void *)object->GetHeights(), object->GetLength(), object->GetHeightScale() );
    comp->SetMass( mass );
}

void GAMEPLAY_HELPER::InitializeCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation, GRAPHIC_CAMERA & camera ) {
    
    camera.Reset( 1.0f, 10000.0f, R3D_APP_PTR->GetApplicationWindow().GetWidth(), R3D_APP_PTR->GetApplicationWindow().GetHeight(), position, orientation );
}
