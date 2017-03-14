//
//  ApplicationTestCommands.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 9/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef ApplicationTestCommands_h
#define ApplicationTestCommands_h

#include "CORE_TIMELINE.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_HELPERS_FACTORY.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_MATH_VECTOR.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "CORE_MEMORY.h"
#include "NETWORK_PLAYER.h"
#include "CORE_HELPERS_CALLBACK.h"

#define SimpleTrickForSerialization() \
virtual void InnerSerialize(CORE_DATA_STREAM & stream) override; \
virtual void InnerDeSerialize(CORE_DATA_STREAM & stream) override;

#define ImplementTrickFroSerializeation(__CLASS_TYPE__, __ENUM_TYPE__) \
void __CLASS_TYPE__::InnerSerialize(CORE_DATA_STREAM & stream) { \
stream << __ENUM_TYPE__; \
XS_CLASS_SERIALIZER<__CLASS_TYPE__>::Serialize<std::true_type>( *this, stream ); \
} \
void __CLASS_TYPE__::InnerDeSerialize(CORE_DATA_STREAM & stream) { \
}

enum APPLICATION_NETWORK_COMMAND_TYPE {
    
    APPLICATION_NETWORK_COMMAND_ClientConnected = 0,
    APPLICATION_NETWORK_COMMAND_ClientReady,
    APPLICATION_NETWORK_COMMAND_ClientQuit,
    APPLICATION_GAMEPLAY_COMMAND_ActionFire,
    APPLICATION_GAMEPLAY_COMMAND_ActionMove,
    APPLICATION_GAMEPLAY_COMMAND_ActionMoveEntity,
    APPLICATION_GAMEPLAY_COMMAND_OrderBuild,
    APPLICATION_GAMEPLAY_COMMAND_OrderAttack,
    APPLICATION_GAMEPLAY_COMMAND_OrderMove,
    APPLICATION_NETWORK_COMMAND_ClientAccepted,
    APPLICATION_NETWORK_COMMAND_ClientRejected,
    APPLICATION_GAMEPLAY_COMMAND_LoadGame,
    APPLICATION_GAMEPLAY_COMMAND_GameStarting,
    APPLICATION_GAMEPLAY_COMMAND_NONE
};

class APPLICATION_COMMAND : public CORE_TIMELINE_COMMAND {
    
    public :
    
    APPLICATION_COMMAND() :
        CORE_TIMELINE_COMMAND(),
        Data( NULL ),
        Type(-1) {
        
    }
    
    virtual ~APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    
    CORE_HELPERS_FACTORY_Define( APPLICATION_COMMAND, enum APPLICATION_NETWORK_COMMAND_TYPE )
    
    virtual void Apply() {
        
    }
    virtual void InnerSerialize(CORE_DATA_STREAM & stream) {
        
    }
    virtual void InnerDeSerialize(CORE_DATA_STREAM & stream) {
        
    };
    
    void SetCommandType( int type ) {
        Type = type;
    }
    
    int GetCommandType() { return Type; }
    protected :
    
    void * Data;
    int Type;
};

class APPLICATION_GAMEPLAY_COMMAND_LOAD_GAME : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_GAMEPLAY_COMMAND_LOAD_GAME() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_GAMEPLAY_COMMAND_LOAD_GAME, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_GAMEPLAY_COMMAND_LoadGame )
    
    virtual void Apply() override;
    
    SimpleTrickForSerialization()
    
    static CORE_HELPERS_CALLBACK
        OnGameLoaded;
};

class APPLICATION_GAMEPLAY_COMMAND_GAME_STARTING : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_GAMEPLAY_COMMAND_GAME_STARTING() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_GAMEPLAY_COMMAND_GAME_STARTING, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_GAMEPLAY_COMMAND_GameStarting )
    
    virtual void Apply() override;
    
    SimpleTrickForSerialization()
};

class APPLICATION_NETWORK_COMMAND_CLIENT_CONNECTED : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_NETWORK_COMMAND_CLIENT_CONNECTED() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_NETWORK_COMMAND_CLIENT_CONNECTED, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_NETWORK_COMMAND_ClientConnected )
    
    virtual void Apply() override;
    
    NETWORK_PLAYER * GetPlayer() { return Player; }
    
    SimpleTrickForSerialization()
    
    NETWORK_PLAYER
        * Player;
};

class APPLICATION_NETWORK_COMMAND_CLIENT_ACCEPTED  : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_NETWORK_COMMAND_CLIENT_ACCEPTED() :
    APPLICATION_COMMAND() {
        
    }
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_NETWORK_COMMAND_CLIENT_ACCEPTED, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_NETWORK_COMMAND_ClientAccepted )
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    virtual void Apply() override;
};

class APPLICATION_NETWORK_COMMAND_CLIENT_REJECTED  : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_NETWORK_COMMAND_CLIENT_REJECTED() :
    APPLICATION_COMMAND() {
        
    }
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_NETWORK_COMMAND_CLIENT_REJECTED, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_NETWORK_COMMAND_ClientRejected )
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    virtual void Apply() override;
};

