//
//  CORE_APPLICATION.h
//  GAME-ENGINE
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
#include "GAMEPLAY_GAME.h"

XS_CLASS_BEGIN( CORE_APPLICATION )

    CORE_APPLICATION() :
        ApplicationWindow(),
        ApplicationName(),
        ApplicationVersion(),
        Game() {
        
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
        
        size_t l=strlen( applicationName )+1;

        ApplicationName = (char * ) CORE_MEMORY_ALLOCATOR::Allocate( l );
        CORE_DATA_COPY_STRING(ApplicationName, applicationName );
    }

    void setApplicationVersion( const char * applicationVersion ) {
        
        size_t l=strlen( applicationVersion ) + 1;

        ApplicationVersion=( char * ) CORE_MEMORY_ALLOCATOR::Allocate( l );

        CORE_DATA_COPY_STRING(ApplicationVersion, applicationVersion );
    }

    inline GAMEPLAY_GAME & GetGame() { return Game; }
    
    inline const char * getApplicationName() const { return ApplicationName; }
    inline const char * getApplicationVersion() const { return ApplicationVersion; }
    inline void SetApplicationWindow( GRAPHIC_WINDOW & application_window) { ApplicationWindow = &application_window; }
    inline const GRAPHIC_WINDOW & GetApplicationWindow() const { return *ApplicationWindow; }
    inline GRAPHIC_WINDOW & GetApplicationWindow() { return *ApplicationWindow; }

    char
        * ApplicationName,
        * ApplicationVersion;
    
    // -- CALLBACKS

    void setApplicationCallback( CORE_HELPERS_CALLBACK & callback , int callbackId );
    
    protected :
    
    GRAPHIC_WINDOW
        * ApplicationWindow;
    static CORE_APPLICATION
        * Instance;
    GAMEPLAY_GAME
        Game;
    CORE_FILESYSTEM
        DefaultFileystem;

XS_CLASS_END

#endif /* defined(__CORE_APPLICATION__) */
