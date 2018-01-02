//
//  NETWORK_PLAYER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_PLAYER_hpp
#define NETWORK_PLAYER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"
#include "SERVICE_NETWORK_COMMAND.h"
#include "SERVICE_NETWORK_CONNECTION.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_DATA_MODEL.h"

#include <string>

#define OUTGOING_MESSAGE_QUEUE_SIZE 36

XS_CLASS_BEGIN_WITH_ANCESTOR(NETWORK_PLAYER, CORE_DATA_MODEL)

    XS_DEFINE_SERIALIZABLE

    NETWORK_PLAYER();
    NETWORK_PLAYER( SERVICE_NETWORK_CONNECTION * connexion, CORE_HELPERS_UNIQUE_IDENTIFIER player_id, bool is_active, bool is_host, std::string & name );
    NETWORK_PLAYER(int player_id, bool is_active);
    virtual ~NETWORK_PLAYER();

    void Finalize();
    CORE_DATA_STREAM & PrepareMessage();
    void AppendMessage(SERVICE_NETWORK_COMMAND * message );

    inline const CORE_HELPERS_UNIQUE_IDENTIFIER & GetUniqueId() const { return UniqueId; }
    inline const std::string & GetName() const { return Name; }
    inline void SetName( const std::string & name ) { Name = name; }
    inline void SetUniqueId(const CORE_HELPERS_UNIQUE_IDENTIFIER & unique_id) { UniqueId = unique_id;}
    inline SERVICE_NETWORK_CONNECTION * GetNetworkConnexion() { return CurrentNewtorkStream; }
    inline void SetNetworkConnexion( SERVICE_NETWORK_CONNECTION *connection ) { CurrentNewtorkStream = connection; }
    inline void SetIsReady( bool ready ) { IsReady = ready; }
    inline bool Ready() const { return IsReady; }
    inline std::array< SERVICE_NETWORK_COMMAND *, OUTGOING_MESSAGE_QUEUE_SIZE> & GetOutGoingMessageQueue() { return OutGoingMessageQueue; }

private :

    std::string
        Name;
    CORE_DATA_STREAM
        OutGoingMessage;
    std::array< SERVICE_NETWORK_COMMAND *, OUTGOING_MESSAGE_QUEUE_SIZE>
        OutGoingMessageQueue;
    SERVICE_NETWORK_CONNECTION
        * CurrentNewtorkStream;
    CORE_HELPERS_UNIQUE_IDENTIFIER
        UniqueId;
    int
        OutGoingMessageQueueIterator;
    bool
        IsActive,
        IsHost,
        IsReady;

XS_CLASS_END

#endif /* NETWORK_PLAYER_hpp */
