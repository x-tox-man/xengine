//
//  GRAPHIC_OBJECT_SHAPE_SPHERE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_OBJECT_SHAPE_SPHERE.h"
#include "GRAPHIC_MESH.h"

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

#define unit_s 1.0f
#define ring_c 13


GRAPHIC_OBJECT_SHAPE_SPHERE::GRAPHIC_OBJECT_SHAPE_SPHERE( int sphere_rings ) :
    GRAPHIC_OBJECT_SHAPE(),
    SphereRings( sphere_rings ) {
    
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Position );
    ShaderBindParameter = ( GRAPHIC_SHADER_BIND ) ( ShaderBindParameter | GRAPHIC_SHADER_BIND_Normal );
}

GRAPHIC_OBJECT_SHAPE_SPHERE::GRAPHIC_OBJECT_SHAPE_SPHERE() :
    GRAPHIC_OBJECT_SHAPE(),
    SphereRings( 0 ) {

}

GRAPHIC_OBJECT_SHAPE_SPHERE::~GRAPHIC_OBJECT_SHAPE_SPHERE() {

}

void GRAPHIC_OBJECT_SHAPE_SPHERE::InitializeShape() {
    
    unsigned int * index_data = ( unsigned int * ) CORE_MEMORY_ALLOCATOR::Allocate( sizeof( unsigned int ) * ring_c * ring_c * 6 );
    
    //algo : 1 vertex => 4 => 16
    
    float * vertex_data = ( float * ) CORE_MEMORY_ALLOCATOR::Allocate ( 8 * sizeof( float ) * ring_c * ring_c * 4 );

    float ratio = 1.0f / ring_c;
    
    int index = 0;
    int cube_index = 0;
    
    for ( int longi = 0; longi < ring_c; longi++ ) {
        
        for ( int lati = 0; lati < ring_c; lati++ ) {
            
            float longi_ratio_base = (longi ) * ratio;
            float longi_ratio_offset = (longi + 1 ) * ratio;
            float lati_ratio_base = (lati ) * ratio;
            float lati_ratio_offset = (lati + 1 ) * ratio;
            
            index_data[ cube_index * 6 + 0 ] = cube_index * 4 ;
            index_data[ cube_index * 6 + 1 ] = cube_index * 4 + 3;
            index_data[ cube_index * 6 + 2 ] = cube_index * 4 + 2;
            index_data[ cube_index * 6 + 3 ] = cube_index * 4;
            index_data[ cube_index * 6 + 4 ] = cube_index * 4 + 2;
            index_data[ cube_index * 6 + 5 ] = cube_index * 4 + 1;
            
            cube_index++;
            
            computePoint( vertex_data, longi_ratio_base,    lati_ratio_base, index++ );
            computePoint( vertex_data, longi_ratio_offset,  lati_ratio_base, index++ );
            computePoint( vertex_data, longi_ratio_offset,  lati_ratio_offset, index++ );
            computePoint( vertex_data, longi_ratio_base,    lati_ratio_offset, index++ );
        }
    }
    
    GRAPHIC_MESH * mesh = new GRAPHIC_MESH();
    
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Position);
    mesh->ActivateBufferComponent(GRAPHIC_SHADER_BIND_Normal);
    
    CORE_DATA_BUFFER * index_buffer = new CORE_DATA_BUFFER;
    CORE_DATA_BUFFER * vertex_buffer = new CORE_DATA_BUFFER;
    
    index_buffer->InitializeWithMemory( ring_c * ring_c * 6 * sizeof(unsigned int), 0, (void*) index_data );
    vertex_buffer->InitializeWithMemory( ring_c * ring_c * 4 * 10 * sizeof(float), 0, (void*) vertex_data );
    
    mesh->SetIndexCoreBuffer( index_buffer );
    mesh->SetVertexCoreBuffer( vertex_buffer );
    
    CORE_MEMORY_ALLOCATOR_Free( index_data );
    CORE_MEMORY_ALLOCATOR_Free( vertex_data );
    
    mesh->CreateBuffers();
    
    AddNewMesh( mesh );
}

void GRAPHIC_OBJECT_SHAPE_SPHERE::computePoint( float * data_pointer, float longi_ratio, float lati_ratio, int point_index ) {
    
    static float base_vector[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    CORE_MATH_MATRIX rotation_matrix ( CORE_MATH_MATRIX::Identity );
    
    rotation_matrix.XRotate( ( float ) ( -longi_ratio * M_PI ) );
    rotation_matrix.YRotate( ( float ) ( lati_ratio * M_PI * 2.0f ) );
    
    CORE_SCALAR vector;
    
    vector = base_vector * rotation_matrix;
    
    data_pointer[ point_index * 8 + 0 ] = vector.Value.FloatArray4[ 0 ];
    data_pointer[ point_index * 8 + 1 ] = vector.Value.FloatArray4[ 1 ];
    data_pointer[ point_index * 8 + 2 ] = vector.Value.FloatArray4[ 2 ];
    data_pointer[ point_index * 8 + 3 ] = 1.0f;
    
    data_pointer[ point_index * 8 + 4 ] = vector.Value.FloatArray4[ 0 ];
    data_pointer[ point_index * 8 + 5 ] = vector.Value.FloatArray4[ 1 ];
    data_pointer[ point_index * 8 + 6 ] = vector.Value.FloatArray4[ 2 ];
    data_pointer[ point_index * 8 + 7 ] = 1.0f;
}
