//
//  GRAPHIC_OBJECT_RESOURCE_LOADER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 13/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH_LOADER_COLLADA.h"
#include "CORE_DATA_STREAM.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_MESH_ANIMATION_COLLECTION.h"

GRAPHIC_OBJECT_RESOURCE_LOADER::GRAPHIC_OBJECT_RESOURCE_LOADER() :
    RESOURCE_LOADER() {
    
};

GRAPHIC_OBJECT_RESOURCE_LOADER::~GRAPHIC_OBJECT_RESOURCE_LOADER() {
    
}

GRAPHIC_OBJECT * GRAPHIC_OBJECT_RESOURCE_LOADER::Load( const CORE_FILESYSTEM_PATH & path, int resource_load_flag, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    CORE_FILESYSTEM_FILE
        file( path );
    GRAPHIC_OBJECT
        * object = new GRAPHIC_OBJECT;
    
    if ( !file.OpenOutput() ) {
        
        return NULL;
    }
    
    int file_size = file.GetSize();
    
    CORE_DATA_STREAM stream( file_size );
    
    int bytes_read = file.OutputBytes(stream.GetMemoryBuffer(), file_size );
    
    if ( bytes_read != file_size ) {
        
        file.Close();
        
        CORE_MEMORY_ObjectSafeDeallocation( object );
        
        return NULL;
    }
    
    file.Close();
    
    stream.Open();
    stream.ResetOffset();
    
    XS_CLASS_SERIALIZER< GRAPHIC_OBJECT, CORE_DATA_STREAM >::Serialize<std::false_type>( "object", *object, stream );
    
    stream.Close();
    
    for ( size_t i = 0; i < object->GetMeshTable().size(); i++ ) {
        
        object->GetMeshTable()[ i ]->CreateBuffers();
    }
    
    return object;
}

GRAPHIC_OBJECT * GRAPHIC_OBJECT_RESOURCE_LOADER::Load( CORE_DATA_STREAM & stream, int resource_load_flag, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_OBJECT
        * object = new GRAPHIC_OBJECT;
    
    XS_CLASS_SERIALIZER< GRAPHIC_OBJECT, CORE_DATA_STREAM >::Serialize<std::false_type>( "object", *object, stream );
    
    for ( size_t i = 0; i < object->GetMeshTable().size(); i++ ) {
        
        object->GetMeshTable()[ i ]->CreateBuffers();
    }
    
    return object;
}

void GRAPHIC_OBJECT_RESOURCE_LOADER::ReloadResource( GRAPHIC_OBJECT * resource_to_reload ) {
    
}

#if ASSET_COMPILER

