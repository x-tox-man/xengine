//
//  APPLICATION_COMMAND_MANAGER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_COMMAND_MANAGER_hpp
#define APPLICATION_COMMAND_MANAGER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_TIMELINE.h"
#include "CORE_MATH_VECTOR.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "CORE_DATA_STREAM.h"
#include "SERVICE_NETWORK_COMMAND.h"
#include "APPLICATION_COMMAND.h"

XS_CLASS_BEGIN(APPLICATION_COMMAND_MANAGER)

    XS_DEFINE_UNIQUE( APPLICATION_COMMAND_MANAGER )

    ~APPLICATION_COMMAND_MANAGER();

    void ProcessEvent( CORE_TIMELINE_EVENT * event );
    void OnTimelineEventAdded( CORE_TIMELINE_EVENT * event );
    inline CORE_TIMELINE & GetTimeline() { return Timeline; }

    void DeSerializeNetworkCommand(SERVICE_NETWORK_COMMAND * command, CORE_TIMELINE_EVENT ** event ) {
        
        CORE_DATA_STREAM
            stream( (char *) command->Data, command->Size );
        
        stream.Open();
        
        int factory_type;
        
        XS_CLASS_SERIALIZER<CORE_TIMELINE_EVENT, CORE_DATA_STREAM >::Serialize< std::false_type >( "event", event, stream );
        stream >> factory_type;
        APPLICATION_COMMAND * event_command = APPLICATION_COMMAND::FactoryCreate((APPLICATION_NETWORK_COMMAND_TYPE) factory_type);
        
        event_command->SetCommandType( factory_type );
        event_command->InnerDeSerialize( stream );
        
        (*event)->SetCommand(event_command);
        
        stream.Close();
    }

    //TODO : Place elsewhere
    template <typename __COMMAND_TYPE__>
    static SERVICE_NETWORK_COMMAND * CreateNetworkCommand(__COMMAND_TYPE__ & command) {
        
        SERVICE_NETWORK_COMMAND
            * message = new SERVICE_NETWORK_COMMAND();
        CORE_TIMELINE_EVENT
            event;
        CORE_DATA_STREAM
            stream;
        
        event.Setup(0.0f, 0.0f, CORE_HELPERS_UNIQUE_IDENTIFIER::Empty, &command);
        
        stream.Open();
        XS_CLASS_SERIALIZER<CORE_TIMELINE_EVENT, CORE_DATA_STREAM >::Serialize< std::true_type >( "event", event, stream );
        stream << command.GetFactoryType();
        XS_CLASS_SERIALIZER<__COMMAND_TYPE__, CORE_DATA_STREAM >::template Serialize< std::true_type >( command, stream );
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

#endif /* APPLICATION_COMMAND_MANAGER_hpp */
