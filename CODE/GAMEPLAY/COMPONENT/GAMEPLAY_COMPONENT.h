//
//  GAMEPLAY_COMPONENT.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_MATERIAL_COLLECTION_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"

#define GAMEPLAY_COMPONENT_BASE_COUNT 2048

class GAMEPLAY_COMPONENT_HOLDER {
public:
    GAMEPLAY_COMPONENT_HOLDER( int type, int offset ) :
        Type( type ),
        Offset( offset ) {
        
    }
    
    int
        Type,
        Offset;
};

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT();
    virtual ~GAMEPLAY_COMPONENT();

    inline int GetSize() const { return Size; }

    XS_DEFINE_SERIALIZABLE

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GAMEPLAY_COMPONENT );

    //TODO: this needs to be replaced by meta GAMEPLAY_COMPONENT description system
    //CORE_HELPERS_FACTORY_Define(GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE )

    virtual void Reset() {
        
    }

protected :

    GAMEPLAY_COMPONENT( unsigned int size );

private :

    unsigned int
        Size;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT__) */