class APPLICATION_NETWORK_COMMAND_CLIENT_READY : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_NETWORK_COMMAND_CLIENT_READY() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_NETWORK_COMMAND_CLIENT_READY, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_NETWORK_COMMAND_ClientReady )
    
    virtual void Apply() override {
        
    }
    
    CORE_HELPERS_UNIQUE_IDENTIFIER ClientIdentifier;
};

class APPLICATION_NETWORK_COMMAND_CLIENT_ACTION : public APPLICATION_COMMAND {
    
    APPLICATION_NETWORK_COMMAND_CLIENT_ACTION() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    virtual void Apply() override {
        
    }
};

class APPLICATION_NETWORK_COMMAND_CLIENT_QUIT : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_NETWORK_COMMAND_CLIENT_QUIT() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_NETWORK_COMMAND_CLIENT_QUIT, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_NETWORK_COMMAND_ClientQuit )
    
    virtual void Apply() override {
        
    }
    
    CORE_HELPERS_UNIQUE_IDENTIFIER ClientIdentifier;
};

/************************************
 * class APPLICATION_GAMEPLAY_COMMAND
 ************************************
 *      Description :
 *          A command that one player does in the game. This should not be used directly
 *          It can be passed to the network as a APPLICATION_NETWORK_COMMAND_CLIENT_ACTION
 ************************************
 */
class APPLICATION_GAMEPLAY_COMMAND : public APPLICATION_COMMAND {
    
    APPLICATION_GAMEPLAY_COMMAND() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    virtual void Apply() override {
        
    }
};

/************************************
 * class APPLICATION_GAMEPLAY_COMMAND_ACTION
 ************************************
 *      Description :
 *          An action is a event that did not last in time and which is to be refreshed until next frame or so
 *          This should be used in FPS/RACING games which represent players perspective real-time inputs & modifications
 *          This should be treated upon firing.
 ************************************
 */
class APPLICATION_GAMEPLAY_COMMAND_ACTION : public APPLICATION_COMMAND {
    
    public :
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    APPLICATION_GAMEPLAY_COMMAND_ACTION() :
        APPLICATION_COMMAND() {
        
    }
    
    virtual void Apply() override {
        
    }
};

class APPLICATION_GAMEPLAY_COMMAND_ACTION_FIRE : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_GAMEPLAY_COMMAND_ACTION_FIRE() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_GAMEPLAY_COMMAND_ACTION_FIRE, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_GAMEPLAY_COMMAND_ActionFire )
    
    virtual void Apply() override {
        
    }
};

class APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_GAMEPLAY_COMMAND_ActionMove )
    
    virtual void Apply() override {
        
    }
};

class APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_GAMEPLAY_COMMAND_ACTION_MOVE_ENTITY, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_GAMEPLAY_COMMAND_ActionMoveEntity )
    
    virtual void Apply() override {
        
    }
    
    CORE_MATH_VECTOR NewPosition;
    GAMEPLAY_COMPONENT_ENTITY * EntityToMove;
};

/************************************
 * class APPLICATION_GAMEPLAY_COMMAND_ORDER
 ************************************
 *      Description :
 *          An order is a event that needs some time before completion that is not immediate nor requires immediate action
 *          This should be used in STR context
 ************************************
 */
class APPLICATION_GAMEPLAY_COMMAND_ORDER : public APPLICATION_COMMAND {
    
    public :
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    APPLICATION_GAMEPLAY_COMMAND_ORDER() :
        APPLICATION_COMMAND() {
        
    }
    
    virtual void Apply() override {
        
    }
};


class APPLICATION_GAMEPLAY_COMMAND_ORDER_BUILD : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_GAMEPLAY_COMMAND_ORDER_BUILD() :
        APPLICATION_COMMAND() {
        
    }

    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_GAMEPLAY_COMMAND_ORDER_BUILD, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_GAMEPLAY_COMMAND_OrderBuild )
    
    virtual void Apply() override {

    }
};

class APPLICATION_GAMEPLAY_COMMAND_ORDER_ATTACK : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_GAMEPLAY_COMMAND_ORDER_ATTACK() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_GAMEPLAY_COMMAND_ORDER_ATTACK, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_GAMEPLAY_COMMAND_OrderAttack )
    
    virtual void Apply() override {
        
    }
};

class APPLICATION_GAMEPLAY_COMMAND_ORDER_MOVE : public APPLICATION_COMMAND {
    
    public :
    
    APPLICATION_GAMEPLAY_COMMAND_ORDER_MOVE() :
        APPLICATION_COMMAND() {
        
    }
    
    XS_DEFINE_SERIALIZABLE
    SimpleTrickForSerialization()
    
    CORE_HELPERS_FACTORY_Element( APPLICATION_GAMEPLAY_COMMAND_ORDER_MOVE, APPLICATION_COMMAND, APPLICATION_NETWORK_COMMAND_TYPE, APPLICATION_GAMEPLAY_COMMAND_OrderMove )
    
    virtual void Apply() override {
        
    }
};

#endif /* ApplicationTestCommands_hpp */
