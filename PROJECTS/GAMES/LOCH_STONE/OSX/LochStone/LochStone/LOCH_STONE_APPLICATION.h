//
//  LOCH_STONE_APPLICATION.h
//  LochStone
//
//  Created by Christophe Bernard on 23/08/15.
//  Copyright (c) 2015 XFriends. All rights reserved.
//

#ifndef __LochStone__LOCH_STONE_APPLICATION__
#define __LochStone__LOCH_STONE_APPLICATION__

#include "CORE_APPLICATION.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"
#include "GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h"
#include "GRAPHIC_OBJECT_SHAPE_SPHERE.h"
#include "GRAPHIC_OBJECT_SHAPE_LINE.h"
#include "GAMEPLAY_SCENE.h"
#include "CORE_MATH_VECTOR.h"
#include "APPLICATION_MAIN_WINDOW.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"
#include "CORE_FILESYSTEM.h"

#include "LOCH_PLAYER.h"
#include "LOCH_BOARD.h"
#include "LOCH_MAIN_MENU.h"

#if GRAPHIC_RENDERER_OPENGL
#define GRAPHIC_RENDER_PLATFORM OPENGL
#include "GRAPHIC_RENDERER.h"
#undef GRAPHIC_RENDER_PLATFORM
#endif

#if GRAPHIC_RENDERER_DX_9
#define GRAPHIC_RENDER_PLATFORM DX_9
#include "GRAPHIC_RENDERER.h"
#undef GRAPHIC_RENDER_PLATFORM
#endif

#if GRAPHIC_RENDERER_DX_11
#define GRAPHIC_RENDER_PLATFORM DX_11
#include "GRAPHIC_RENDERER.h"
#undef GRAPHIC_RENDER_PLATFORM
#endif

XS_CLASS_BEGIN_WITH_ANCESTOR( LOCH_STONE_APPLICATION, CORE_APPLICATION )

CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( LOCH_STONE_APPLICATION );

LOCH_STONE_APPLICATION();

virtual void Initialize();
virtual void Finalize();

virtual void Update( float time_step );
virtual void Render();

void InitializeGraphics();

void OnObjectPicked( GAMEPLAY_COMPONENT_ENTITY * entity );

GAMEPLAY_SCENE * GetScene() { return Scene; }

CORE_FILESYSTEM & GetDefaultFileystem() { return DefaultFileystem; }

private :

GAMEPLAY_SCENE * Scene;
CORE_MATH_VECTOR Position;
CORE_MATH_QUATERNION Lookat;
GRAPHIC_CAMERA *Camera;
LOCH_MAIN_MENU MainWindow;
GRAPHIC_CAMERA_ORTHOGONAL * InterfaceCamera;
CORE_FILESYSTEM DefaultFileystem;

XS_CLASS_END

#endif /* defined(__LochStone__LOCH_STONE_APPLICATION__) */
