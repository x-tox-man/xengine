//
//  GAMEPLAY_SCENE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SYSTEM_POLYGON_FILL_MODE.h"
#include "GRAPHIC_SYSTEM.h"
#include "SERVICE_LOGGER.h"

#if GRAPHIC_RENDERER_OPENGL
    #define GRAPHIC_RENDER_PLATFORM OPENGL
    #include "GRAPHIC_RENDERER.h"
    #undef GRAPHIC_RENDER_PLATFORM
#endif

#if GRAPHIC_RENDERER_DX_9
    #define GRAPHIC_RENDER_PLATFORM DX_9
    #include "GRAPHIC_RENDERER.h"
    #undef GRAPHIC_RENDER_PLATFORM
#endif

#if GRAPHIC_RENDERER_DX_11
    #define GRAPHIC_RENDER_PLATFORM DX_11
    #include "GRAPHIC_RENDERER.h"
    #undef GRAPHIC_RENDER_PLATFORM
#endif

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GAMEPLAY_SCENE )
    
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GAMEPLAY_SCENE )

GAMEPLAY_SCENE::GAMEPLAY_SCENE() :
    UpdatableSystemTable(),
    RenderableSystemTable() {
    
}

GAMEPLAY_SCENE::~GAMEPLAY_SCENE() {

    for (int i = 0; i < UpdatableSystemTable.size(); i++ ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( UpdatableSystemTable[ i ] );
    }
    
    for (int i = 0; i < RenderableSystemTable.size(); i++ ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( RenderableSystemTable[ i ] );
    }
}

void GAMEPLAY_SCENE::InsertUpdatableSystem( GAMEPLAY_COMPONENT_SYSTEM * system ) {
    
    UpdatableSystemTable.push_back( system );
}

void GAMEPLAY_SCENE::InsertRenderableSystem( GAMEPLAY_COMPONENT_SYSTEM * system ) {
    
    RenderableSystemTable.push_back( system );
}

void GAMEPLAY_SCENE::Update( float time_step ) {
    
    for (int i = 0; i < UpdatableSystemTable.size(); i++ ) {
        
        UpdatableSystemTable[ i ]->Update( time_step );
    }
}

void GAMEPLAY_SCENE::Render() {
    
    GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_LessOrEqual, true, 0.0f, 1.0f);
    GRAPHIC_SYSTEM::EnableBackfaceCulling();
    GRAPHIC_SYSTEM::SetPolygonMode( GRAPHIC_SYSTEM_POLYGON_FILL_MODE_Full );
    
    for (int i = 0; i < RenderableSystemTable.size(); i++ ) {
        
        RenderableSystemTable[ 0 ]->Render();
    }
}