void GRAPHIC_OBJECT_RESOURCE_LOADER::CompileResource( const CORE_FILESYSTEM_PATH & source_path, const CORE_FILESYSTEM_PATH & destination_path ) {
    
    GRAPHIC_OBJECT
        * object;
    CORE_DATA_STREAM
        stream;
    CORE_FILESYSTEM_FILE
        file( destination_path );
    
    object = LoadObject( source_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< GRAPHIC_OBJECT, CORE_DATA_STREAM >::Serialize< std::true_type >( "asset", *object, stream );
    
    stream.Close();
    
    if ( !file.OpenInput() ) {
        
        CORE_RUNTIME_Abort();
    }
    
    int bytes_written = file.InputBytes( stream.GetMemoryBuffer(), stream.GetOffset() );
    
    file.Close();
    
    if ( bytes_written != stream.GetOffset() ) {
        
        CORE_RUNTIME_Abort();
    }
        
    // HACK : this will allow iphone to find object on correct path
    /*if ( object->GetAnimationTable().size() ) {
        
        GRAPHIC_MESH_ANIMATION * animation = object->GetAnimationTable()[ 0 ];
        
        char new_path[128];
        
        strcpy(new_path, destination_path.GetPath() );
        
        char * last_dot = strrchr ( new_path, '.' );
        ++last_dot;
        *last_dot = '\0';
        
        strcat(new_path, animation->GetName().c_str() );
        strcat(new_path, ".abx" );
        
        CORE_FILESYSTEM_PATH
        animation_destination_path( new_path );
        
        CORE_FILESYSTEM_FILE
        file( animation_destination_path );
        
        file.OpenInput();
        
        file.Close();
        
    }*/
    
    {
        GRAPHIC_MESH_ANIMATION_COLLECTION
            collection;
        
        collection.GetAnimationTable().resize( object->GetAnimationTable().size() );
        
        for (int i = 0; i < object->GetAnimationTable().size(); i++ ) {
            
            collection.GetAnimationTable()[ i ] = object->GetAnimationTable()[ i ];
        }
        
        char * new_path = (char *) CORE_MEMORY_ALLOCATOR::Allocate( strlen(destination_path.GetPath()) + strlen( destination_path.GetPath()) +1 );
        
        strcpy(new_path, destination_path.GetPath() );
        
        char * last_dot = strrchr ( new_path, '.' );
        ++last_dot;
        *last_dot = '\0';
        
        strcat(new_path, "acbx" );
        
        CORE_DATA_STREAM
            animation_stream;
        CORE_FILESYSTEM_PATH
            animation_destination_path( new_path );
        CORE_FILESYSTEM_FILE
            file( animation_destination_path );
        
        animation_stream.Open();
        
        XS_CLASS_SERIALIZER< GRAPHIC_MESH_ANIMATION_COLLECTION, CORE_DATA_STREAM >::Serialize< std::true_type >( "asset", collection, animation_stream );
        
        animation_stream.Close();
        
        if ( !file.OpenInput() ) {
            
            CORE_RUNTIME_Abort();
        }
        
        int bytes_written = file.InputBytes( animation_stream.GetMemoryBuffer(), animation_stream.GetOffset() );
        
        file.Close();
        
        if ( bytes_written != animation_stream.GetOffset() ) {
            
            CORE_RUNTIME_Abort();
        }
    }
    
    /*for (int i = 0; i < object->GetAnimationTable().size(); i++ ) {
        
        GRAPHIC_MESH_ANIMATION * animation = object->GetAnimationTable()[ i ];
        
        char * new_path = (char *) CORE_MEMORY_ALLOCATOR::Allocate( strlen(destination_path.GetPath()) + strlen(animation->GetName().c_str()) +2 );
        
        strcpy(new_path, destination_path.GetPath() );
        
        char * last_dot = strrchr ( new_path, '.' );
        ++last_dot;
        *last_dot = '\0';
        
        strcat(new_path, animation->GetName().c_str() );
        strcat(new_path, ".abx" );
        
        char buff[2];
        
        sprintf(buff, "%i", i );
        
        strcat(new_path, buff);
        
        CORE_DATA_STREAM
            animation_stream;
        CORE_FILESYSTEM_PATH
            animation_destination_path( new_path );
        CORE_FILESYSTEM_FILE
            file( animation_destination_path );
        
        animation_stream.Open();
        
        XS_CLASS_SERIALIZER< GRAPHIC_MESH_ANIMATION, CORE_DATA_STREAM >::Serialize< std::true_type >( "asset", *object->GetAnimationTable()[ i ], animation_stream );
        
        animation_stream.Close();
        
        if ( !file.OpenInput() ) {
            
            CORE_RUNTIME_Abort();
        }
        
        int bytes_written = file.InputBytes( animation_stream.GetMemoryBuffer(), animation_stream.GetOffset() );
        
        file.Close();
        
        if ( bytes_written != animation_stream.GetOffset() ) {
            
            CORE_RUNTIME_Abort();
        }
    }*/
}
#endif

GRAPHIC_OBJECT * GRAPHIC_OBJECT_RESOURCE_LOADER::LoadObject( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad ) {
    
    GRAPHIC_OBJECT
    * object = new GRAPHIC_OBJECT;
    
    switch ( meshTypeToLoad )
    {
#ifdef __COMPILE_WITH__COLLADA__
        case GRAPHIC_MESH_TYPE_OpenCollada :
        {
            GRAPHIC_MESH_LOADER_COLLADA
                loader;
            
            loader.LoadFile( *object, path );
            
            break;
        }
#endif
            
        case GRAPHIC_MESH_TYPE_ModelResource :
        {
            CORE_FILESYSTEM_FILE
            file( path );
            
            if ( !file.OpenOutput() ) {
                
                return NULL;
            }
            
            int file_size = file.GetSize();
            
            CORE_DATA_STREAM stream( file_size );
            
            int bytes_read = file.OutputBytes(stream.GetMemoryBuffer(), file_size );
            
            if ( bytes_read != file_size ) {
                
                file.Close();
                
                CORE_MEMORY_ObjectSafeDeallocation( object );
                
                return NULL;
            }
            
            file.Close();
            
            stream.Open();
            stream.ResetOffset();
            
            SERVICE_LOGGER_Error( "resource size %d\n", stream.GetAllocatedBytes() );
            
            XS_CLASS_SERIALIZER< GRAPHIC_OBJECT, CORE_DATA_STREAM >::Serialize<std::false_type>( "object", *object, stream );
            
            stream.Close();
            
            for ( size_t i = 0; i < object->GetMeshTable().size(); i++ ) {
                
                object->GetMeshTable()[ i ]->CreateBuffers();
            }
            
            break;
        }
            
        default:
        {
            
            break;
        }
    }
    
    return object;
}
