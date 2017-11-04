//
//  GRAPHIC_MESH_SUB_SKELETON.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_SUB_SKELETON.h"
#include "CORE_DATA_STREAM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_MESH_SUB_SKELETON )
    XS_DEFINE_ClassMember( "JointIndex", int, JointIndex )
    XS_DEFINE_ClassMember( "Transform", CORE_SCALAR, Transform )
    XS_DEFINE_ClassMember( "ChildCount", int, ChildCount )
    XS_DEFINE_ClassMemberArray( "SubSkelettonTable", GRAPHIC_MESH_SUB_SKELETON, SubSkelettonTable, (int) ChildCount )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_MESH_SUB_SKELETON::GRAPHIC_MESH_SUB_SKELETON() :
    SubSkelettonTable( NULL ),
    Joint( NULL ),
    JointIndex( 0 ),
    ChildCount( 0 ),
    Transform()  {
    
}

GRAPHIC_MESH_SUB_SKELETON::~GRAPHIC_MESH_SUB_SKELETON() {

    //JOINTS will be relesed elsewhere
}

void GRAPHIC_MESH_SUB_SKELETON::Initialize( const std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & table ) {
    
    Joint = table[ JointIndex ];
    
    #if DEBUG
        assert(Joint != NULL);
    #endif
    
    for (int i = 0; i < ChildCount; i++ ) {
        
        SubSkelettonTable[i].Initialize( table );
    }
}

void GRAPHIC_MESH_SUB_SKELETON::print() {
    
    SERVICE_LOGGER_Error( "Joint : %s\n", Joint->GetJointName() );
    
    for (int i = 0; i < ChildCount; i++ ) {
        
        SubSkelettonTable[i].print();
    }
}
