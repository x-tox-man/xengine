//
//  CORE_APPLICATION.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/11/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __CORE_APPLICATION__
#define __CORE_APPLICATION__

#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_WINDOW.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "CORE_MEMORY.h"

XS_CLASS_BEGIN( CORE_APPLICATION )

    CORE_APPLICATION() :
        ApplicationWindow(),
        ApplicationName(),
        ApplicationVersion() {
        
    }

    virtual ~CORE_APPLICATION();

    //:NOTE: this could come from scripts :
    
    virtual void Initialize();
    virtual void Finalize();
    virtual void Update( float time_step );
    virtual void Render();

    static void SetApplicationInstance( CORE_APPLICATION & instance ) { Instance = &instance; }
    static CORE_APPLICATION & GetApplicationInstance() { return *Instance; }

    void setApplicationName( const char * applicationName ) {
        
        ApplicationName = (char * ) CORE_MEMORY_ALLOCATOR::Allocate( strlen( applicationName));
        strcpy( ApplicationName, applicationName);
    }

    void setApplicationVersion( const char * applicationVersion ) {
        
        ApplicationName = (char * ) CORE_MEMORY_ALLOCATOR::Allocate( strlen( applicationVersion));
        strcpy( ApplicationVersion, applicationVersion);
    }
    
    const char * getApplicationName() const { return ApplicationName; }
    const char * getApplicationVersion() const { return ApplicationVersion; }
    void SetApplicationWindow( GRAPHIC_WINDOW & application_window) { ApplicationWindow = &application_window; }
    const GRAPHIC_WINDOW & GetApplicationWindow() const { return *ApplicationWindow; }
    GRAPHIC_WINDOW & GetApplicationWindow() { return *ApplicationWindow; }
    char
        * ApplicationName,
        * ApplicationVersion;
    
    // -- CALLBACKS

    void setApplicationCallback( CORE_HELPERS_CALLBACK & callback , int callbackId );
    
    protected :
    
    GRAPHIC_WINDOW * ApplicationWindow;
    static CORE_APPLICATION * Instance;
    
XS_CLASS_END

#endif /* defined(__CORE_APPLICATION__) */
