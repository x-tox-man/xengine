//
//  GRAPHIC_MESH_MANAGER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_MESH_LOADER_COLLADA.h"
#include "GRAPHIC_OBJECT_ANIMATED.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_LOADER.h"
#include "CORE_DATA_JSON.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GRAPHIC_MESH_MANAGER::GRAPHIC_MESH_MANAGER() {
    
}

GRAPHIC_MESH_MANAGER::~GRAPHIC_MESH_MANAGER() {

}

GRAPHIC_OBJECT * GRAPHIC_MESH_MANAGER::LoadObject( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad ) {
    
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

GRAPHIC_OBJECT_ANIMATED * GRAPHIC_MESH_MANAGER::LoadObjectAnimated( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad ) {
    
    GRAPHIC_OBJECT_ANIMATED
        * object = new GRAPHIC_OBJECT_ANIMATED;
    
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
            CORE_DATA_LOADER< GRAPHIC_OBJECT >::Load( object, path );
            
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

void GRAPHIC_MESH_MANAGER::Compile( const CORE_FILESYSTEM_PATH & path, const CORE_FILESYSTEM_PATH & destination_path, const int meshIdentifier, int meshTypeToLoad ) {

    GRAPHIC_OBJECT
        * object;
    CORE_DATA_STREAM
        stream;
    CORE_FILESYSTEM_FILE
        file( destination_path );
    
    object = LoadObject( path, meshIdentifier, meshTypeToLoad );
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< GRAPHIC_OBJECT, CORE_DATA_STREAM >::Serialize< std::true_type >( "object", *object, stream );
    
    stream.Close();
    
    if ( !file.OpenInput() ) {
        
        CORE_RUNTIME_Abort();
    }
    
    int bytes_written = file.InputBytes( stream.GetMemoryBuffer(), stream.GetOffset() );
    
    file.Close();
    
    if ( bytes_written != stream.GetOffset() ) {
        
        CORE_RUNTIME_Abort();
    }
    
    #ifdef __COMPILE_WITH__COLLADA__
    
        // HACK : this will allow iphone to find object on correct path
        if ( object->GetAnimationTable().size() ) {
            
            GRAPHIC_MESH_ANIMATION * animation = object->GetAnimationTable()[ 0 ];
            
            char new_path[128];
            
            strcpy(new_path, destination_path.GetPath() );
            
            char * last_dot = strrchr ( new_path, '.' );
            ++last_dot;
            *last_dot = '\0';
            
            strcat(new_path, animation->GetAnimationName().c_str() );
            strcat(new_path, ".abx" );
            
            CORE_FILESYSTEM_PATH
                animation_destination_path( new_path );
            
            CORE_FILESYSTEM_FILE
                file( animation_destination_path );
            
            file.OpenInput();
            
            file.Close();
            
        }
    
        for (int i = 0; i < object->GetAnimationTable().size(); i++ ) {
        
            GRAPHIC_MESH_ANIMATION * animation = object->GetAnimationTable()[ i ];
        
            char new_path[128];
        
            strcpy(new_path, destination_path.GetPath() );
        
            char * last_dot = strrchr ( new_path, '.' );
            ++last_dot;
            *last_dot = '\0';
        
            strcat(new_path, animation->GetAnimationName().c_str() );
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
        
            XS_CLASS_SERIALIZER< GRAPHIC_MESH_ANIMATION, CORE_DATA_STREAM >::Serialize< std::true_type >( "mesh", *object->GetAnimationTable()[ i ], animation_stream );
        
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
    #endif
}

void GRAPHIC_MESH_MANAGER::GetMesh( int meshIdentifier )
{
    
}
