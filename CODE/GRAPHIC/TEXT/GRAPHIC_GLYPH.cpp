//
//  GRAPHIC_GLYPH.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 27/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_GLYPH.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_GLYPH )
    XS_DEFINE_ClassMember( "Value", char , Value )
    XS_DEFINE_ClassMember( "PaddingBounding", CORE_MATH_VECTOR, PaddingBounding )
    XS_DEFINE_ClassMember( "Advance", CORE_MATH_VECTOR, Advance )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GRAPHIC_GLYPH * )
XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT( GRAPHIC_GLYPH, char )

GRAPHIC_GLYPH::GRAPHIC_GLYPH() {
    
}

GRAPHIC_GLYPH::~GRAPHIC_GLYPH() {

}

GRAPHIC_GLYPH::GRAPHIC_GLYPH( const GRAPHIC_GLYPH & other ) :
    Value( other.Value ),
    PaddingBounding( other.PaddingBounding ) {
    
}
