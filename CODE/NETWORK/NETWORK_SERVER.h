//
//  GAME_SERVER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 29/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_SERVER_hpp
#define NETWORK_SERVER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_BUFFER.h"
#include "SERVICE_NETWORK_LOBBY.h"
#include "NETWORK_PLAYER.h"
#include "CORE_TIMELINE.h"
#include "SERVICE_NETWORK_LOBBY_CLIENT.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "CORE_FIXED_STATE_EVENT.h"
#include "SERVICE_NETWORK_CONNECTION.h"
#include "CORE_TIMELINE_EVENT.h"
#include "NETWORK_SERVER_DELEGATE.h"

#define THIS_GAME_MAX_NETWORK_PLAYER_SIZE 8
#define THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE 512

XS_CLASS_BEGIN(NETWORK_SERVER)

    NETWORK_SERVER();
    ~NETWORK_SERVER();

    CORE_FIXED_STATE_MACHINE_DefineEvent( GAME_EVENT, CORE_TIMELINE_EVENT * )
    CORE_FIXED_STATE_MACHINE_DefineEvent( UPDATE_EVENT, float )
    CORE_FIXED_STATE_MACHINE_DefineEvent( CLIENT_LOADED_EVENT, NETWORK_PLAYER * )
    CORE_FIXED_STATE_MACHINE_DefineEvent( CLIENT_DISCONNECTED_EVENT, NETWORK_PLAYER * )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( TCP_CONNECTED_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( QUIT_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( COUNTDOWN_FINISHED_EVENT )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( COUNTDOWN_CANCELLED_EVENT )


    CORE_FIXED_STATE_MACHINE_DeclareBaseState( BASE_STATE, NETWORK_SERVER )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( TCP_CONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( CLIENT_DISCONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( CLIENT_LOADED_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( GAME_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UPDATE_EVENT )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( COUNTDOWN_FINISHED_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState(BASE_STATE, STARTING_STATE)
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( CLIENT_DISCONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( GAME_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( CLIENT_LOADED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( COUNTDOWN_FINISHED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( COUNTDOWN_CANCELLED_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( STARTING_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState(BASE_STATE, ACCEPTING_CONNECTIONS_STATE)
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( TCP_CONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( CLIENT_DISCONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( GAME_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( ACCEPTING_CONNECTIONS_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState(BASE_STATE, CLOSED_GAME_STATE)
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( GAME_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( CLIENT_DISCONNECTED_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( CLOSED_GAME_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState(BASE_STATE, NETWORK_RECOVER_STATE)
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( QUIT_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( GAME_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( NETWORK_RECOVER_STATE )

    void Initialize( float network_refresh_rate, const char * discover_message );
    void SetAcceptsConnexions(bool accepts);

    void Update( float time_step );

    void Finalize();

    void DispatchMessageToAllPlayers(SERVICE_NETWORK_COMMAND * command);
    void DispatchMessageToPlayer(NETWORK_PLAYER & player, CORE_DATA_STREAM & data_buffer);
    void DispatchMessageToPlayer(NETWORK_PLAYER & player, SERVICE_NETWORK_COMMAND * command);

    void DropPlayer( NETWORK_PLAYER * );
    void AcceptPlayerFromConnection( SERVICE_NETWORK_CONNECTION * );
    void RejectPlayer( SERVICE_NETWORK_CONNECTION * connection );

    bool AcceptsConnections();
    void DisconnectAll();
    void StartCountDown();
    void ServerChanged();
    void SetReady( bool ready );

    inline SERVICE_NETWORK_LOBBY * GetLobby() { return LobbyInstance; }
    inline CORE_FIXED_STATE_MACHINE< BASE_STATE, NETWORK_SERVER > & GetStateMachine() { return StateMachine; }
    inline NETWORK_PLAYER & GetCurrentPlayer() { return CurrentPlayer; }
    inline void SetGameStartedCallback( const CORE_HELPERS_CALLBACK & callback) { GameStartedCallback = callback; }
    inline std::array<NETWORK_PLAYER *, THIS_GAME_MAX_NETWORK_PLAYER_SIZE> & GetPlayerTable() { return PlayerTable; }
    inline void SetSeed( int seed ) { Seed = seed; }
    inline void SetDelegate( NETWORK_SERVER_DELEGATE * delegate ) { Delegate = delegate; }

    SERVICE_NETWORK_COMMAND * CreateInfo();

private :

    void ProcessIncommingMessages();
    void ProcessAndSendOutgoingMessages();
    void SendStartingMessage();

    void UpdateLagValues();

    void OnLobbyTCPNewConnection( SERVICE_NETWORK_CONNECTION * stream );
    void OnTCPDataReceived( SERVICE_NETWORK_COMMAND * command );
    void ConnectedUpdateClientInfo( NETWORK_PLAYER * player );

    std::array<NETWORK_PLAYER *, THIS_GAME_MAX_NETWORK_PLAYER_SIZE>
        PlayerTable;
    std::array< SERVICE_NETWORK_COMMAND *, THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE>
        IncommingMessageQueue;
    CORE_FIXED_STATE_MACHINE< BASE_STATE, NETWORK_SERVER >
        StateMachine;
    NETWORK_PLAYER
        CurrentPlayer;
    CORE_HELPERS_CALLBACK
        GameStartedCallback;
    NETWORK_SERVER_DELEGATE
        * Delegate;
    SERVICE_NETWORK_LOBBY
        * LobbyInstance;
    int
        StartingGameCounter,
        Seed,
        IncommingMessageQueueIterator;
    bool
        StartingGameTicTacCounter;
    float
        NetworkRefreshRate,
        AccumulatedRemaining;
    CORE_PARALLEL_LOCK_MUTEX
        ServerLock;

XS_CLASS_END

#endif /* GAME_SERVER_hpp */
