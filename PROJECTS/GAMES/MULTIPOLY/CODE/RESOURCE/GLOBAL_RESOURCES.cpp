//
//  RESOURCE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GLOBAL_RESOURCES.h"
#include "RESOURCE_IMAGE.h"
#include "GRAPHIC_FONT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_ACTION.h"

GLOBAL_RESOURCES::GLOBAL_RESOURCES() :
    FrameRenderStyle( NULL ),
    TexturedPlanObject( NULL ) {
        
}

GLOBAL_RESOURCES::~GLOBAL_RESOURCES() {
}

void GLOBAL_RESOURCES::Initialize() {
    
    DirectionalLight = new GRAPHIC_SHADER_LIGHT;
    
    CORE_MATH_VECTOR diffuse(1.0f, 1.0f, 1.0f, 1.0f);
    CORE_MATH_VECTOR direction(0.0f, -1.0f, 0.0f, 1.0f);
    
    DirectionalLight->InitializeDirectional( diffuse, direction, 0.5f, 0.5f);
    
    CORE_MATH_VECTOR diffuse_1(0.9f, 0.0f, 0.0f, 1.0f);
    CORE_MATH_VECTOR diffuse_2(0.0f, 0.0f, 0.9f, 1.0f);
    
    CORE_MATH_VECTOR direction_1(0.0f, 1.0f, 0.0f, 0.0f);
    CORE_MATH_VECTOR direction_2(0.0f, -1.0f, 0.0f, 0.0f);
    
    CORE_MATH_VECTOR point1_position(-10.0f, 0.0f, 0.0f, 1.0f);
    CORE_MATH_VECTOR point2_position(10.0f, 0.0f, 0.0f, 1.0f);
    
    PointLightOne = new GRAPHIC_SHADER_LIGHT;
    PointLightOne->InitializePoint(diffuse_1, point1_position, 0.001f, 0.01f, 0.5f, 1.0f, 1.0f);
    
    PointLightTwo = new GRAPHIC_SHADER_LIGHT;
    PointLightTwo->InitializePoint(diffuse_2, point2_position, 0.001f, 0.01f, 0.5f, 1.0f, 1.0f);
    
    SpotLightOne = new GRAPHIC_SHADER_LIGHT;
    SpotLightOne->InitializeSpot(diffuse_1, point1_position, direction_1, 0.1f, 0.2f, 0.4f, 0.001f, 1.0f, 1.0f );
    
    SpotLightTwo = new GRAPHIC_SHADER_LIGHT;
    SpotLightTwo->InitializeSpot(diffuse_2, point2_position, direction_2, 0.1f, 0.2f, 0.9f, 0.1f, 1.0f, 1.0f );
    
    GRAPHIC_FONT_MANAGER::GetInstance().LoadFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "arial_black_12" ), CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "fxb", "FONTS/" ), CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12" , "png", "FONTS/" ) );
    GRAPHIC_SHADER_EFFECT::PTR line_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::LineShader"), CORE_FILESYSTEM_PATH::FindFilePath( "LineShader" , "vsh", "OPENGL2" ) );
    
    
    HouseObject = GRAPHIC_OBJECT::LoadResourceForPath( "HouseObject", CORE_FILESYSTEM_PATH::FindFilePath( "untitled", "smx", "MODELS" ) );
    
    for ( int i = 0; i < HouseObject->GetMeshTable().size(); i++ ) {
        
        HouseObject->GetMeshTable()[ i ]->CreateBuffers();
    }
    
    Line = new GRAPHIC_OBJECT_SHAPE_LINE;
    line_shader_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormal );
    
    Line->InitializeShape( &line_shader_effect->GetProgram() );
    
    GRAPHIC_SHADER_EFFECT::PTR
    ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) ),
    ui_colored_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderColored"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderColored" , "vsh", "OPENGL2" ) );
    
    ui_textured_shader_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    ui_colored_shader_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormal );
    
    auto frame_tb = new GRAPHIC_TEXTURE_BLOCK;
    
    frame_tb->SetTexture( CreateTextureFromImagePath("frameBorder") );
    frame_tb->Initialize();
    
    auto plan_color = new GRAPHIC_OBJECT_SHAPE_PLAN;
    
    plan_color->InitializeShape( &ui_colored_shader_effect->GetProgram() );
    
    FrameRenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    
    FrameRenderStyle->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.5f ) );
    FrameRenderStyle->SetDecoratingShape( CreateFrameBorder( 11.0f / 400.0f, 11.0f / 200.0f, ui_textured_shader_effect) );
    FrameRenderStyle->SetDecoratingTextureBlock( frame_tb );
    FrameRenderStyle->SetShape( plan_color );
    
    CellRenderStyle= new GRAPHIC_UI_RENDER_STYLE;
    
    CellRenderStyle->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.5f ) );
    CellRenderStyle->SetDecoratingShape( CreateFrameBorder( 11.0f / 500.0f, 11.0f / 32.0f, ui_textured_shader_effect ) );
    CellRenderStyle->SetDecoratingTextureBlock( frame_tb );
    CellRenderStyle->SetShape( plan_color );
    
    
    PageFrameRenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    
    PageFrameRenderStyle->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.5f ) );
    PageFrameRenderStyle->SetDecoratingShape( CreateFrameBorder( 11.0f / 600.0f, 11.0f / 300.0f, ui_textured_shader_effect ) );
    PageFrameRenderStyle->SetDecoratingTextureBlock( frame_tb );
    PageFrameRenderStyle->SetShape( plan_color );
    
    TexturedPlanObject = CreateUIPlanShape( ui_textured_shader_effect );
}

