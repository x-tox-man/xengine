//
//  CORE_ABSTRACT_PROGRAM_NATIVELIBRARY.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 08/04/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "CORE_ABSTRACT_PROGRAM_NATIVELIBRARY.h"

CORE_ABSTRACT_PROGRAM_NATIVELIBRARY::CORE_ABSTRACT_PROGRAM_NATIVELIBRARY() :
    CORE_ABSTRACT_PROGRAM_FACTORY() {
    
}

CORE_ABSTRACT_PROGRAM_NATIVELIBRARY::CORE_ABSTRACT_PROGRAM_NATIVELIBRARY( const CORE_ABSTRACT_PROGRAM_NATIVELIBRARY & other) : CORE_ABSTRACT_PROGRAM_FACTORY() {
    
}

CORE_ABSTRACT_PROGRAM_NATIVELIBRARY::~CORE_ABSTRACT_PROGRAM_NATIVELIBRARY() {
    
}

void CORE_ABSTRACT_PROGRAM_NATIVELIBRARY::Load( const char * path, const CORE_ABSTRACT_BASE_PROGRAM_RUNTIME & runtime) {
    
#if PLATFORM_OSX
    char final_path[128];
    
    CORE_DATA_COPY_STRING( final_path, path );
    CORE_DATA_STRING_CONCAT( final_path, ".dylib" );
    
    LibraryHandle = dlopen( final_path, RTLD_LOCAL);
    
    if (LibraryHandle) {
                
        char* (*b1a_name)() = dlsym(Bus1a_handle, "B1a_name");
        
        if (b1a_name) {
            
            printf("[%s] libBus1a.B1a_name() = %s\n",
                   __FILE__, b1a_name());
        }
    }
    else {
        printf("[%s] Unable to open libBus1a.dylib: %s\n", __FILE__, dlerror());
    }
    
#endif
    
}

void CORE_ABSTRACT_PROGRAM_NATIVELIBRARY::Execute() {
    
}

void CORE_ABSTRACT_PROGRAM_NATIVELIBRARY::Finalize() {
    
#if PLATFORM_OSX
    dlclose(Bus1a_handle);
#endif
}
