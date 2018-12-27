//
//  GRAPHIC_MESH_POLYGON_RENDER_MODE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 16/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_POLYGON_RENDER_MODE.h"
#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_CLASS_SERIALIZER_TemplateScalar( GRAPHIC_MESH_POLYGON_RENDER_MODE )

#if OPENGL4

GLuint GRAPHIC_MESH_POLYGON_RENDER_MODE_GetForOpengl4( const GRAPHIC_MESH_POLYGON_RENDER_MODE mode ) {
    
    static GLuint MAPPING[] = { GL_TRIANGLES, GL_LINES, GL_POINT, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP, GL_PATCHES };
    
    return MAPPING[ mode ];
}
#elif OPENGLES2
    GLuint GRAPHIC_MESH_POLYGON_RENDER_MODE_GetForOpenglES2( const GRAPHIC_MESH_POLYGON_RENDER_MODE mode ) {
        static GLuint MAPPING[] = { GL_TRIANGLES, GL_LINES, GL_POINTS, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP, GL_PATCHES };
        
        return MAPPING[ mode ];
    }
#endif
