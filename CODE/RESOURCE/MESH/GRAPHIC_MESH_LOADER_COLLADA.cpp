//
//  GRAPHIC_MESH_LOADER_COLLADA.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_LOADER_COLLADA.h"

#if __COMPILE_WITH__COLLADA__

    #include "COLLADASaxFWLLoader.h"
    #include "COLLADAFWRoot.h"
    #include "COLLADAFWGeometry.h"
    #include "COLLADAFWNode.h"
    #include "COLLADAFWVisualScene.h"
    #include "COLLADAFWInstanceGeometry.h"
    #include "GRAPHIC_MESH.h"

    #include "GRAPHIC_SHADER_BIND.h"
    #include "MATH_TOOLBOX.h"

    bool COLLADA_LOADER_ERROR_HANDLER::handleError(const COLLADASaxFWL::IError *error )
    {
        return false;
    }

    COLLADA_LOADER_WRITER::COLLADA_LOADER_WRITER():
        COLLADAFW::IWriter(),
        graphicObject( NULL ),
        animatedJoints() {
        
    };

    void COLLADA_LOADER_WRITER::cancel(const COLLADAFW::String & errorMessage) {
        
    }

    /** This is the method called. The writer hast to prepare to receive data.*/
    void COLLADA_LOADER_WRITER::start()
    {
        
    }

    /** This method is called after the last write* method. No other methods will be called after this.*/
    void COLLADA_LOADER_WRITER::finish()
    {
        
    }

    /** When this method is called, the writer must write the global document asset.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeGlobalAsset ( const COLLADAFW::FileInfo* asset )
    {
        return true;
    }

    /** When this method is called, the writer must write the scene.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeScene ( const COLLADAFW::Scene* scene )
    {
        return true;
    }

    int COLLADA_LOADER_WRITER::FindNodeId( const char * node_name ) {
        
        int index = -1;
        
        for ( int i = 0; i < graphicObject->GetAnimationTable()[0]->GetJointTable().size(); i++ ) {
            
            if( graphicObject->GetAnimationTable()[0]->GetJointTable()[i] != NULL && strcmp(node_name, graphicObject->GetAnimationTable()[0]->GetJointTable()[i]->GetName() ) == 0 ) {
                
                return i;
            }
        }
        //TODO: What's up here here???
        return index;
    }

    void COLLADA_LOADER_WRITER::FillSkeleton( GRAPHIC_MESH_SKELETON_JOINT & skeleton, COLLADAFW::Node & node, std::vector< GRAPHIC_MESH_ANIMATION_JOINT::PTR > & new_joints_table ) {
        
        skeleton.ChildCount = (int) node.getChildNodes().getCount();
        skeleton.ChildJointTable = ( GRAPHIC_MESH_SKELETON_JOINT *) CORE_MEMORY_ALLOCATOR::Allocate( sizeof( GRAPHIC_MESH_SKELETON_JOINT ) * (int) node.getChildNodes().getCount() );
        
        skeleton.SetName( node.getName().c_str() );
        skeleton.Index = (int) indexTable[node.getUniqueId().getObjectId()];
         
        int found_node = FindNodeId( node.getName().c_str() );
        if ( found_node > -1 ) {
            new_joints_table[ skeleton.Index ] = graphicObject->GetAnimationTable()[0]->GetJointTable()[ found_node ];
        }
        else {
            new_joints_table[ skeleton.Index ] = NULL;
        }
        
        memcpy((void*) &skeleton.Transform.Value.FloatMatrix4x4, (void*)&node.getTransformationMatrix().getElement(0), 16 * sizeof(float));
        
        printf( "FillSkeleton %d %s\n", skeleton.Index, node.getName().c_str());
        
        for( int i = 0; i < (int) node.getChildNodes().getCount(); i++ ) {
            
            FillSkeleton( skeleton.ChildJointTable[ i ], *node.getChildNodes()[ i ], new_joints_table );
        }
    }

    /*void COLLADA_LOADER_WRITER::fillSkeleton(
                                             std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & joints,
                                             int base_index,
                                             int * index_table,
                                             COLLADAFW::Node * node,
                                             GRAPHIC_MESH_SKELETON_JOINT & skeleton ) {
        
        CORE_SCALAR
        scalar;
        
        memcpy((void*) &scalar.Value.FloatMatrix4x4, (void*)&node->getTransformationMatrix().getElement(0), 16 * sizeof(float));
        
        skeleton.SubSkelettonTable = ( GRAPHIC_MESH_SKELETON_JOINT *) CORE_MEMORY_ALLOCATOR::Allocate( sizeof( GRAPHIC_MESH_SKELETON_JOINT ) * node->getChildNodes().getCount() );
        
        skeleton.ChildCount = (int) node->getChildNodes().getCount();
        skeleton.Joint = joints[ node->getObjectId() ];
        
        if ( skeleton.Joint != NULL ) {
            
            for ( int i = 0; i < graphicObject->GetJointTable().size(); i++ ) {
                if ( strcmp(skeleton.Joint->GetJointName(), graphicObject->GetJointTable()[i]->GetJointName() ) == 0 ){
                    
                    skeleton.JointIndex = i;
                    break;
                }
            }
        }
        
        for ( int i = 0; i < node->getChildNodes().getCount(); i++ ) {
            
            fillSkeleton( joints, base_index, index_table, node->getChildNodes()[i], skeleton.SubSkelettonTable[i] );
        }
    }*/

    /** When this method is called, the writer must write the entire visual scene.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeVisualScene ( const COLLADAFW::VisualScene* visualScene )
    {
        std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> accumulatedVector;
        accumulatedVector.resize(256);
        
        int * index_table = (int*) CORE_MEMORY_ALLOCATOR::Allocate( 256 * sizeof( int ) );
        
        for (int i = 0; i < 256; i++ ) {
            accumulatedVector[0] = NULL;
            index_table[i] = -1;
        }
        
        if ( graphicObject->GetAnimationTable().size() > 0 ) {
            
            assert( graphicObject->GetAnimationTable().size() == 1 ); //handle multiple animations later
            
            for (int an_ind = 0; an_ind < graphicObject->GetAnimationTable().size(); an_ind++ ) {
                
                for (int i = 0; i < visualScene->getRootNodes().getCount(); i++ ) {
                    
                    //Hack: Ignore NODES only take joints for root nodes
                    if ( visualScene->getRootNodes()[i]->getType() != COLLADAFW::Node::NodeType::JOINT ){
                        continue;
                    }
                    
                    std::vector< GRAPHIC_MESH_ANIMATION_JOINT::PTR > tempTable;
                    tempTable.resize( graphicObject->GetAnimationTable()[0]->GetJointTable().size() );
                    
                    FillSkeleton( graphicObject->GetSkeleton(), *visualScene->getRootNodes()[i], tempTable );
                    
                    for ( int ai = 0; ai < graphicObject->GetAnimationTable()[0]->GetJointTable().size(); ai ++ ) {
                        
                        graphicObject->GetAnimationTable()[0]->GetJointTable()[ai] = tempTable[ ai ];
                    }
                }
            }
        }
        else {
            
            for (int i = 0; i < visualScene->getRootNodes().getCount(); i++ ) {
                
                if ( visualScene->getRootNodes()[i]->getInstanceGeometries().getCount() == 1 && graphicObject->GetMeshTable().size() > i) {

                    for (int j = 0; j < 16; j++){
                        float elem = visualScene->getRootNodes()[i]->getTransformationMatrix().getElement(j);
                        memcpy( (void*)&graphicObject->GetMeshTable()[i]->GetTransform()[j], (void*) &elem, sizeof(float));
                    }
                }
            }
        }
        
        CORE_MEMORY_ALLOCATOR_Free( index_table );
        
        return true;
    }

    /** When this method is called, the writer must handle all nodes contained in the
     library nodes.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeLibraryNodes ( const COLLADAFW::LibraryNodes* libraryNodes )
    {
        if ( ! libraryNodes->getNodes().empty() )
        {
            //Do something
        }
        
        return true;
    }

    bool COLLADA_LOADER_WRITER::ComputeBufferSizeForItem( int & buffer_size, int & section_count, const COLLADAFW::FloatOrDoubleArray & array )
    {
        if ( array.getFloatValues() )
        {
            buffer_size += ( array.getFloatValues()->getCount() / 3 ) * 4 * sizeof(float); // 3 floats mapped to 2??? float * sierofsbytes
            
            ++section_count;
            
            return true;
        }
        else if ( array.getDoubleValues() )
        {
            buffer_size += array.getDoubleValues()->getCount() /3 * 4 * sizeof(double);
            
            ++section_count;
            
            return true;
        }
        else
        {
            return false;
        }
    }

    void COLLADA_LOADER_WRITER::CopyVertexDataToBuffer( const COLLADAFW::FloatOrDoubleArray & array, const CORE_HELPERS_IDENTIFIER * identifier, CORE_DATA_BUFFER & buffer, int marker_index, int vertices_count )
    {
        unsigned int
        size = 0,
        count = 0;
        //item_size = array.getValuesCount() / vertices_count * 4;
        
        void * ptr = NULL;
        
        if ( array.getFloatValues() )
        {
            size = (int) array.getFloatValues()->getCount() * 4;
            count = (int) array.getValuesCount();
            ptr = (void *) array.getFloatValues()->getData();
        }
        else if ( array.getDoubleValues() )
        {
            size = (int) array.getDoubleValues()->getCount() * 8;
            count = (int) array.getValuesCount();
            ptr = (void *) array.getDoubleValues()->getData();
        }
        
        //    if ( ptr != NULL )
        //    {
        //        buffer.setMarkerAtIndex( identifier, marker_index, size, item_size );
        //        memcpy( buffer.getpointerAtIndex( 0, *identifier ), ptr, size );
        //    }
    }

    // this function assumes that all sections are proportionnal
    void COLLADA_LOADER_WRITER::MakeInterleavedBuffer( CORE_DATA_BUFFER & buffer )
    {
        void * base = buffer.getpointerAtIndex( 0 );
        void * temporary = CORE_MEMORY_ALLOCATOR::Allocate( buffer.GetSize() );
        int sections = buffer.GetSections();
        memcpy(temporary, base, buffer.GetSize());
        
        int test = buffer.getSectionSize( 0 );
        test = buffer.getSectionItemOffset( 0 );
        
        test = buffer.getSectionSize( 0 ) / buffer.getSectionItemOffset(0);
        
        for ( int i = 0; i < test; i++ )
        {
            long section_offset = i * buffer.getSectionSize( 0 );
            
            for ( int j = 0; j < sections; j++ )
            {
                memcpy( base, (void *)((char *) temporary + section_offset), buffer.getSectionItemOffset(j) );
                section_offset += buffer.getSectionSize( j );
                base = (void *)((long) base + (long)buffer.getSectionItemOffset(j));
            }
        }
        
        CORE_MEMORY_ALLOCATOR_Free(temporary);
    }

    void COLLADA_LOADER_WRITER::ComputeMeshBoundingObject( const float * points, int points_count, GRAPHIC_MESH & mesh, int index_count, int * indices ) {
        
        gte::Vector3<double> * vector = new gte::Vector3<double>[points_count];
        
        for (int i = 0; i < points_count; i++ ) {
            
            vector[i][0] = points[i*3 + 0];
            vector[i][1] = points[i*3 + 1];
            vector[i][2] = points[i*3 + 2];
        }

        gte::MinimumVolumeBox3<double, double> mvb3(4);
        
        gte::OrientedBox3<double> minBox = mvb3( points_count, vector );
        
        CORE_MATH_VECTOR extent, position;
        CORE_MATH_QUATERNION orientation, orientation2;
        
        extent[0] = minBox.extent[0];
        extent[1] = minBox.extent[1];
        extent[2] = minBox.extent[2];
        extent[3] = 0.0f;
        
        position[0] = minBox.center[0];
        position[1] = minBox.center[1];
        position[2] = minBox.center[2];
        position[3] = 0.0f;
        
        // TODO:
        
        CORE_MATH_MATRIX mat;
        CORE_MATH_MATRIX mat2( CORE_MATH_MATRIX::Identity );
        
        
        // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToEuler/
        // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/
        
        float euler_x =  atan2f( minBox.axis[1][2], minBox.axis[2][2] );
        float euler_y =  atan2f( -minBox.axis[2][0], sqrtf( minBox.axis[2][1] * minBox.axis[2][1] + minBox.axis[2][2]*minBox.axis[2][2]) );
        float euler_z =  atan2f( minBox.axis[1][0], minBox.axis[0][0] );

        mat.GetRow( 0 )[0] = minBox.axis[0][0];
        mat.GetRow( 0 )[1] = minBox.axis[1][0];
        mat.GetRow( 0 )[2] = minBox.axis[2][0];
        mat.GetRow( 0 )[3] = 0.0f;
        
        mat.GetRow( 1 )[0] = minBox.axis[0][1];
        mat.GetRow( 1 )[1] = minBox.axis[1][1];
        mat.GetRow( 1 )[2] = minBox.axis[2][1];
        mat.GetRow( 1 )[3] = 0.0f;
        
        mat.GetRow( 2 )[0] = minBox.axis[0][2];
        mat.GetRow( 2 )[1] = minBox.axis[1][2];
        mat.GetRow( 2 )[2] = minBox.axis[2][2];
        mat.GetRow( 2 )[3] = 0.0f;
        
        mat.GetRow( 3 )[0] = 0.0f;
        mat.GetRow( 3 )[1] = 0.0f;
        mat.GetRow( 3 )[2] = 0.0f;
        mat.GetRow( 3 )[3] = 1.0f;
        
        /*mat2.XRotate( euler_x );
        mat2.YRotate( euler_y );
        mat2.ZRotate( euler_z );*/
        //printf("%f %f %f\n", euler_x* 180.0f/M_PI, euler_y* 180.0f/M_PI, euler_z* 180.0f/M_PI );
        
        orientation.FromMatrix( mat.GetRow(0) );
        //orientation2.ToMatrix( mat2.GetRow(0) );
        //orientation2.FromMatrix( mat2.GetRow(0) );
        
        mesh.GetBoundingShape().SetHalfDiagonal( extent * 0.5f );
        mesh.GetBoundingShape().SetPosition( CORE_MATH_VECTOR(0.0f, 0.0f, 0.0f, 1.0f ) );
        //mesh.GetBoundingShape().SetOrientation( orientation );
        
        delete [] vector;
    }

    /** When this method is called, the writer must write the geometry.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeGeometry ( const COLLADAFW::Geometry* geometry )
    {
        std::string
            mesh_name;
        
        mesh_name = geometry->getName();
        
        switch ( geometry->getType() )
        {
            case COLLADAFW::Geometry::GEO_TYPE_MESH:
            {
                static const CORE_HELPERS_IDENTIFIER
                    positions( "Positions" ),
                    normals( "Normals" ),
                    colors( "Colors" ),
                    tangents( "Tangents" ),
                    binormals( "Binormals" ),
                    uvcoords( "UVCoords" );
                int
                    buffer_size = 0,
                    section_count = 0;
                    const COLLADAFW::Mesh
                    * data = (COLLADAFW::Mesh *)geometry;
                
                if ( data->getMeshPrimitives().getCount() > 0 ) {
                    
                    const COLLADAFW::MeshPrimitiveArray * primitives = ( const COLLADAFW::MeshPrimitiveArray * ) &data->getMeshPrimitives();
                    
                    for ( int poly_count = 0; poly_count < primitives->getCount(); poly_count++ ) {
                        
                        GRAPHIC_MESH *
                            mesh = new GRAPHIC_MESH;
                        CORE_DATA_BUFFER
                            * index_buffer = new CORE_DATA_BUFFER();
                        CORE_DATA_BUFFER
                            * vertex_buffer = new CORE_DATA_BUFFER();
                        bool
                            hasPosition = ComputeBufferSizeForItem( buffer_size, section_count, data->getPositions() ),
                            hasNormals = ComputeBufferSizeForItem( buffer_size, section_count, data->getNormals() ),
                            hasUV = ComputeBufferSizeForItem( buffer_size, section_count, data->getUVCoords() ),
                            hasColors = false;//calculateBufferSizeForItem( buffer_size, section_count, data->getColors() );
                        int
                            vertex_size = 0;
                        
                        mesh->SetName( mesh_name.c_str() );
                        
                        {
                            // TODO: all vertices will have x-y-z components. when collada supports it, enable this
                            
                            mesh->SetVertexCoreBuffer( vertex_buffer );
                            
                            if ( hasPosition ) {
                                
                                mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Position );
                                
                                vertex_size += 4;
                            }
                            
                            if ( hasNormals ) {
                                mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Normal );
                                
                                vertex_size += 4;
                            }
                            
                            if ( hasUV ) {
                                mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Texcoord0 );
                                
                                vertex_size += 2;
                            }
                            
                            if ( hasColors ) {
                                mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Color );
                                
                                vertex_size += 4;
                            }
                            
                            if ( data->getMeshPrimitives().getCount() > 0 ) {
                                
                                // TODO:
                            }
                            
                            if( hasUV && hasNormals ) {
                                
                                vertex_size+=6;
                                
                                mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Tangents );
                                mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_Bitangents );
                                
                                //vertex_size += 6;
                            }
                            
                            //unsigned int vertices_count = (int) (data->getPositions().getValuesCount() / 3);
                            
                            mesh->SetIndexCoreBuffer( index_buffer );
                        }
                        
                        int accumulated_index = 0;
                        
                        const COLLADAFW::MeshPrimitive * prim = ( const COLLADAFW::MeshPrimitive * ) primitives->getData()[poly_count];
                        
                        const COLLADAFW::UIntValuesArray & pos_indices = prim->getPositionIndices();
                        
                        const COLLADAFW::IndexList * index_list;
                        
                        if ( hasUV ) {
                            
                            index_list = *(prim->getUVCoordIndicesArray().getData());
                        }
                        
                        if ( mesh->CurrenGeometrytTable != NULL ) {
                            
                            CORE_MEMORY_ALLOCATOR_Free( mesh->CurrenGeometrytTable );
                        }
                        
                        mesh->CurrenGeometrytTable = (GRAPHIC_MESH::VERTEX_ELEMENT *) CORE_MEMORY_ALLOCATOR::Allocate( sizeof( GRAPHIC_MESH::VERTEX_ELEMENT ) * 3 * prim->getFaceCount());
                        index_buffer->Initialize( (unsigned int) prim->getFaceCount() * 3 * 4 );
                        mesh->CurrenGeometrytTableSize = (int) (3 * prim->getFaceCount());
                        
                        //memcpy((void *)index_buffer->getpointerAtIndex( 0 ), (void *)prim->getPositionIndices().getData(), sizeof(unsigned int) * prim->getPositionIndices().getCount() );
                        
                        for (int face = 0; face < prim->getFaceCount(); face++ ) {
                            
                            for ( int v_index = 0; v_index < prim->getGroupedVerticesVertexCount( face ); v_index++ ) {
                                const COLLADAFW::UIntValuesArray & arr = prim->getPositionIndices();
                                
                                //Need to take stride in account
                                /*mesh->CurrenGeometrytTable[ accumulated_index ].position[0] = *(data->getPositions().getFloatValues()->getData() + accumulated_index * 3 );
                                mesh->CurrenGeometrytTable[ accumulated_index ].position[1] = *(data->getPositions().getFloatValues()->getData()+ accumulated_index * 3 + 1);
                                mesh->CurrenGeometrytTable[ accumulated_index ].position[2] = *(data->getPositions().getFloatValues()->getData()+ accumulated_index * 3 + 2);
                                mesh->CurrenGeometrytTable[ accumulated_index ].position[3] = 1.0f;*/
                                
                                memcpy((void *)index_buffer->getpointerAtIndex( accumulated_index ), &accumulated_index, sizeof(unsigned int));
                                
                                mesh->CurrenGeometrytTable[ accumulated_index ].position[0] = *(data->getPositions().getFloatValues()->getData()+ prim->getPositionIndices()[accumulated_index] * 3 );
                                mesh->CurrenGeometrytTable[ accumulated_index ].position[1] = *(data->getPositions().getFloatValues()->getData()+ prim->getPositionIndices()[accumulated_index] * 3 + 1);
                                mesh->CurrenGeometrytTable[ accumulated_index ].position[2] = *(data->getPositions().getFloatValues()->getData()+ prim->getPositionIndices()[accumulated_index] * 3 + 2);
                                mesh->CurrenGeometrytTable[ accumulated_index ].position[3] = 1.0f;
                                
                                /*printf( "%d\n", prim->getPositionIndices()[accumulated_index] );
                                printf( "%f\t%f\t%f\t\n", mesh->CurrenGeometrytTable[ accumulated_index ].position[0], mesh->CurrenGeometrytTable[ accumulated_index ].position[1], mesh->CurrenGeometrytTable[ accumulated_index ].position[2] );*/
                                
                                mesh->CurrenGeometrytTable[ accumulated_index ].vertex_index = pos_indices[ accumulated_index ];
                                
                                if ( hasNormals ) {
                                    const COLLADAFW::UIntValuesArray & norm_indices = prim->getNormalIndices();
                                    
                                    mesh->CurrenGeometrytTable[ accumulated_index ].Normals[0] = *(data->getNormals().getFloatValues()->getData()+ prim->getNormalIndices()[accumulated_index] * 3);
                                    mesh->CurrenGeometrytTable[ accumulated_index ].Normals[1] = *(data->getNormals().getFloatValues()->getData()+ prim->getNormalIndices()[accumulated_index] * 3 + 1);
                                    mesh->CurrenGeometrytTable[ accumulated_index ].Normals[2] = *(data->getNormals().getFloatValues()->getData()+ prim->getNormalIndices()[accumulated_index] * 3 + 2);
                                    mesh->CurrenGeometrytTable[ accumulated_index ].Normals[3] = 0.0f;
                                }
                                
                                if ( hasUV ) {
                                    
                                    const COLLADAFW::UIntValuesArray & uv_indices = prim->getUVCoordIndices(0)->getIndices();
                                    
                                    mesh->CurrenGeometrytTable[ accumulated_index ].UV0[0] = *(data->getUVCoords().getFloatValues()->getData()+ uv_indices[accumulated_index ] * 2 );
                                    mesh->CurrenGeometrytTable[ accumulated_index ].UV0[1] = *(data->getUVCoords().getFloatValues()->getData()+ uv_indices[accumulated_index ] * 2 + 1);
                                    
                                    //printf( "%f\t%f\n", mesh->CurrenGeometrytTable[ accumulated_index ].UV0[0], mesh->CurrenGeometrytTable[ accumulated_index ].UV0[1] );
                                }
                                
                                ++accumulated_index;
                            }
                            
                            //@see http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
                            if ( hasUV && hasNormals ) { // normal_mapping
                                // Shortcuts for vertices
                                CORE_MATH_VECTOR v0(  mesh->CurrenGeometrytTable[ accumulated_index - 3 ].position );
                                CORE_MATH_VECTOR v1( mesh->CurrenGeometrytTable[ accumulated_index - 2 ].position );
                                CORE_MATH_VECTOR v2( mesh->CurrenGeometrytTable[ accumulated_index - 1 ].position );
                                
                                // Shortcuts for UVs
                                CORE_MATH_VECTOR uv0( mesh->CurrenGeometrytTable[ accumulated_index - 3 ].UV0[0], mesh->CurrenGeometrytTable[ accumulated_index - 3 ].UV0[1] );
                                CORE_MATH_VECTOR uv1( mesh->CurrenGeometrytTable[ accumulated_index - 2 ].UV0[0], mesh->CurrenGeometrytTable[ accumulated_index - 2 ].UV0[1] );
                                CORE_MATH_VECTOR uv2( mesh->CurrenGeometrytTable[ accumulated_index - 1 ].UV0[0], mesh->CurrenGeometrytTable[ accumulated_index - 1 ].UV0[1] );
                                
                                // Edges of the triangle : postion delta
                                CORE_MATH_VECTOR deltaPos1 = v1-v0;
                                CORE_MATH_VECTOR deltaPos2 = v2-v0;
                                
                                // UV delta
                                CORE_MATH_VECTOR deltaUV1 = uv1-uv0;
                                CORE_MATH_VECTOR deltaUV2 = uv2-uv0;
                                
                                float r = 1.0f / (deltaUV1[0] * deltaUV2[1] - deltaUV1[1] * deltaUV2[0]);
                                
                                CORE_MATH_VECTOR tangent = (deltaPos1 * deltaUV2[1]   - deltaPos2 * deltaUV1[1])*r;
                                CORE_MATH_VECTOR bitangent = (deltaPos2 * deltaUV1[0]   - deltaPos1 * deltaUV2[0])*r;
                                
                                memcpy( mesh->CurrenGeometrytTable[ accumulated_index - 3].tangents, &tangent[0], 12);
                                memcpy( mesh->CurrenGeometrytTable[ accumulated_index - 2].tangents, &tangent[0], 12);
                                memcpy( mesh->CurrenGeometrytTable[ accumulated_index - 1].tangents, &tangent[0], 12);
                                
                                memcpy( mesh->CurrenGeometrytTable[ accumulated_index - 3].binormal, &bitangent[0], 12);
                                memcpy( mesh->CurrenGeometrytTable[ accumulated_index - 2].binormal, &bitangent[0], 12);
                                memcpy( mesh->CurrenGeometrytTable[ accumulated_index - 1].binormal, &bitangent[0], 12);
                            }
                        }
                        
                        mesh->CurrenGeometrytTableSize = accumulated_index;
                        
                        
                        vertex_buffer->Initialize( accumulated_index * vertex_size * sizeof( float ), 1 );
                        
                        ComputeMeshBoundingObject( data->getPositions().getFloatValues()->getData(), (int) data->getPositions().getFloatValues()->getCount() / 3, *mesh, (int) prim->getFaceCount() * 3, (int *) index_buffer->getpointerAtIndex(0,0) );
                        
                        for (int i = 0; i< accumulated_index; i++ ) {
                            
                            int offset = 0;
                            
                            if ( hasPosition ) {
                                
                                memcpy( (void *)(vertex_buffer->getpointerAtIndex( i * vertex_size )), (void *) ( &mesh->CurrenGeometrytTable[ i ].position[0]), 16 );
                                offset+= 4;
                            }
                            
                            if ( hasNormals ) {
                                
                                memcpy( (void *)(vertex_buffer->getpointerAtIndex( i * vertex_size + offset)), (void *) ( &mesh->CurrenGeometrytTable[ i ].Normals[0]), 16 );
                                offset+= 4;
                            }
                            
                            if ( hasUV ) {
                                
                                memcpy( (void *)(vertex_buffer->getpointerAtIndex( i * vertex_size + offset)), (void *) ( &mesh->CurrenGeometrytTable[ i ].UV0[0]), 8 );
                                offset+= 2;
                            }
                            
                            if ( hasColors ) {
                                
                            }
                            
                            if( hasUV && hasNormals ) {
                                //WHY THIS????
                                memcpy( (void *)(vertex_buffer->getpointerAtIndex( i * vertex_size + offset)), (void *) ( &mesh->CurrenGeometrytTable[ i ].tangents[0]), 12 );
                                offset+= 3;
                                
                                memcpy( (void *)(vertex_buffer->getpointerAtIndex( i * vertex_size + offset)), (void *) ( &mesh->CurrenGeometrytTable[ i ].binormal[0]), 12 );
                                offset+= 3;
                            }
                        }
                        
                        graphicObject->AddNewMesh( mesh );
                    }
                }
                
                break;
            }
            case COLLADAFW::Geometry::GEO_TYPE_SPLINE:
            {
                break;
            }
            case COLLADAFW::Geometry::GEO_TYPE_CONVEX_MESH:
            {
                break;
            }
            default:
            {
                break;
            }
        }
        
        return true;
    }

    /** When this method is called, the writer must write the material.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeMaterial( const COLLADAFW::Material* material )
    {
        for (int i = 0; i < graphicObject->GetMeshTable().size(); i++) {
            graphicObject->GetMeshTable()[i];
            
            if ( graphicObject->GetMeshTable()[i]->GetName() == material->getName() ) {
                
                
            }
        }
        
        return true;
    }

    /** When this method is called, the writer must write the effect.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeEffect( const COLLADAFW::Effect* effect )
    {
        return true;
    }

    /** When this method is called, the writer must write the camera.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeCamera( const COLLADAFW::Camera* camera )
    {
        return true;
    }

    /** When this method is called, the writer must write the image.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeImage( const COLLADAFW::Image* image )
    {
        return true;
    }

    /** When this method is called, the writer must write the light.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeLight( const COLLADAFW::Light* light )
    {
        return true;
    }

    /** When this method is called, the writer must write the Animation.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeAnimation( const COLLADAFW::Animation* animation )
    {
        switch ( animation->getAnimationType() ) {
                
            case COLLADAFW::Animation::AnimationType::ANIMATION_CURVE : {
                
                const COLLADAFW::AnimationCurve *
                    curve = (COLLADAFW::AnimationCurve*)animation;
                GRAPHIC_MESH_ANIMATION_JOINT *
                    skeleton = new GRAPHIC_MESH_ANIMATION_JOINT();
                
                unsigned int size = (int) this->animatedJoints.size();
                
                graphicObject->GetAnimationTable()[0]->GetTimeTableBuffer().Initialize((int) (curve->getInputValues().getFloatValues()->getCount() * sizeof( float) ) );
                
                memcpy( graphicObject->GetAnimationTable()[0]->GetTimeTableBuffer().getpointerAtIndex(0, 0), curve->getInputValues().getFloatValues()->getData(), curve->getInputValues().getFloatValues()->getCount() * sizeof(float) );
                
                animatedJoints[ animation->getUniqueId().getObjectId() ] = skeleton;
                printf( "joint_index %d %s\n", animation->getUniqueId().getObjectId(), animation->getName().c_str() );
                
                int dimension = (int) curve->getOutDimension();
                
                if ( curve->getInPhysicalDimension() == COLLADAFW::PhysicalDimension::PHYSICAL_DIMENSION_TIME ) {
                    
                    int animation_values_count = (int) curve->getInputValues().getValuesCount();
                    
                    skeleton->Initialize(dimension, animation_values_count);
                    skeleton->SetName(animation->getName().c_str() );
                    
                    if ( curve->getOutputValues().getType() == COLLADAFW::FloatOrDoubleArray::DATA_TYPE_FLOAT ) {
                        
                        const float * floatPointer = curve->getOutputValues().getFloatValues()->getData();
                        
                        memcpy((void *) skeleton->GetMatrixBuffer(), (const void *) floatPointer, animation_values_count * dimension *sizeof(float));
                        
                        CORE_MATH_POSE * buffer = skeleton->GetPoseBuffer();
                        
                        for( int i = 0; i < animation_values_count; i++) {
                            
                            CORE_MATH_POSE temporary;
                            CORE_MATH_MATRIX mat(floatPointer + (i * 16));
                            
                            temporary.FromMatrix( mat );
                            
                            buffer->CopyFrom( temporary );
                            buffer->GetOrientation().Normalize();
                            buffer++;
                        }
                        
                        buffer = skeleton->GetPoseBuffer();
                        
                        for( int i = 0; i < animation_values_count; i++) {
                            
                            CORE_MATH_MATRIX mat;
                            (*buffer).ToMatrix(mat);
                            CORE_MATH_MATRIX mat2(floatPointer + (i * 16));
                            
                            for (int j = 0; j < 16; j++ ) {
                                
                                if ( mat[j] - mat2[j] > 0.03f ) {
                                    
                                    //CORE_RUNTIME_Abort();
                                }
                            }
                            
                            buffer++;
                        }
                    }
                    else {
                        
                        assert( "TODO" );
                    }
                }
                else {
                    
                    assert( "TODO" );
                }
                
                break;
            }
                
            case COLLADAFW::Animation::AnimationType::ANIMATION_FORMULA : {
                
                assert( "TODO" );
                
                break;
            }
                
            default:
                assert( "TODO" );
                break;
        }
        
        return true;
    }

    /** When this method is called, the writer must write the AnimationList.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeAnimationList( const COLLADAFW::AnimationList* animationList )
    {
        return true;
    }

    /** When this method is called, the writer must write the skin controller data.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeSkinControllerData( const COLLADAFW::SkinControllerData* skinControllerData ) {
        // read and write weights to vertex buffer data
        
        int unid = (int) skinControllerData->getUniqueId().getObjectId();
        
        GRAPHIC_MESH * mesh = graphicObject->GetMeshTable()[unid];
        
        CORE_DATA_BUFFER * buffer = new CORE_DATA_BUFFER();
        mesh->SetVertexCoreBuffer(buffer);
        
        GRAPHIC_MESH_ANIMATION *
        animation = new GRAPHIC_MESH_ANIMATION();
        
        animation->SetName( skinControllerData->getName() );
        
        graphicObject->GetAnimationTable().resize(skinControllerData->getUniqueId().getObjectId() + 1 );
        graphicObject->GetAnimationTable()[ skinControllerData->getUniqueId().getObjectId() ] = animation;
        graphicObject->GetAnimationTable()[ skinControllerData->getUniqueId().getObjectId()]->GetJointTable().resize( skinControllerData->getJointsCount() );
        animatedJoints.resize( skinControllerData->getJointsCount() );
        
        //animationTable.resize( skinControllerData->getUniqueId().getObjectId() + 1 );
        //animationTable[ skinControllerData->getUniqueId().getObjectId() ] = animation;
        
        float bind_shape_matrix[ 16 ];
        
        for ( int i = 0; i < 16; i++ ) {
            
            bind_shape_matrix[i] = (float) skinControllerData->getBindShapeMatrix().getElement(i);
        }
        
        int size = (int) skinControllerData->getInverseBindMatrices().getCount() * 16 * sizeof(float);
        float * inverse_bind_matrices = (float*)CORE_MEMORY_ALLOCATOR::Allocate(size);
        
        for ( int j = 0; j < skinControllerData->getInverseBindMatrices().getCount(); j++ ) {
            
            for ( int i = 0; i < 16; i++ ) {
                
                inverse_bind_matrices[j * 16 + i] = (float) skinControllerData->getInverseBindMatrices()[j].getElement(i);
            }
        }
        
        animation->GetInverseBindMatrixes().InitializeWithMemory(size, 0, inverse_bind_matrices);
        animation->SetBindShapeMatrix(bind_shape_matrix);
        

        unsigned int BASE_JOINTS_PER_VERTEX = 0;

        BASE_JOINTS_PER_VERTEX = 4;
        
        
        //TODO: Why????
        unsigned int joint_index_offset = 1;
        
        int new_buffer_size = buffer->GetSize()
        + (int) ( BASE_JOINTS_PER_VERTEX * skinControllerData->getJointsPerVertex().getCount()* sizeof( float ) )
        + (int) ( BASE_JOINTS_PER_VERTEX * skinControllerData->getJointsPerVertex().getCount()* sizeof( unsigned int ) );
        
        int stride = 0;
        
        mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_SkinWeight );
        mesh->ActivateBufferComponent( GRAPHIC_SHADER_BIND_JointIndices );
        
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_Position )
            stride+= 4;
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_Normal )
            stride+= 4;
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_Color )
            stride+= 4;
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_Texcoord0 )
            stride+= 2;
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_Texcoord1 )
            stride+= 2;
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_Tangents )
            stride+= 3;
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_Bitangents )
            stride+= 3;
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_JointIndices )
            stride+= BASE_JOINTS_PER_VERTEX;
        if ( mesh->GetVertexComponent() & GRAPHIC_SHADER_BIND_SkinWeight )
            stride+= BASE_JOINTS_PER_VERTEX;
        
        const int final_stride = stride * sizeof(float);
        
        assert ( new_buffer_size > buffer->GetSize() );
        
        void * alternate_new_buffer = CORE_MEMORY_ALLOCATOR::Allocate( mesh->CurrenGeometrytTableSize * final_stride );
        
        //loop through all joints and weights
        int joints_per_vertex_total = (int) skinControllerData->getJointsPerVertex().getCount();
        
        for ( int i = 0; i < joints_per_vertex_total; i++ ) {
            
            int jointsPerVertex = *((unsigned int *) skinControllerData->getJointsPerVertex().getData() + i);
            
            for (int new_geometry_index = 0; new_geometry_index < mesh->CurrenGeometrytTableSize; new_geometry_index++ ) {
                
                if ( mesh->CurrenGeometrytTable[ new_geometry_index ].vertex_index == i ) {
                    
                    mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[0] = 0.0f;
                    mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[1] = 0.0f;
                    mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[2] = 0.0f;
                    mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[3] = 0.0f;
                    
                    for( int joint_per_vertex_index = 0; joint_per_vertex_index < jointsPerVertex; joint_per_vertex_index++ ) {
                        
                        if ( joint_per_vertex_index > 3 ) {
                            continue;
                        }
                        
                        mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[joint_per_vertex_index] = *(skinControllerData->getJointIndices().getData() +( joint_index_offset + joint_per_vertex_index ));
                        
                        assert( (int) mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[joint_per_vertex_index] == 0.0f || (int) mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[joint_per_vertex_index] >= 1.0f );
                        
                        mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[joint_per_vertex_index] = *(skinControllerData->getWeights().getFloatValues()->getData() + joint_index_offset + joint_per_vertex_index );
                        
                        /*printf( "first index %d %d %d, next index, %d %d %d\n", (int) mesh->CurrenGeometrytTable[ new_geometry_index - joint_per_vertex_index ].joint_index[0], (int) mesh->CurrenGeometrytTable[ new_geometry_index - joint_per_vertex_index ].joint_index[1], (int) mesh->CurrenGeometrytTable[ new_geometry_index - joint_per_vertex_index ].joint_index[2],
                               (int) mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[0], (int) mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[1],
                               (int) mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[2]);
                        
                        if (  joint_per_vertex_index > 0 && joint_per_vertex_index == jointsPerVertex - 1 ) {
                            if ( abs(mesh->CurrenGeometrytTable[ new_geometry_index - joint_per_vertex_index ].joint_index[0] - mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[0] ) > 5 ||
                                ( mesh->CurrenGeometrytTable[ new_geometry_index -1 ].joint_weights[1] > 0.0f && mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[1] > 0.0f && (
                                abs(mesh->CurrenGeometrytTable[ new_geometry_index - joint_per_vertex_index ].joint_index[1] - mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[1] ) > 5 )) ||
                                ((mesh->CurrenGeometrytTable[ new_geometry_index -1 ].joint_weights[2] > 0.0f && mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[2] > 0.0f && (
                                abs(mesh->CurrenGeometrytTable[ new_geometry_index - joint_per_vertex_index ].joint_index[2] - mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[2] ) > 5) ) ) ) {
                                
                                printf( "I sense a great disturbance in the force\n");
                            }
                        }*/
                        
                        assert( (int) mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[0] > 0 );
                        
                        if (mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[2] <= 0.0f ) {
                            
                            mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[2] = 0.0f;
                        }
                        
                        if (mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[0] +
                            mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[1] >= 1.0f) {
                            
                            mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[2] = 0.0f;
                        }
                        
                        
                    }
                    
                    //printf( "%f %f %f\n", mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[0], mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[1], mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[2]);
                    
                    //printf( "%d %d %d\n", (int)mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[0], (int)mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[1], (int)mesh->CurrenGeometrytTable[ new_geometry_index ].joint_index[2]);
                    //assert( mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[0] + mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[1] + mesh->CurrenGeometrytTable[ new_geometry_index ].joint_weights[2] <= 1.01f);
                }
            }
                
            joint_index_offset += jointsPerVertex;
        }
        
        int off_stride = final_stride / sizeof( int );
        
        for (int v_index = 0; v_index < mesh->CurrenGeometrytTableSize; v_index++ ) {
            
            memcpy( (void*)((int*)alternate_new_buffer + v_index * off_stride ),        (void*)mesh->CurrenGeometrytTable[v_index].position,        16 );
            memcpy( (void*)((int*)alternate_new_buffer + v_index * off_stride + 4 ),    (void*)mesh->CurrenGeometrytTable[v_index].Normals,         16 );
            memcpy( (void*)((int*)alternate_new_buffer + v_index * off_stride + 8),     (void*)mesh->CurrenGeometrytTable[v_index].UV0,             8 );
            
            memcpy( (void*)((int*)alternate_new_buffer + v_index * off_stride + 10),     (void*)mesh->CurrenGeometrytTable[v_index].joint_weights,     16 );
            memcpy( (void*)((int*)alternate_new_buffer + v_index * off_stride + 14),     (void*)mesh->CurrenGeometrytTable[v_index].joint_index,   16 );
            
            memcpy( (void*)((int*)alternate_new_buffer + v_index * off_stride + 18 ),   (void*)mesh->CurrenGeometrytTable[v_index].tangents,        12 );
            memcpy( (void*)((int*)alternate_new_buffer + v_index * off_stride + 21),    (void*)mesh->CurrenGeometrytTable[v_index].binormal,        12 );
            
            //assert( mesh->CurrenGeometrytTable[v_index].joint_index[0] != 0.0f && mesh->CurrenGeometrytTable[v_index].joint_weights[0] != 0.0f );
            //printf("windex %d %d %d\n", (int)mesh->CurrenGeometrytTable[v_index].joint_index[0], (int)mesh->CurrenGeometrytTable[v_index].joint_index[1], (int)mesh->CurrenGeometrytTable[v_index].joint_index[2]);
            
            //assert( mesh->CurrenGeometrytTable[v_index].joint_index[0] != 0.0f && mesh->CurrenGeometrytTable[v_index].joint_weights[0] != 0.0f );
            //printf("windex %d %d %d\n", (int)mesh->CurrenGeometrytTable[v_index].joint_index[0], (int)mesh->CurrenGeometrytTable[v_index].joint_index[1], (int)mesh->CurrenGeometrytTable[v_index].joint_index[2]);
            
            /*SERVICE_LOGGER_Error( "%f %f %f\n", mesh->CurrenGeometrytTable[v_index].tangents[0], mesh->CurrenGeometrytTable[v_index].tangents[1], mesh->CurrenGeometrytTable[v_index].tangents[2] );
            
            SERVICE_LOGGER_Error( "%f %f %f\n", mesh->CurrenGeometrytTable[v_index].binormal[0], mesh->CurrenGeometrytTable[v_index].binormal[1], mesh->CurrenGeometrytTable[v_index].binormal[2] );*/
        }
        
        buffer->Finalize();
        
        //buffer.InitializeWithMemory( new_buffer_size, 1, new_buffer );
        buffer->InitializeWithMemory( mesh->CurrenGeometrytTableSize * final_stride, 1, alternate_new_buffer );
        
        /*for (int vi =0; vi < mesh->CurrenGeometrytTableSize; vi++) {
            
            for (int vj =vi; vj < mesh->CurrenGeometrytTableSize; vj++) {
                
                if ( vi  != vj) {
                    bool equal = mesh->CurrenGeometrytTable[vi].binormal[0] == mesh->CurrenGeometrytTable[vj].binormal[0] && mesh->CurrenGeometrytTable[vi].binormal[1] == mesh->CurrenGeometrytTable[vj].binormal[1] && mesh->CurrenGeometrytTable[vi].binormal[2] == mesh->CurrenGeometrytTable[vj].binormal[2] &&
                        mesh->CurrenGeometrytTable[vi].joint_index[0] == mesh->CurrenGeometrytTable[vj].joint_index[0] && mesh->CurrenGeometrytTable[vi].joint_index[1] == mesh->CurrenGeometrytTable[vj].joint_index[1] && mesh->CurrenGeometrytTable[vi].joint_index[2] == mesh->CurrenGeometrytTable[vj].joint_index[2] &&
                    mesh->CurrenGeometrytTable[vi].joint_weights[0] == mesh->CurrenGeometrytTable[vj].joint_weights[0] && mesh->CurrenGeometrytTable[vi].joint_weights[1] == mesh->CurrenGeometrytTable[vj].joint_weights[1] && mesh->CurrenGeometrytTable[vi].joint_weights[2] == mesh->CurrenGeometrytTable[vj].joint_weights[2] &&
                    mesh->CurrenGeometrytTable[vi].Normals[0] == mesh->CurrenGeometrytTable[vj].Normals[0] && mesh->CurrenGeometrytTable[vi].Normals[1] == mesh->CurrenGeometrytTable[vj].Normals[1] && mesh->CurrenGeometrytTable[vi].Normals[2] == mesh->CurrenGeometrytTable[vj].Normals[2] &&
                    mesh->CurrenGeometrytTable[vi].position[0] == mesh->CurrenGeometrytTable[vj].position[0] && mesh->CurrenGeometrytTable[vi].position[1] == mesh->CurrenGeometrytTable[vj].position[1] && mesh->CurrenGeometrytTable[vi].position[2] == mesh->CurrenGeometrytTable[vj].position[2] &&
                    mesh->CurrenGeometrytTable[vi].tangents[0] == mesh->CurrenGeometrytTable[vj].tangents[0] && mesh->CurrenGeometrytTable[vi].tangents[1] == mesh->CurrenGeometrytTable[vj].tangents[1] && mesh->CurrenGeometrytTable[vi].tangents[2] == mesh->CurrenGeometrytTable[vj].tangents[2] &&
                    mesh->CurrenGeometrytTable[vi].UV0[0] == mesh->CurrenGeometrytTable[vi].UV0[0] && mesh->CurrenGeometrytTable[vi].UV0[1] == mesh->CurrenGeometrytTable[vi].UV0[1];
                    
                    if (equal) {
                        printf( "Dupplicated vertex at index : %d %d \n", vi, vj);
                    }
                }
            }
        }*/
        
        return true;
    }
    
    /** When this method is called, the writer must write the controller.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeController( const COLLADAFW::Controller* controller )
    {
        COLLADAFW::SkinController *
            skin_controller = (COLLADAFW::SkinController *) controller;
        
        GRAPHIC_MESH_ANIMATION::PTR animation = graphicObject->GetAnimationTable()[ controller->getUniqueId().getObjectId() ];
        
        animation->GetJointTable().resize( skin_controller->getJoints().getCount() );
        indexTable.resize( skin_controller->getJoints().getCount() );
        
        for ( int i = 0; i <skin_controller->getJoints().getCount(); i++  ) {
            
            int object_id = (int) skin_controller->getJoints().getData()[i].getObjectId();
            
            printf( "object id : %d\n", object_id );
            indexTable[i] = object_id;
            
            if ( object_id < animatedJoints.size() ) {
                
                animation->GetJointTable()[ object_id ] = animatedJoints[ object_id ];
            }
            else {
                
                animation->GetJointTable()[i] = NULL;
            }
        }
        
        return true;
    }

    /** When this method is called, the writer must write the formulas. All the formulas of the entire
     COLLADA file are contained in @a formulas.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeFormulas( const COLLADAFW::Formulas* formulas )
    {
        return true;
    }

    /** When this method is called, the writer must write the kinematics scene.
     @return The writer should return true, if writing succeeded, false otherwise.*/
    bool COLLADA_LOADER_WRITER::writeKinematicsScene( const COLLADAFW::KinematicsScene* kinematicsScene )
    {
        return true;
    }

    GRAPHIC_MESH_LOADER_COLLADA::GRAPHIC_MESH_LOADER_COLLADA( void )
    {
    }

    GRAPHIC_MESH_LOADER_COLLADA::~GRAPHIC_MESH_LOADER_COLLADA() {
        
        
    }

    void GRAPHIC_MESH_LOADER_COLLADA::LoadFile( GRAPHIC_OBJECT & meshToLoad, const CORE_FILESYSTEM_PATH & file_path )
    {
        COLLADA_LOADER_ERROR_HANDLER errorHandler;
        COLLADA_LOADER_WRITER writer;
        COLLADASaxFWL::Loader loader( &errorHandler );
        COLLADAFW::Root root(&loader, &writer);
        
        writer.graphicObject = &meshToLoad;
        
        
        // Load scene graph
        bool success = root.loadDocument( file_path.GetPath() );
        
        if ( ! success ) {
            
        }
        
    }
#endif
