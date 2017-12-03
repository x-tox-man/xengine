//
//  GRAPHIC_OBJECT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include <math.h>

#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_MATRIX.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_OBJECT )
    XS_DEFINE_ClassMember( "MeshTable", std::vector< GRAPHIC_MESH * > , MeshTable )
    XS_DEFINE_ClassMember( "JointTable", std::vector< GRAPHIC_MESH_ANIMATION_JOINT *>, JointTable )
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

GRAPHIC_OBJECT::GRAPHIC_OBJECT( const GRAPHIC_OBJECT & other) :
    GR_O_ANCESTOR_TYPE(),
    MeshTable( other.MeshTable),
    JointTable(other.JointTable)
    #if __COMPILE_WITH__COLLADA__
        ,AnimationTable( other.AnimationTable)
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
    
    for ( int i = 0; i < MeshTable.size(); i++ ) {
        
        CORE_MATH_MATRIX
            result,
            object;
        
        GRAPHIC_SYSTEM::EnableBlend( GRAPHIC_SYSTEM_BLEND_OPERATION_SourceAlpha, GRAPHIC_SYSTEM_BLEND_OPERATION_OneMinusSourceAlpha );
        
        effect->Apply( renderer );
        
        GRAPHIC_SHADER_ATTRIBUTE * mvp_matrix = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
        GRAPHIC_SHADER_ATTRIBUTE * model_matrix = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ModelViewMatrix );
        GRAPHIC_SHADER_ATTRIBUTE & time_mod = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::TimeModulator );
        
        CompteModelViewProjection( options, MeshTable[i]->GetTransform(), renderer, result, object );
        
        GRAPHIC_SYSTEM_ApplyMatrix(mvp_matrix->AttributeIndex, 1, 0, &result[0])
        
        if ( model_matrix->AttributeIndex > 0 ) {
            GRAPHIC_SYSTEM_ApplyMatrix(model_matrix->AttributeIndex, 1, 0, &object[0])
        }

        GRAPHIC_SHADER_ATTRIBUTE & depth = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture );
        
        if ( time_mod.AttributeIndex > 0 ) {
            
            GFX_CHECK( glUniform1f( time_mod.AttributeIndex,
                                   time_mod.AttributeValue.Value.FloatValue); )
        }
        
        if ( depth.AttributeIndex > 0 && renderer.GetDepthTexture() ) {
            
            CORE_MATH_MATRIX
            depthMVP,
            depthBias;
            
            assert( depth.AttributeIndex > 0 );
            
            GRAPHIC_SHADER_ATTRIBUTE * shadowmap_mvp = &effect->GetProgram().getShaderAttribute(GRAPHIC_SHADER_PROGRAM::ShadowMapMVP );
            
            renderer.GetDepthTexture()->ApplyDepth(0, depth.AttributeIndex );
            
            CORE_MATH_MATRIX biasMatrix(0.5f, 0.0f, 0.0f, 0.5f,
                                        0.0f, 0.5f, 0.0f, 0.5f,
                                        0.0f, 0.0f, 0.5f, 0.5f,
                                        0.0f, 0.0f, 0.0f, 1.0f
                                        );
            
            depthMVP = renderer.GetShadowMapCamera().GetProjectionMatrix();
            depthMVP *= renderer.GetShadowMapCamera().GetViewMatrix();
            depthMVP *= object;
            
            depthBias = biasMatrix * depthMVP;
            
            GRAPHIC_SYSTEM_ApplyMatrix( shadowmap_mvp->AttributeIndex, 1, 0, &depthBias[0] )
        }
        
        MeshTable[ i ]->ApplyBuffers();
    }
    
    effect->Discard();
}

void GRAPHIC_OBJECT::CompteModelViewProjection( const GRAPHIC_OBJECT_RENDER_OPTIONS & options, const CORE_MATH_MATRIX & transform, GRAPHIC_RENDERER & renderer, CORE_MATH_MATRIX & mvp, CORE_MATH_MATRIX & object_matrix ) {
    
    CORE_MATH_MATRIX
        scaling_matrix;
    CORE_MATH_MATRIX
        parent_matrix;
    
    CORE_MATH_MATRIX
        orientation_mat;
    
    if ( options.GetParent() ) {
        
        options.GetParent()->GetOrientation().ToMatrix( &orientation_mat[0] );
        
        object_matrix.Translate( options.GetParent()->GetPosition() );
        object_matrix *= orientation_mat;
    }
    
    if ( !transform.IsIdentity() ) {
        
        object_matrix *= transform;
    }
    
    options.GetOrientation().ToMatrix( &orientation_mat[0] );
    
    object_matrix.Scale( options.GetScaleFactor() );
    object_matrix.Translate( options.GetPosition() );
    object_matrix *= orientation_mat;
    
    
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

GRAPHIC_SHADER_BIND & GRAPHIC_OBJECT::GetShaderBindParameter() {
    
    return MeshTable[0]->GetVertexComponent();
}
