//
//  GAMEPLAY_ACTION_SYSTEM.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_ACTION_SYSTEM__
#define __GAME_ENGINE_REBORN__GAMEPLAY_ACTION_SYSTEM__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_TIMELINE_EVENT.h"
#include "SERVICE_NETWORK_COMMAND.h"
#include "CORE_TIMELINE.h"
#include "GAMEPLAY_ACTION.h"

XS_CLASS_BEGIN( GAMEPLAY_ACTION_SYSTEM )

    XS_DEFINE_UNIQUE( GAMEPLAY_ACTION_SYSTEM )

    void ProcessEvent( CORE_TIMELINE_EVENT * event );
    void OnTimelineEventAdded( CORE_TIMELINE_EVENT * event );

    inline CORE_TIMELINE & GetTimeline() { return Timeline; }

    void DeSerializeNetworkCommand( SERVICE_NETWORK_COMMAND * command, CORE_TIMELINE_EVENT ** event ) {
        
        CORE_DATA_STREAM
            stream( (char *) command->Data, command->Size );
        
        stream.Open();
        
        int factory_type;
        
        XS_CLASS_SERIALIZER< CORE_TIMELINE_EVENT, CORE_DATA_STREAM >::Serialize< std::false_type >( "event", event, stream );
        stream >> factory_type;
        
        GAMEPLAY_ACTION * event_command = GAMEPLAY_ACTION::FactoryCreate((GAMEPLAY_ACTION_TYPE) factory_type);
        
        event_command->SetCommandType( factory_type );
        event_command->InnerDeSerialize( stream );
        
        (*event)->SetCommand(event_command);
        
        stream.Close();
    }

    // TODO: Place elsewhere
    template <typename __COMMAND_TYPE__>
    static SERVICE_NETWORK_COMMAND * CreateNetworkCommand(__COMMAND_TYPE__ & command, float start, float end ) {
        
        SERVICE_NETWORK_COMMAND
            * message = new SERVICE_NETWORK_COMMAND();
        CORE_TIMELINE_EVENT
            event;
        CORE_DATA_STREAM
            stream;
        
        event.Setup(start, end, CORE_HELPERS_UNIQUE_IDENTIFIER::Empty, &command);
        
        stream.Open();
        XS_CLASS_SERIALIZER< CORE_TIMELINE_EVENT, CORE_DATA_STREAM >::Serialize< std::true_type >( "event", event, stream );
        stream << command.FactoryGetType();
        XS_CLASS_SERIALIZER< __COMMAND_TYPE__, CORE_DATA_STREAM >::template Serialize< std::true_type >( "command", command, stream );
        stream.Close();
        
        message->Data = CORE_MEMORY_ALLOCATOR_Allocate(stream.GetOffset());
        message->Size = (int) stream.GetOffset();
        
        memcpy(message->Data, stream.GetMemoryBuffer(), stream.GetOffset());
        
        return message;
    }

    // TODO: Place elsewhere
    template <typename __COMMAND_TYPE__>
    static SERVICE_NETWORK_COMMAND * CreateNetworkCommand(__COMMAND_TYPE__ & command, unsigned int tick ) {
        
        SERVICE_NETWORK_COMMAND
            * message = new SERVICE_NETWORK_COMMAND();
        CORE_TIMELINE_EVENT
            event;
        CORE_DATA_STREAM
            stream;
        
        event.Setup( tick, CORE_HELPERS_UNIQUE_IDENTIFIER::Empty, &command );
        
        stream.Open();
        XS_CLASS_SERIALIZER< CORE_TIMELINE_EVENT, CORE_DATA_STREAM >::Serialize< std::true_type >( "event", event, stream );
        stream << command.FactoryGetType();
        XS_CLASS_SERIALIZER< __COMMAND_TYPE__, CORE_DATA_STREAM >::template Serialize< std::true_type >( "command", command, stream );
        stream.Close();
        
        message->Data = CORE_MEMORY_ALLOCATOR_Allocate(stream.GetOffset());
        message->Size = (int) stream.GetOffset();
        
        memcpy(message->Data, stream.GetMemoryBuffer(), stream.GetOffset());
        
        return message;
    }

private :

    CORE_TIMELINE
        Timeline;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_ACTION_SYSTEM__) */
