//
//  GAMEPLAY_ACTION.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_ACTION__
#define __GAME_ENGINE_REBORN__GAMEPLAY_ACTION__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_TIMELINE_COMMAND.h"
#include "GAMEPLAY_ACTION_TYPE.h"
#include "CORE_HELPERS_FACTORY.h"
#include "CORE_DATA_JSON.h"

#define SimpleTrickForSerialization() \
    virtual void InnerSerialize(CORE_DATA_STREAM & stream) override; \
    virtual void InnerDeSerialize(CORE_DATA_STREAM & stream) override;

#define ImplementTrickFroSerializeation(__CLASS_TYPE__, __ENUM_TYPE__) \
    void __CLASS_TYPE__::InnerSerialize(CORE_DATA_STREAM & stream) { \
        stream << __ENUM_TYPE__; \
XS_CLASS_SERIALIZER<__CLASS_TYPE__, CORE_DATA_STREAM >::Serialize<std::true_type>( #__CLASS_TYPE__, *this, stream ); \
    } \
    void __CLASS_TYPE__::InnerDeSerialize(CORE_DATA_STREAM & stream) { \
        XS_CLASS_SERIALIZER<__CLASS_TYPE__, CORE_DATA_STREAM>::Serialize<std::false_type>( #__CLASS_TYPE__,*this, stream ); \
    }

XS_CLASS_BEGIN_WITH_ANCESTOR(GAMEPLAY_ACTION, CORE_TIMELINE_COMMAND)

    XS_DEFINE_SERIALIZABLE

    GAMEPLAY_ACTION();
    virtual ~GAMEPLAY_ACTION();

    CORE_HELPERS_FACTORY_Define( GAMEPLAY_ACTION, enum GAMEPLAY_ACTION_TYPE )

    virtual void Apply() { }
    virtual void InnerSerialize(CORE_DATA_STREAM & stream) {}
    virtual void InnerDeSerialize(CORE_DATA_STREAM & stream) {}

    inline void SetCommandType( int type ) { Type = type; }
    inline int GetCommandType() { return Type; }

protected :

    void
        * Data;
    int
        Type;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_ACTION__) */