void GLOBAL_RESOURCES::Finalize() {
 
    CORE_MEMORY_ObjectSafeDeallocation( DirectionalLight );
    CORE_MEMORY_ObjectSafeDeallocation( PointLightTwo );
    CORE_MEMORY_ObjectSafeDeallocation( SpotLightOne );
    CORE_MEMORY_ObjectSafeDeallocation( SpotLightTwo );
    CORE_MEMORY_ObjectSafeDeallocation( HouseObject );
    
    CORE_MEMORY_ObjectSafeDeallocation( Line );
    
    CORE_MEMORY_ObjectSafeDeallocation( FrameRenderStyle );
    CORE_MEMORY_ObjectSafeDeallocation( PageFrameRenderStyle );
    CORE_MEMORY_ObjectSafeDeallocation( CellRenderStyle );
}

GRAPHIC_TEXTURE * GLOBAL_RESOURCES::CreateTextureFromImagePath(const char * image_path) {
    
    auto image = RESOURCE_IMAGE::LoadResourceForPath( image_path, CORE_FILESYSTEM_PATH::FindFilePath( image_path, "png", "TEXTURES" ) );
    
    return image->CreateTextureObject( false );
}

GRAPHIC_TEXTURE_BLOCK * GLOBAL_RESOURCES::CreateTextureBlockFromImagePath(const char * image_path) {
    GRAPHIC_TEXTURE_BLOCK * tb = new GRAPHIC_TEXTURE_BLOCK();
    
    tb->SetTexture(CreateTextureFromImagePath( image_path ) );
    
    return tb;
}

GRAPHIC_OBJECT_SHAPE_PLAN * GLOBAL_RESOURCES::CreateUIPlanShape( GRAPHIC_SHADER_EFFECT * effect ) {

    GRAPHIC_OBJECT_SHAPE_PLAN::PTR shape = new GRAPHIC_OBJECT_SHAPE_PLAN();
    shape->InitializeShape( &effect->GetProgram() );
    
    return shape;
}

GRAPHIC_OBJECT_SHAPE_FRAME * GLOBAL_RESOURCES::CreateFrameBorder( float height, float width, GRAPHIC_SHADER_EFFECT::PTR shader ) {
    
    auto frame = new GRAPHIC_OBJECT_SHAPE_FRAME;
    
    frame->SetBorderSize( height, width);
    frame->InitializeShape( &shader->GetProgram() );
    
    return frame;
}

