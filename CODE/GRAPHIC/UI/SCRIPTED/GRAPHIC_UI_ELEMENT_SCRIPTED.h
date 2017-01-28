//
//  GRAPHIC_UI_ELEMENT_SCRIPTED.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 5/12/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_ELEMENT_SCRIPTED_H
#define GRAPHIC_UI_ELEMENT_SCRIPTED_H

#include "CORE_HELPERS_CLASS.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"

XS_CLASS_BEGIN( GRAPHIC_UI_ELEMENT_SCRIPTED )

    GRAPHIC_UI_ELEMENT_SCRIPTED();

    void Initialize( const CORE_FILESYSTEM_PATH & path, void * element_ptr );
    void InitializeFrame( const CORE_FILESYSTEM_PATH & path, void * frame_ptr );
    void Start();
    void Update( float time_step );
    void Reset();

    void Copy( GRAPHIC_UI_ELEMENT_SCRIPTED & other );
private :

    CORE_ABSTRACT_PROGRAM_LUA::PTR LuaProgram;
    bool IsRunning;

XS_CLASS_END

#endif /* GRAPHIC_UI_ELEMENT_SCRIPTED_hpp */
