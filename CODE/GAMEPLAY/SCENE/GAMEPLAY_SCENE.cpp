//
//  GAMEPLAY_SCENE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SYSTEM_POLYGON_FILL_MODE.h"
#include "GRAPHIC_SYSTEM.h"
#include "SERVICE_LOGGER.h"
#include "GAMEPLAY_COMPONENT_ACTION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_SCRIPT.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

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
    //TODO
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GAMEPLAY_SCENE )


GAMEPLAY_SCENE::GAMEPLAY_SCENE() :
    UpdatableSystemTable(),
    RenderableSystemTable() {
    
}

GAMEPLAY_SCENE::~GAMEPLAY_SCENE() {
    
    Clear();

    for ( size_t i = 0; i < UpdatableSystemTable.size(); i++ ) {
        
        UpdatableSystemTable[ i ]->Finalize();
        CORE_MEMORY_ObjectSafeDeallocation( UpdatableSystemTable[ i ] );
    }
    
    for ( size_t i = 0; i < RenderableSystemTable.size(); i++ ) {
        
        RenderableSystemTable[ i ]->Finalize();
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
    
    for ( size_t i = 0; i < UpdatableSystemTable.size(); i++ ) {
        
        UpdatableSystemTable[ i ]->Update( time_step );
    }
}

void GAMEPLAY_SCENE::Render( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_SYSTEM::EnableDepthTest( GRAPHIC_SYSTEM_COMPARE_OPERATION_LessOrEqual, true );
    GRAPHIC_SYSTEM::EnableBackfaceCulling();
    GRAPHIC_SYSTEM::SetPolygonMode( GRAPHIC_SYSTEM_POLYGON_FILL_MODE_Full );
    
    for ( size_t i = 0; i < RenderableSystemTable.size(); i++ ) {
        
        RenderableSystemTable[ 0 ]->Render( renderer );
    }
}

void GAMEPLAY_SCENE::SaveTo( const CORE_FILESYSTEM_PATH & path ) {
    
    std::vector< GAMEPLAY_COMPONENT_SYSTEM * >::iterator
        update_table_iterator = UpdatableSystemTable.begin();
    std::vector< GAMEPLAY_COMPONENT_SYSTEM * >::iterator
        render_table_iterator = RenderableSystemTable.begin();
    
    CORE_DATA_STREAM
        stream;
    CORE_FILESYSTEM_FILE
        file( path );
    
    stream.Open();
    
    //Serialize Components
    GAMEPLAY_COMPONENT_RENDER::SaveToStream( stream );
    GAMEPLAY_COMPONENT_POSITION::SaveToStream( stream );
    GAMEPLAY_COMPONENT_SCRIPT::SaveToStream( stream );
    GAMEPLAY_COMPONENT_PHYSICS::SaveToStream( stream );
    GAMEPLAY_COMPONENT_ACTION::SaveToStream( stream );
    
    //Serialize Entities
    /*GAMEPLAY_COMPONENT_MANAGER::GetInstance().SaveToStream( stream );
    
    //Serialize Systems
    while (update_table_iterator != UpdatableSystemTable.end() ) {
        
        (*update_table_iterator)->SaveToStream( stream );
        
        update_table_iterator++;
    }
    
    while (render_table_iterator != RenderableSystemTable.end() ) {
        
        (*render_table_iterator)->SaveToStream( stream );
        
        render_table_iterator++;
    }
    
    file.OpenInput();
    file.InputBytes( stream.GetMemoryBuffer(), stream.GetOffset() );
    file.Close();*/
}

void GAMEPLAY_SCENE::LoadFrom( const CORE_FILESYSTEM_PATH & path ) {
    
    std::vector< GAMEPLAY_COMPONENT_SYSTEM * >::iterator
        update_table_iterator = UpdatableSystemTable.begin();
    std::vector< GAMEPLAY_COMPONENT_SYSTEM * >::iterator
        render_table_iterator = RenderableSystemTable.begin();
    
    CORE_FILESYSTEM_FILE
        file( path );
    
    file.OpenOutput();
    
    CORE_DATA_STREAM
        stream( file.GetSize() );
    
    int bytes_read = file.OutputBytes(stream.GetMemoryBuffer(), file.GetSize() );
    
    if ( bytes_read != file.GetSize() ) {
        
        file.Close();
        
        abort();
    }

    file.Close();
    
    
    stream.Open();
    
    //Serialize Components
    GAMEPLAY_COMPONENT_RENDER::LoadFromStream( stream );
    GAMEPLAY_COMPONENT_POSITION::LoadFromStream( stream );
    GAMEPLAY_COMPONENT_SCRIPT::LoadFromStream( stream );
    GAMEPLAY_COMPONENT_PHYSICS::LoadFromStream( stream );
    GAMEPLAY_COMPONENT_ACTION::LoadFromStream( stream );
    
    //Serialize Entities
    GAMEPLAY_COMPONENT_MANAGER::GetInstance().LoadFromStream( stream );
    
    //Serialize Systems
    while (update_table_iterator != UpdatableSystemTable.end() ) {
        
        (*update_table_iterator)->LoadFromStream( stream );
        
        update_table_iterator++;
    }
    
    while (render_table_iterator != RenderableSystemTable.end() ) {
        
        (*render_table_iterator)->LoadFromStream( stream );
        
        render_table_iterator++;
    }
}

void GAMEPLAY_SCENE::Clear() {
    
    std::vector< GAMEPLAY_COMPONENT_SYSTEM * >::iterator
        update_table_iterator = UpdatableSystemTable.begin();
    std::vector< GAMEPLAY_COMPONENT_SYSTEM * >::iterator
        render_table_iterator = RenderableSystemTable.begin();
    
    GAMEPLAY_COMPONENT_ACTION::Clear();
    GAMEPLAY_COMPONENT_SCRIPT::Clear();
    GAMEPLAY_COMPONENT_POSITION::Clear();
    GAMEPLAY_COMPONENT_RENDER::Clear();
    GAMEPLAY_COMPONENT_PHYSICS::Clear();
    
    GAMEPLAY_COMPONENT_MANAGER::GetInstance().Clear();
    
    while (update_table_iterator != UpdatableSystemTable.end() ) {
        
        (*update_table_iterator)->Clear();
        
        update_table_iterator++;
    }
    
    while (render_table_iterator != RenderableSystemTable.end() ) {
        
        (*render_table_iterator)->Clear();
        
        render_table_iterator++;
    }
}
