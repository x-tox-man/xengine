//
//  GRAPHIC_MESH_SKELETON_JOINT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_SKELETON_JOINT.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH_SKELETON_JOINT )
    XS_DEFINE_ClassMember( "Index", int, Index )
    XS_DEFINE_ClassMember( "ChildCount", int, ChildCount )
    XS_DEFINE_ClassMemberArray( "ChildJointTable", GRAPHIC_MESH_SKELETON_JOINT, ChildJointTable, (int) ChildCount )
    XS_DEFINE_ClassMemberArray( "Name", char, Name, (size_t) 256 )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_MESH_SKELETON_JOINT::GRAPHIC_MESH_SKELETON_JOINT() :
    ChildJointTable( NULL ),
    Index( 0 ),
    ChildCount( 0 ),
    Transform(),
    Name() {
    
}

GRAPHIC_MESH_SKELETON_JOINT::~GRAPHIC_MESH_SKELETON_JOINT() {

    //JOINTS will be relesed elsewhere
}

void GRAPHIC_MESH_SKELETON_JOINT::print() {
    
    for (int i = 0; i < ChildCount; i++ ) {
        
        ChildJointTable[i].print();
    }
}
