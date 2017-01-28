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

XS_CLASS_BEGIN( CORE_APPLICATION )
    
    // -- APPLICATION SPECIFICS

    CORE_APPLICATION() : ApplicationWindow() {
        
    }

    //:NOTE: this could come from scripts :
    
    virtual void Initialize();
    virtual void Finalize();
    virtual void Render();
    
    void setApplicationName( const char * applicationName ) { ApplicationName = applicationName; }
    void setApplicationVersion( const char * applicationVersion ) { ApplicationVersion = applicationVersion; }
    
    const std::string & getApplicationName() const { return ApplicationName; }
    const std::string & getApplicationVersion() const { return ApplicationVersion; }
    void SetApplicationWindow( GRAPHIC_WINDOW & application_window) { ApplicationWindow = &application_window; }
    const GRAPHIC_WINDOW & GetApplicationWindow() const { return *ApplicationWindow; }
    
    std::string ApplicationName, ApplicationVersion;
    
    // -- CALLBACKS

    void setApplicationCallback( CORE_HELPER_CALLBACK & callback , int callbackId );
    
    protected :
    
    GRAPHIC_WINDOW
        * ApplicationWindow;
    

XS_CLASS_END

#endif /* defined(__CORE_APPLICATION__) */
