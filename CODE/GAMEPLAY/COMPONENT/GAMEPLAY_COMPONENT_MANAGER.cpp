//
//  GAMEPLAY_COMPONENT_MANAGER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_ACTION.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_SCRIPT.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY_HANDLE, CORE_HELPERS_IDENTIFIER )

typedef std::map< CORE_HELPERS_IDENTIFIER, GAMEPLAY_COMPONENT_ENTITY_HANDLE > MGCEHHMAP;

/*XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_MANAGER )
    XS_DEFINE_ClassMember( "NamedEntitiesTable", MGCEHHMAP , NamedEntitiesTable )
XS_END_INTERNAL_MEMORY_LAYOUT*/

GAMEPLAY_COMPONENT_MANAGER::GAMEPLAY_COMPONENT_MANAGER() :
    ECSData(),
    NamedEntitiesTable(),
    Offset( 0 ) {
    
    Initialize();
}

GAMEPLAY_COMPONENT_MANAGER::~GAMEPLAY_COMPONENT_MANAGER() {

}

void GAMEPLAY_COMPONENT_MANAGER::Initialize() {

    ECSData.InitializeWithSize( ECS_SIZE * 2048 );
}

void GAMEPLAY_COMPONENT_MANAGER::Finalize() {
    
    ECSData.Close();
}

void GAMEPLAY_COMPONENT_MANAGER::Clear() {
    
    ECSData.Close();
}

void GAMEPLAY_COMPONENT_MANAGER::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    //CORE_RUNTIME_Abort();
    stream.InputBytes( (u_int8_t*) ECSData.GetMemoryBuffer(), ECSData.GetSize() );
}

void GAMEPLAY_COMPONENT_MANAGER::LoadFromStream( CORE_DATA_STREAM & stream ) {

    stream.OutputBytes( (u_int8_t*) ECSData.GetMemoryBuffer(), ECSData.GetSize() );
}

