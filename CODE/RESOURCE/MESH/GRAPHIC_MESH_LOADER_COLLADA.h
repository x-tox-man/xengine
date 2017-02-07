//
//  GRAPHIC_MESH_LOADER_COLLADA.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_LOADER_COLLADA__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_LOADER_COLLADA__

#if __COMPILE_WITH__COLLADA__
    #include "CORE_HELPERS_CLASS.h"
    #include "GRAPHIC_OBJECT.h"
    #include "GRAPHIC_MESH.h"
    #include "CORE_HELPERS_IDENTIFIER.h"
    #include "COLLADASaxFWLIErrorHandler.h"
    #include "COLLADAFW.h"
    #include "GRAPHIC_MESH_SUB_SKELETON.h"
    #include "CORE_FILESYSTEM.h"

    union PRIMITIVE_LIST
    {
        float * floatArray;
        int * intArray;
    };

    struct TECHNIQUE_COMMON
    {
        int
        count,
        stride;
        std::string id;
    };

    struct INPUT_VALUE
    {
        std::string
            source,
            semantic;
    };

    struct VERTICES_VALUE
    {
        INPUT_VALUE input;
        std::string id;
    };

    struct SOURCE
    {
        TECHNIQUE_COMMON technique;
        PRIMITIVE_LIST
            primitive,
            coordinates;
        int
            primitiveCount,
            coordinateCount;
    };

    class COLLADA_LOADER_ERROR_HANDLER : public COLLADASaxFWL::IErrorHandler
    {
        bool virtual handleError(const COLLADASaxFWL::IError* error);
        bool hasError() { return mError; }
        bool mError;
    XS_CLASS_END

    class COLLADA_LOADER_WRITER : public COLLADAFW::IWriter
    {
        public:
        COLLADA_LOADER_WRITER();
        
        virtual    ~COLLADA_LOADER_WRITER() {};
        
        void fillSkeleton(
            std::vector<GRAPHIC_MESH_ANIMATION_JOINT *> & joints,
            int base_index,
            int * index_table,
            COLLADAFW::Node * node,
            GRAPHIC_MESH_SUB_SKELETON & skeleton );
        
        virtual void cancel(const COLLADAFW::String& errorMessage);
        
        /** This is the method called. The writer hast to prepare to receive data.*/
        virtual void start();
        
        /** This method is called after the last write* method. No other methods will be called after this.*/
        virtual void finish();
        
        /** When this method is called, the writer must write the global document asset.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeGlobalAsset ( const COLLADAFW::FileInfo* asset );
        
        /** When this method is called, the writer must write the scene.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeScene ( const COLLADAFW::Scene* scene );
        
        /** When this method is called, the writer must write the entire visual scene.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeVisualScene ( const COLLADAFW::VisualScene* visualScene );
        
        /** When this method is called, the writer must handle all nodes contained in the
         library nodes.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeLibraryNodes ( const COLLADAFW::LibraryNodes* libraryNodes );
        
        /** When this method is called, the writer must write the geometry.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeGeometry ( const COLLADAFW::Geometry* geometry );
        
        /** When this method is called, the writer must write the material.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeMaterial( const COLLADAFW::Material* material );
        
        /** When this method is called, the writer must write the effect.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeEffect( const COLLADAFW::Effect* effect );
        
        /** When this method is called, the writer must write the camera.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeCamera( const COLLADAFW::Camera* camera );
        
        /** When this method is called, the writer must write the image.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeImage( const COLLADAFW::Image* image );
        
        /** When this method is called, the writer must write the light.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeLight( const COLLADAFW::Light* light );
        
        /** When this method is called, the writer must write the Animation.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeAnimation( const COLLADAFW::Animation* animation );
        
        /** When this method is called, the writer must write the AnimationList.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeAnimationList( const COLLADAFW::AnimationList* animationList );
        
        /** When this method is called, the writer must write the skin controller data.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeSkinControllerData( const COLLADAFW::SkinControllerData* skinControllerData );
        
        /** When this method is called, the writer must write the controller.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeController( const COLLADAFW::Controller* controller );
        
        /** When this method is called, the writer must write the formulas. All the formulas of the entire
         COLLADA file are contained in @a formulas.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeFormulas( const COLLADAFW::Formulas* formulas );
        
        /** When this method is called, the writer must write the kinematics scene.
         @return The writer should return true, if writing succeeded, false otherwise.*/
        virtual bool writeKinematicsScene( const COLLADAFW::KinematicsScene* kinematicsScene );
        
        GRAPHIC_OBJECT * graphicObject;
        
    private:
        bool ComputeBufferSizeForItem( int & buffer_size, int & section_count, const COLLADAFW::FloatOrDoubleArray & array );
        void ComputeMeshBoundingObject( const float * points, int size, GRAPHIC_MESH & mesh, int index_count, int * indices );
        void CopyVertexDataToBuffer( const COLLADAFW::FloatOrDoubleArray & array, const CORE_HELPERS_IDENTIFIER * identifier, CORE_DATA_BUFFER & buffer, int marker_index, int vertices_count );
        void MakeInterleavedBuffer( CORE_DATA_BUFFER & buffer );
        
    XS_CLASS_END

    XS_CLASS_BEGIN( GRAPHIC_MESH_LOADER_COLLADA )
    public:
        GRAPHIC_MESH_LOADER_COLLADA();
        virtual    ~GRAPHIC_MESH_LOADER_COLLADA();
        
        void LoadFile( GRAPHIC_OBJECT & meshToLoad, const CORE_FILESYSTEM_PATH & file_path );
        
    private:

        GRAPHIC_OBJECT * graphicObject;
        
        static const CORE_HELPERS_IDENTIFIER
            VertexSemanticIdentifier,
            NormalSemanticItentifier;
        
    XS_CLASS_END
#endif
        
#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_LOADER_COLLADA__) */
