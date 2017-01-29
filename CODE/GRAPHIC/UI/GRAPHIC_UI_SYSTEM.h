//
//  GRAPHIC_UI_SYSTEM.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 20/12/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_SYSTEM_h
#define GRAPHIC_UI_SYSTEM_h

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_UI_RENDER_STYLE.h"
#include "CORE_MATH_SHAPE_RECTANGLE.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_UI_PLACEMENT.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "GRAPHIC_UI_ELEMENT_SCRIPTED.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "GRAPHIC_UI_FRAME.h"
#include "CORE_PARALLEL.h"

XS_CLASS_BEGIN( GRAPHIC_UI_SYSTEM )

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GRAPHIC_UI_SYSTEM );

    XS_DEFINE_UNIQUE( GRAPHIC_UI_SYSTEM )

    ~GRAPHIC_UI_SYSTEM();

    GRAPHIC_UI_FRAME * GetCurrentScreen() { return CurrentScreen; }

    void Update( float time_step );
    void Render( GRAPHIC_RENDERER &);

    void RegisterScreen( GRAPHIC_UI_FRAME * screen, const char * screen_name );
    void RegisterScritpedScreen( const CORE_FILESYSTEM_PATH & script_path, const char * screen_name );

    void UnregisterScreen(const char * screen_name);

    CORE_PARALLEL_LOCK_MUTEX & GetLockMutex() { return UISystemLock; }

    const CORE_MATH_VECTOR & GetScreenMouseCoordinates() { return ScreenMouseCoordinates; }

    void SetScreenSize( const CORE_MATH_VECTOR & screen_size ) { ScreenSize = screen_size; }
    const CORE_MATH_VECTOR & GetScreenSize() const { return ScreenSize; }

private :

    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_UI_FRAME * >
        VisibleScreenTable;
    GRAPHIC_UI_FRAME
        * CurrentScreen;
    CORE_PARALLEL_LOCK_MUTEX
        UISystemLock;
    CORE_MATH_VECTOR
        ScreenSize,
        ScreenMouseCoordinates;

XS_CLASS_END

#endif /* GRAPHIC_UI_SYSTEM_h */
