//
//  GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/05/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX_h
#define GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX_h

typedef struct {
    unsigned int
        FrameIndex,
        NextFrameIndex;
    float
        Percentage;
} GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX;

#endif /* GRAPHIC_MESH_ANIMATION_CONTROLLER_FRAME_INDEX_h */
