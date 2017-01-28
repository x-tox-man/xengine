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
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_MESH_ANIMATION_JOINT.h"
#include "GRAPHIC_MESH_ANIMATION.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_SHADER_BIND.h"

class GRAPHIC_MESH;

XS_CLASS_BEGIN( GRAPHIC_OBJECT )
    GRAPHIC_OBJECT();

    XS_DEFINE_SERIALIZABLE

    void AddNewMesh( GRAPHIC_MESH * mesh );
    void SetShaderForMesh( GRAPHIC_MESH * meshToBind, GRAPHIC_SHADER_PROGRAM * shader );
    void BindShader();
    void Release();

    virtual void Render( const GRAPHIC_RENDERER & renderer );

    inline std::vector< GRAPHIC_MESH *> & GetMeshTable() { return MeshTable;}
    inline std::vector< GRAPHIC_SHADER_PROGRAM *> & GetShaderTable() { return ShaderTable; }
    inline std::vector< GRAPHIC_MESH_ANIMATION *> & getAnimationControllerTable() { return AnimationControllerTable; }
    inline std::vector< GRAPHIC_MESH_ANIMATION_JOINT *> & getJointTable() { return JointTable; }

    inline const CORE_MATH_VECTOR & GetPosition() const { return Position; }
    inline CORE_MATH_VECTOR & GetPosition() { return Position; }
    inline void SetPosition( const CORE_MATH_VECTOR & position ) { Position = position; };

    inline const CORE_MATH_VECTOR & GetScaleFactor() const { return ScaleFactor; }
    inline CORE_MATH_VECTOR & GetScaleFactor() { return ScaleFactor; }
    inline void SetScaleFactor( const CORE_MATH_VECTOR & scale_factor ) { ScaleFactor = scale_factor; };

    inline const CORE_MATH_QUATERNION & GetOrientation() const { return Orientation; }
    inline CORE_MATH_QUATERNION & GetOrientation() { return Orientation; }
    inline GRAPHIC_SHADER_BIND & GetShaderBindParameter() { return ShaderBindParameter; }

private:

    std::vector< GRAPHIC_MESH *>
        MeshTable;
    std::vector< GRAPHIC_SHADER_PROGRAM *>
        ShaderTable;
    std::vector< GRAPHIC_MESH_ANIMATION *>
        AnimationControllerTable;

protected:

    CORE_MATH_VECTOR
        Position,
        ScaleFactor;
    CORE_MATH_QUATERNION
        Orientation;

    //TODO: only for resource compiling target
    std::vector< GRAPHIC_MESH_ANIMATION_JOINT *>
        JointTable;

protected:

GRAPHIC_SHADER_BIND ShaderBindParameter;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT__) */
