//
//  GRAPHIC_OBJECT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include <math.h>

#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_MATRIX.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "CORE_DATA_STREAM.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_OBJECT )
    XS_DEFINE_ClassMember( std::vector< GRAPHIC_MESH * > , MeshTable )
    XS_DEFINE_ClassMember( std::vector< GRAPHIC_MESH_ANIMATION_JOINT *>, JointTable )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_OBJECT::GRAPHIC_OBJECT() :
    GR_O_ANCESTOR_TYPE(),
    MeshTable(),
    JointTable()
#if __COMPILE_WITH__COLLADA__
    ,AnimationTable()
#endif
{
    
    JointTable.resize(0);
}

GRAPHIC_OBJECT::~GRAPHIC_OBJECT() {
    
    Release();
    
    for( int i = 0; i < MeshTable.size(); i++ ) {

        CORE_MEMORY_ObjectSafeDeallocation( MeshTable[ i ] );
    }

    for ( int i=0; i < JointTable.size(); i++ ) {

        CORE_MEMORY_ObjectSafeDeallocation( JointTable[ i ] );
    }
    
    #if __COMPILE_WITH__COLLADA__
        for ( int i = 0; i < AnimationTable.size(); i++ ) {
            
            CORE_MEMORY_ObjectSafeDeallocation( AnimationTable[ i ] );
        }
    #endif
}

void GRAPHIC_OBJECT::AddNewMesh( GRAPHIC_MESH * mesh ) {
    
    MeshTable.push_back(mesh);
}

void GRAPHIC_OBJECT::Render( GRAPHIC_RENDERER & renderer, const GRAPHIC_OBJECT_RENDER_OPTIONS & options, GRAPHIC_SHADER_EFFECT * effect ) {

    effect->Apply( renderer );
    
    for ( int i = 0; i < MeshTable.size(); i++ ) {
        
        CORE_MATH_MATRIX
            result;
        
        GRAPHIC_SHADER_ATTRIBUTE * mvp_matrix = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
        
        GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
        
        CompteModelViewProjection( options, MeshTable[i]->GetTransform(), renderer, result );
        
        GRAPHIC_SYSTEM_ApplyMatrix(mvp_matrix->AttributeIndex, 1, 0, &result[0])
        
        MeshTable[ i ]->ApplyBuffers();
    }
    
    effect->Discard();
}

void GRAPHIC_OBJECT::CompteModelViewProjection( const GRAPHIC_OBJECT_RENDER_OPTIONS & options, const CORE_MATH_MATRIX & transform, GRAPHIC_RENDERER & renderer, CORE_MATH_MATRIX & mvp ) {
    
    CORE_MATH_MATRIX
        object_matrix,
        scaling_matrix;
    
    if ( !transform.IsIdentity() ) {
        
        object_matrix *= transform;
    }
    
    CORE_MATH_MATRIX
        orientation_mat;
    
    options.GetOrientation().ToMatrix( &orientation_mat[0] );
    
    object_matrix.Scale( options.GetScaleFactor() );
    object_matrix *= orientation_mat;
    object_matrix.Translate( options.GetPosition() );
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    
    mvp = renderer.GetCamera().GetProjectionMatrix();
    mvp *= renderer.GetCamera().GetViewMatrix();
    mvp *= object_matrix;
}

void GRAPHIC_OBJECT::Release() {
    
    for ( int i = 0; i < MeshTable.size(); i++ ) {
        
        MeshTable[i]->ReleaseBuffers();
    }
}
