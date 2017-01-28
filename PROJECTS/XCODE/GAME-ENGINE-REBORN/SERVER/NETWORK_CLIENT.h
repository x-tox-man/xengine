//
//  NETWORK_CLIENT.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_CLIENT_hpp
#define NETWORK_CLIENT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_BUFFER.h"
#include "SERVICE_NETWORK_LOBBY.h"
#include "NETWORK_PLAYER.h"
#include "CORE_TIMELINE.h"
#include "APPLICATION_COMMAND_MANAGER.h"
#include "SERVICE_NETWORK_CLIENT.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "CORE_FIXED_STATE_EVENT.h"
#include "NETWORK_CLIENT_DELEGATE.h"
#include "SERVICE_NETWORK_CONNECTION.h"
#include "CORE_TIMELINE_EVENT.h"

#define THIS_GAME_MAX_NETWORK_PLAYER_SIZE 8
#define THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE 512

XS_CLASS_BEGIN(NETWORK_CLIENT)

    NETWORK_CLIENT();

    /**
     * UDP_RECEIVED_EVENT : Event for UDP broadcast message received
     * UDP_SERVER_SELECTED_EVENT : Event for server selected (client side)
     * TCP_CONNECTED_EVENT : Message for server connection success
     * SELF_QUIT_EVENT : Event for client quitting game (lobby)
     * SERVER_DISCONNECTED_EVENT : Server connection is lost
     * SERVER_KICK_EVENT : Server closed client connection
     * SERVER_REJECTED_CONNECTION_EVENT : Server couldn't accept this client connection request
     * SERVER_REJECTED_CONNECTION_EVENT : Client left the lobby
     *   Note : this is unrecoverable
     */
    CORE_FIXED_STATE_MACHINE_DefineEvent( UDP_RECEIVED_EVENT, SERVICE_NETWORK_COMMAND * )
    CORE_FIXED_STATE_MACHINE_DefineEvent( UDP_SERVER_SELECTED_EVENT, SERVICE_NETWORK_COMMAND * )
    CORE_FIXED_STATE_MACHINE_DefineEvent( GAME_EVENT, CORE_TIMELINE_EVENT * )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( TCP_CONNECTED_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( SELF_QUIT_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( SERVER_DISCONNECTED_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( SERVER_ACCEPTED_CONNECTION_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( SERVER_KICK_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( SERVER_REJECTED_CONNECTION_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( QUIT_EVENT )

    CORE_FIXED_STATE_MACHINE_DeclareBaseState( BASE_STATE, NETWORK_CLIENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UDP_RECEIVED_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UDP_SERVER_SELECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( TCP_CONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( SERVER_REJECTED_CONNECTION_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( SERVER_ACCEPTED_CONNECTION_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( SELF_QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( SERVER_DISCONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( SERVER_KICK_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( GAME_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState(BASE_STATE, INITIAL_STATE)
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UDP_RECEIVED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UDP_SERVER_SELECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( TCP_CONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( QUIT_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( INITIAL_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState(BASE_STATE, TCP_CHALLENGE_STATE)
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( SERVER_ACCEPTED_CONNECTION_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( SERVER_REJECTED_CONNECTION_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( GAME_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( QUIT_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( TCP_CHALLENGE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState(BASE_STATE, CONNECTED_STATE)
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( SELF_QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( SERVER_DISCONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( SERVER_KICK_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( GAME_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( CONNECTED_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState(BASE_STATE, NETWORK_RECOVER_STATE)
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( SELF_QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( GAME_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( NETWORK_RECOVER_STATE )

    void Initialize();

    void Update( float time_step );

    void Finalize();

    void DispatchMessageToAllPlayers(SERVICE_NETWORK_COMMAND * command);
    void DispatchMessageToPlayer(NETWORK_PLAYER & player, CORE_DATA_STREAM & data_buffer);
    void SelectServer(SERVICE_NETWORK_COMMAND *);
    void OnTcpConnection();

    void SendJoinRequestCommand();
    void Disconnect();

    void OnTCPDataReceived( SERVICE_NETWORK_COMMAND * command );
    void OnUDPDataReceived( SERVICE_NETWORK_COMMAND * command );
    void SetClientIsConnected(bool is_connected);

    void SetOnServerStatusCallback(CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * > & callback) {
        OnServerStatusCallback = callback;
    }

    SERVICE_NETWORK_CLIENT * GetClient() { return ClientInstance; }

    NETWORK_PLAYER & GetCurrentPlayer() { return CurrentPlayer; }

private :

    void ProcessIncommingMessages();
    void ProcessAndSendOutgoingMessages();


    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >
        OnServerStatusCallback;
    SERVICE_NETWORK_CLIENT
        * ClientInstance;
    std::array< SERVICE_NETWORK_COMMAND *, THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE>
        IncommingMessageQueue;
    int
        IncommingMessageQueueIterator;
    CORE_TIMELINE
        NetworkEventsTimeLine;
    NETWORK_PLAYER
        CurrentPlayer;
    float
        NetworkRefreshRate,
        AccumulatedRemaining;
    CORE_FIXED_STATE_MACHINE< BASE_STATE, NETWORK_CLIENT >
        StateMachine;
    NETWORK_CLIENT_DELEGATE
        * Delegate;

XS_CLASS_END

#endif /* NETWORK_CLIENT_hpp */
