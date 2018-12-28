//
//  MENU_SCENE.cpp
//  Run3d
//
//  Created by Christophe Bernard on 19/03/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "MENU_SCENE.h"
#include "GAMEPLAY_HELPER.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "GRAPHICS_STEAM_CLOUD.h"

MENU_SCENE::MENU_SCENE() {
    
}

void MENU_SCENE::Initialize() {
    
    GRAPHICS_STEAM_CLOUD
        cloud;
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_ENTITY >();
    GAMEPLAY_HELPER::CreateComponent_PositionRender( entity );
    
    GAMEPLAY_HELPER::Set3DObject(entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "base_hub" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture( entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( entity, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::AddToWorld( entity );
    
    auto ship = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_ENTITY >();
    GAMEPLAY_HELPER::CreateComponent_PositionRender( ship );
    
    GAMEPLAY_HELPER::Set3DObject(ship, CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship" ) );
    //ship->GetComponentRender()->GetObject().GetResource< GRAPHIC_OBJECT >()->SetTesselation( true );
    GAMEPLAY_HELPER::Scale3dObject( ship, 20.0f );
    GAMEPLAY_HELPER::SetEffect( ship, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture( ship, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( ship, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    //GAMEPLAY_HELPER::SetDisplacement( ship, "spaceship1_displacement", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-displacement", "png", "TEXTURES" ) );
    
    GAMEPLAY_COMPONENT_RENDER::PTR render = (GAMEPLAY_COMPONENT_RENDER::PTR) ship->GetComponent( GAMEPLAY_COMPONENT_TYPE_Render );
    GAMEPLAY_COMPONENT_POSITION::PTR pos = (GAMEPLAY_COMPONENT_POSITION::PTR) ship->GetComponent(GAMEPLAY_COMPONENT_TYPE_Position );
    CORE_MATH_QUATERNION q;
    q.RotateZ( 360.0f );
    
    pos->SetSpin( q );
    
    GAMEPLAY_HELPER::AddToWorld( ship );
    GAMEPLAY_HELPER::AddToMotion( ship );
    
    //Background
    auto background = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_ENTITY >();
    GAMEPLAY_HELPER::CreateComponent_PositionRender( background );
    GAMEPLAY_HELPER::Set3DPlane( background, CORE_MATH_VECTOR( 100.0f, 100.0f ) );
    
    GAMEPLAY_HELPER::AddToWorld( background );
    CORE_MATH_QUATERNION q1;
    q1.RotateX( M_PI_2 );
    GAMEPLAY_COMPONENT_POSITION::PTR pos2 = (GAMEPLAY_COMPONENT_POSITION::PTR) background->GetComponent(GAMEPLAY_COMPONENT_TYPE_Position );
    q1.Normalize();
    background->SetPosition( CORE_MATH_VECTOR( 0.0f, 20.0f, .0f, 0.0f ) );
    background->SetOrientation( q1 );
    
    GAMEPLAY_HELPER::SetEffect( background, CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SkyEffect" ) );
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "space_diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "high-resolution-space-1", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetTexture( background, "space_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "high-resolution-space-1", "png", "TEXTURES" ) );
    
    cloud.Initialize();
}
