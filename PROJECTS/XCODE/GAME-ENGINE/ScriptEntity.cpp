//
//  ScriptEntity.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "ScriptEntity.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( ScriptEntity )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD( ScriptEntity, mySuperScriptMethod )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( ScriptEntity, mySuperScriptMethodWithParameter, const char * )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD( ScriptEntity, Ping )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( ScriptEntity )

ScriptEntity::ScriptEntity() {

}

ScriptEntity::~ScriptEntity() {

}

void ScriptEntity::Ping() {
    
    SERVICE_LOGGER_Info("ping\n");
}

void ScriptEntity::Initialize( CORE_FILESYSTEM_PATH path ) {
    
    
}

void ScriptEntity::mySuperScriptMethod() {
    
    SERVICE_LOGGER_Info("putain ca mourche \n" );
}

void ScriptEntity::mySuperScriptMethodWithParameter(const char * string ) {
    
    SERVICE_LOGGER_Info("putain ca mourche avec un param %s \n", string );
}

int ScriptEntity::mySuperScriptMethodWithParameterAndReturnType(const char *) {
    
    return 0;
}