GAMEPLAY_COMPONENT_ENTITY * GLOBAL_RESOURCES::CreatePlanComponent(
    GAMEPLAY_COMPONENT_ENTITY * in_component,
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR object,
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_QUATERNION & orientation,
    const CORE_MATH_VECTOR & size,
    GAMEPLAY_SCENE * scene,
    const CORE_HELPERS_CALLBACK_1<GAMEPLAY_COMPONENT_ENTITY *> & callback,
    bool picking ) {
    
    /*GRAPHIC_OBJECT * object = GRAPHIC_OBJECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER("CellID"), path);
     
     for ( int i = 0; i < object->GetMeshTable().size(); i++ ) {
     
     object->GetMeshTable()[ i ]->CreateBuffers();
     }
     
     object->GetShaderTable().resize( 1 );
     object->GetShaderTable()[ 0 ] = program;*/
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION * ) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position );
    
    in_component->SetCompononent( pos, GAMEPLAY_COMPONENT_TYPE_Position );
    in_component->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    
    auto action = (GAMEPLAY_COMPONENT_ACTION * ) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render );
    in_component->SetCompononent( action, GAMEPLAY_COMPONENT_TYPE_Action );
    
    action->SetActionCallback( callback );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) in_component->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject(  object );
    ( ( GAMEPLAY_COMPONENT_RENDER *) in_component->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetScaleFactor(size.X());
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( in_component );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    if ( picking ) {
        
        GAMEPLAY_COMPONENT_SYSTEM_PICKING * picking_system = ( GAMEPLAY_COMPONENT_SYSTEM_PICKING * ) scene->GetUpdatableSystemTable()[2];
        
        in_component->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Physics ), GAMEPLAY_COMPONENT_TYPE_Physics );
    
        picking_system->AddEntity( in_component );
    }
    
    
    in_component->SetPosition( position );
    pos->SetOrientation( orientation );
    
    return in_component;
}

GAMEPLAY_COMPONENT_ENTITY * GLOBAL_RESOURCES::CreateOtherObjectComponent(
    GAMEPLAY_COMPONENT_ENTITY * in_component,
    GRAPHIC_OBJECT::PTR object,
    GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_QUATERNION & orientation,
    const CORE_MATH_VECTOR & size,
    GAMEPLAY_SCENE * scene ) {
    
    object->GetShaderTable().resize( 1 );
    object->GetShaderTable()[ 0 ] = program;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION * ) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position );
    
    in_component->SetCompononent( pos, GAMEPLAY_COMPONENT_TYPE_Position );
    in_component->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Render ), GAMEPLAY_COMPONENT_TYPE_Render );
    
    ( ( GAMEPLAY_COMPONENT_RENDER *) in_component->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetObject(  object );
    ( ( GAMEPLAY_COMPONENT_RENDER *) in_component->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetProgram(  program );
    ( ( GAMEPLAY_COMPONENT_RENDER *) in_component->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render))->SetScaleFactor(size.X());
    
    GAMEPLAY_COMPONENT_SYSTEM_RENDERER * render_system = ( GAMEPLAY_COMPONENT_SYSTEM_RENDERER * ) scene->GetRenderableSystemTable()[0];
    
    render_system->AddEntity( in_component );
    render_system->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    in_component->SetPosition( position );
    pos->SetOrientation( orientation );
    
    return in_component;
}

GRAPHIC_UI_RENDER_STYLE * GLOBAL_RESOURCES::CreateRenderStyleFromTextureName( const char * texture_name ) {
    
    auto rs = new GRAPHIC_UI_RENDER_STYLE;
    rs->SetColor( CORE_MATH_VECTOR( 0.0f, 0.0f, 0.0f, 0.5f ) );
    rs->SetShape( GetInstance().TexturedPlanObject );
    rs->SetTextureBlock(CreateTextureBlockFromImagePath(texture_name));
    
    return rs;
}
