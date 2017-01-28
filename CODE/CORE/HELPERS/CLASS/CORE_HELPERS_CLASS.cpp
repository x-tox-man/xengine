//
//  CORE_HELPERS_CLASS.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_TYPES.h"

#include <string>

XS_CLASS_SERIALIZER_TemplateScalar( int )
XS_CLASS_SERIALIZER_TemplateScalar( bool )
XS_CLASS_SERIALIZER_TemplateScalar( unsigned int )
XS_CLASS_SERIALIZER_TemplateScalar( long int )
XS_CLASS_SERIALIZER_TemplateScalar( unsigned long )
XS_CLASS_SERIALIZER_TemplateScalar( char )
XS_CLASS_SERIALIZER_TemplateScalar( unsigned char )
XS_CLASS_SERIALIZER_TemplateScalar( float )
XS_CLASS_SERIALIZER_TemplateScalar( double )
XS_CLASS_SERIALIZER_TemplateScalar( wchar_t )
XS_CLASS_SERIALIZER_TemplateScalarPointer( char )
XS_CLASS_SERIALIZER_TemplateScalarPointer( float )
XS_CLASS_SERIALIZER_TemplateScalarPointerPointer( char )
XS_CLASS_SERIALIZER_TemplateScalarPointerPointer( wchar_t )

