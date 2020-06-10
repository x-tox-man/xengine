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
#include "CORE_DATA_JSON.h"

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
    // TODO:
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GAMEPLAY_SCENE )

//XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_SYSTEM )

//XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_SCENE )
//    XS_DEFINE_ClassMember( "UpdatableSystemTable", unsigned int, UpdatableSystemTable )
//    XS_DEFINE_ClassMember( "RenderableSystemTable", unsigned int, RenderableSystemTable )
//XS_END_INTERNAL_MEMORY_LAYOUT


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
        
        UpdatableSystemTable[ i ]->Update( GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEcsBasePointer(), time_step );
    }
}

void GAMEPLAY_SCENE::Render( GRAPHIC_RENDERER & renderer, int transparent_mask ) {
    
    for ( size_t i = 0; i < RenderableSystemTable.size(); i++ ) {
        
        if ( transparent_mask == GAMEPLAY_COMPONENT_SYSTEM_MASK_All || RenderableSystemTable[ i ]->GetMask() & transparent_mask ) {
            
            RenderableSystemTable[ i ]->Render( GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEcsBasePointer(), renderer );
        }
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
    
    //Serialize Entities
    GAMEPLAY_COMPONENT_MANAGER::GetInstance().SaveToStream( stream );
    
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
    file.Close();
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
        
        CORE_RUNTIME_Abort();
    }

    file.Close();
    
    stream.Open();
    
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
