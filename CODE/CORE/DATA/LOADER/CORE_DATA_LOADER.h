//
//  CORE_DATA_LOADER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_DATA_LOADER_h
#define CORE_DATA_LOADER_h

#include "CORE_DATA_STREAM.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_FILESYSTEM_FILE.h"


template <typename __TYPE_TO_SERIALIZE__ >
class CORE_DATA_LOADER {
    
public:
    static bool Load( __TYPE_TO_SERIALIZE__ * object, const CORE_FILESYSTEM_PATH & path ) {
        
        CORE_FILESYSTEM_FILE
            file( path );
        
        if ( !file.OpenOutput() ) {
            
            return false;
        }
        
        int file_size = file.GetSize();
        
        CORE_DATA_STREAM stream( file_size );
        
        int bytes_read = file.OutputBytes(stream.GetMemoryBuffer(), file_size );
        
        if ( bytes_read != file_size ) {
            
            file.Close();
            
            return false;
        }
        
        file.Close();
        
        stream.Open();
        stream.ResetOffset();
        
        SERVICE_LOGGER_Error( "resource size %d\n", stream.GetAllocatedBytes() );
        
        XS_CLASS_SERIALIZER< __TYPE_TO_SERIALIZE__, CORE_DATA_STREAM >::template Serialize<std::false_type>( "data", *object, stream );
        
        stream.Close();
        
        return true;
    }
    
    static bool Load( __TYPE_TO_SERIALIZE__ * object, const CORE_FILESYSTEM_PATH & path, CORE_DATA_STREAM & stream ) {
        
        CORE_FILESYSTEM_FILE
            file( path );
        
        if ( !file.OpenOutput() ) {
            
            return false;
        }
        
        int file_size = file.GetSize();
        
        stream.InitializeWithSize( file_size );
        
        int bytes_read = file.OutputBytes(stream.GetMemoryBuffer(), file_size );
        
        if ( bytes_read != file_size ) {
            
            file.Close();
            
            return false;
        }
        
        file.Close();
        
        stream.Open();
        stream.ResetOffset();
        
        SERVICE_LOGGER_Error( "resource size %d\n", stream.GetAllocatedBytes() );
        
        XS_CLASS_SERIALIZER< __TYPE_TO_SERIALIZE__, CORE_DATA_STREAM >::template Serialize<std::false_type>( "data", *object, stream );
        
        return true;
    }
    
    static bool Load( __TYPE_TO_SERIALIZE__ * object, CORE_DATA_STREAM & stream ) {
        
        XS_CLASS_SERIALIZER< __TYPE_TO_SERIALIZE__, CORE_DATA_STREAM >::template Serialize<std::false_type>( "object", *object, stream );
        
        return true;
    }
    
    static bool Save( __TYPE_TO_SERIALIZE__ * object, const CORE_FILESYSTEM_PATH & path ) {
        
        CORE_DATA_STREAM
            stream;
        CORE_FILESYSTEM_FILE
            file( path );
        
        stream.Open();
        
        XS_CLASS_SERIALIZER< __TYPE_TO_SERIALIZE__, CORE_DATA_STREAM >::template Serialize< std::true_type >( "object", *object, stream );
        
        stream.Close();
        
        if ( !file.OpenInput() ) {
            
            return false;
        }
        
        int bytes_written = file.InputBytes( stream.GetMemoryBuffer(), stream.GetOffset() );
        
        file.Close();
        
        if ( bytes_written != stream.GetOffset() ) {
            
            return false;
        }
        
        return true;
    }
    
    static bool Save( CORE_DATA_STREAM & stream, const CORE_FILESYSTEM_PATH & path ) {
        
        CORE_FILESYSTEM_FILE
            file( path );
        
        if ( !file.OpenInput() ) {
            
            return false;
        }
        
        int bytes_written = file.InputBytes( stream.GetMemoryBuffer(), stream.GetOffset() );
        
        file.Close();
        
        if ( bytes_written != stream.GetOffset() ) {
            
            return false;
        }

        
        return true;
    }
};

#endif /* CORE_DATA_LOADER_h */
