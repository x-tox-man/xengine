//
//  GRAPHIC_OBJECT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_SHADER_PROGRAM_DATA_PROXY.h"
#include "GRAPHIC_MESH_ANIMATION_JOINT.h"
#include "GRAPHIC_MESH_ANIMATION.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "GRAPHIC_SYSTEM.h"
#include "RESOURCE.h"
#include "RESOURCE_TYPE.h"
#include "CORE_HELPERS_COLOR.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_OBJECT_RENDER_OPTIONS.h"
#include "GRAPHIC_SHADER_EFFECT.h"

class GRAPHIC_MESH;
class GRAPHIC_OBJECT;
class GRAPHIC_OBJECT_RESOURCE_LOADER;

typedef RESOURCE< GRAPHIC_OBJECT, GRAPHIC_OBJECT_RESOURCE_LOADER > GR_O_ANCESTOR_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_OBJECT, GR_O_ANCESTOR_TYPE )

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( GRAPHIC_OBJECT, BASE_RESOURCE, RESOURCE_TYPE, RESOURCE_TYPE_ModelResource )
    
    GRAPHIC_OBJECT();
    virtual ~GRAPHIC_OBJECT();

    void AddNewMesh( GRAPHIC_MESH * mesh );

    void Release();

    virtual void Render( GRAPHIC_RENDERER & renderer, const GRAPHIC_OBJECT_RENDER_OPTIONS & options, GRAPHIC_SHADER_EFFECT * effect );

    inline std::vector< GRAPHIC_MESH *> & GetMeshTable() { return MeshTable;}
    inline std::vector< GRAPHIC_MESH_ANIMATION_JOINT *> & GetJointTable() { return JointTable; }
    GRAPHIC_SHADER_BIND & GetShaderBindParameter();


    #if __COMPILE_WITH__COLLADA__
        inline std::vector< GRAPHIC_MESH_ANIMATION *> & GetAnimationTable() { return AnimationTable; }

        std::vector< GRAPHIC_MESH_ANIMATION *>
            AnimationTable;
    #endif

protected:

    void CompteModelViewProjection( const GRAPHIC_OBJECT_RENDER_OPTIONS & options, const CORE_MATH_MATRIX & transform, GRAPHIC_RENDERER & renderer, CORE_MATH_MATRIX & mvp, CORE_MATH_MATRIX & object_matrix );

    std::vector< GRAPHIC_MESH_ANIMATION_JOINT *>
        JointTable;
    std::vector< GRAPHIC_MESH *>
        MeshTable;
    GRAPHIC_SHADER_BIND
        ShaderBindParameter;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT__) */
