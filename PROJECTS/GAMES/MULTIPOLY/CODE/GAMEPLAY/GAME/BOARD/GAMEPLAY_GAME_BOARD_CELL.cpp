//
//  GAMEPLAY_GAME_BOARD_CELL.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GLOBAL_RESOURCES.h"

GAMEPLAY_GAME_BOARD_CELL::GAMEPLAY_GAME_BOARD_CELL() :
    GAMEPLAY_COMPONENT_ENTITY(),
    ThisCellPlayerTable() {
    
}

GAMEPLAY_GAME_BOARD_CELL::~GAMEPLAY_GAME_BOARD_CELL() {
    
}

void GAMEPLAY_GAME_BOARD_CELL::Initialize(
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_VECTOR & size,
    const CORE_MATH_QUATERNION & orientation,
    GAMEPLAY_SCENE * scene,
    GRAPHIC_TEXTURE_BLOCK * block,
    bool is_corner ) {
    
    auto shader = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("CellShader"), CORE_FILESYSTEM_PATH::FindFilePath("UIShaderTextured", "vsh", "OPENGL2"));
    
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = GLOBAL_RESOURCES::CreateUIPlanShape( shader );
    shader->Initialize( shape->GetShaderBindParameter() );
    shape->SetTextureBlock( block );
    
    CreateThisComponent(
        shape,//is_corner ? CORE_FILESYSTEM_PATH::FindFilePath("CellCorner", "smx", "MODELS") : CORE_FILESYSTEM_PATH::FindFilePath("CellBase", "smx", "MODELS"),
        &shader->GetProgram(),
        position,
        orientation,
        size,
        scene);
}

GAMEPLAY_COMPONENT_ENTITY * GAMEPLAY_GAME_BOARD_CELL::CreateThisComponent(
    //const CORE_FILESYSTEM_PATH & path,
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR object,
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_QUATERNION & orientation,
    const CORE_MATH_VECTOR & size,
    GAMEPLAY_SCENE * scene ) {
    
    /*GRAPHIC_OBJECT * object = GRAPHIC_OBJECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("CellID"), path);
    
    for ( int i = 0; i < object->GetMeshTable().size(); i++ ) {
        
        object->GetMeshTable()[ i ]->CreateBuffers();
    }
    
    object->GetShaderTable().resize( 1 );
    object->GetShaderTable()[ 0 ] = program;*/
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION * ) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position );
    
    SetCompononent( pos, GAMEPLAY_COMPONENT_TYPE_Position );
    SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject(  object );
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( this );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    SetPosition( position );
    pos->SetOrientation( orientation );

    return this;
}
