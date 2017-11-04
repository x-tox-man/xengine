//
//  NETWORK_SERVER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_SERVER.h"
#include "CORE_MATH_VECTOR.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED.h"
#include "GAMEPLAY_ACTION_COMMAND_START_GAME.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_CONNECTED.h"

//----------------------------------------------------------------------------------------------------------//
//                              ACCEPTING_CONNECTIONS_STATE                                                 //
//-- STATE BEGIN
//----------------------------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE )
    GetContext().SetAcceptsConnexions(true);
CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE, TCP_CONNECTED_EVENT )
        
    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE, GAME_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE, QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

CORE_FIXED_STATE_DefineStateLeaveEvent( NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE )
    GetContext().SetAcceptsConnexions(false);
CORE_FIXED_STATE_EndOfStateEvent()
//----------------------------------------------------------------------------------------------------------//
//-- STATE END
//----------------------------------------------------------------------------------------------------------//


//----------------------------------------------------------------------------------------------------------//
//                              STARTING_STATE                                                              //
//-- STATE BEGIN
//----------------------------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( NETWORK_SERVER::STARTING_STATE )
    std::vector<NETWORK_PLAYER * >
        player_table;

    for( int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++) {
        
        if ( GetContext().GetPlayerTable()[ i ] != NULL ) {
            
            NETWORK_PLAYER
                * player_ptr( GetContext().GetPlayerTable()[ i ] );
            
            player_table.push_back( player_ptr );
        }
    }

    GAMEPLAY_ACTION_COMMAND_START_GAME
        command( player_table, GetContext().Seed );

    GetContext().DispatchMessageToAllPlayers( GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand(command));
    GetContext().SetAcceptsConnexions(false);
CORE_FIXED_STATE_EndOfStateEvent()

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::STARTING_STATE, CLIENT_DISCONNECTED_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::STARTING_STATE, COUNTDOWN_FINISHED_EVENT )
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().GetStateMachine(), GetContext().CLOSED_GAME_STATE );
    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::STARTING_STATE, COUNTDOWN_CANCELLED_EVENT )
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().GetStateMachine(), GetContext().ACCEPTING_CONNECTIONS_STATE );
    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::STARTING_STATE, UPDATE_EVENT )
        GetContext().SendStartingMessage();
    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

CORE_FIXED_STATE_DefineStateLeaveEvent( NETWORK_SERVER::STARTING_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//----------------------------------------------------------------------------------------------------------//
//-- STATE END
//----------------------------------------------------------------------------------------------------------//


//----------------------------------------------------------------------------------------------------------//
//                              CLOSED_GAME_STATE                                                           //
//-- STATE BEGIN
//----------------------------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( NETWORK_SERVER::CLOSED_GAME_STATE )
    GetContext().GameStartedCallback();
CORE_FIXED_STATE_EndOfStateEvent()

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::CLOSED_GAME_STATE, CLIENT_DISCONNECTED_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::CLOSED_GAME_STATE, QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::CLOSED_GAME_STATE, GAME_EVENT )
        GAMEPLAY_ACTION_SYSTEM::GetInstance().ProcessEvent(event.GetEventData() );
    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

CORE_FIXED_STATE_DefineStateLeaveEvent( NETWORK_SERVER::CLOSED_GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//----------------------------------------------------------------------------------------------------------//
//-- STATE END
//----------------------------------------------------------------------------------------------------------//


//----------------------------------------------------------------------------------------------------------//
//                              NETWORK_RECOVER_STATE                                                       //
//-- STATE BEGIN
//----------------------------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( NETWORK_SERVER::NETWORK_RECOVER_STATE )
    GetContext().SetAcceptsConnexions(true);
CORE_FIXED_STATE_EndOfStateEvent()

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::NETWORK_RECOVER_STATE, QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::NETWORK_RECOVER_STATE, GAME_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

CORE_FIXED_STATE_DefineStateLeaveEvent( NETWORK_SERVER::NETWORK_RECOVER_STATE )
    GetContext().SetAcceptsConnexions(false);
CORE_FIXED_STATE_EndOfStateEvent()
//----------------------------------------------------------------------------------------------------------//
//-- STATE END
//----------------------------------------------------------------------------------------------------------//

NETWORK_SERVER::NETWORK_SERVER() :
    LobbyInstance( NULL ),
    PlayerTable(),
    IncommingMessageQueue(),
    IncommingMessageQueueIterator( 0 ),
    NetworkRefreshRate( 0.0f ),
    AccumulatedRemaining( 0.0f ),
    NetworkEventsTimeLine(),
    CurrentPlayer(),
    OnPlayerConnected(),
    OnPlayerLeft(),
    GameStartedCallback(),
    StartingGameCounter( 0 ),
    StartingGameTicTacCounter( true ) {
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        PlayerTable[i] = NULL;
    }
     
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE; i++ ) {

        IncommingMessageQueue[i] = NULL;
    }
}

NETWORK_SERVER::~NETWORK_SERVER() {
    
}

void NETWORK_SERVER::Initialize( float network_refresh_rate ) {
    
    LobbyInstance = new SERVICE_NETWORK_LOBBY();
    NetworkRefreshRate = network_refresh_rate;
    
    LobbyInstance->Initialize(THIS_GAME_MAX_NETWORK_PLAYER_SIZE, "XS_SERVER_ACCEPTS_CONNECTIONS" );
    
    LobbyInstance->OnTCPNetworkCommandReceivedCallback = new CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >( &Wrapper1< NETWORK_SERVER , SERVICE_NETWORK_COMMAND *, &NETWORK_SERVER::OnTCPDataReceived >, this );
    
    LobbyInstance->OnTCPNewConnectionCallback = CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_CONNECTION * >( &Wrapper1< NETWORK_SERVER, SERVICE_NETWORK_CONNECTION * , &NETWORK_SERVER::OnLobbyTCPNewConnection>, this );
    
    CORE_FIXED_STATE_InitializeState( StateMachine, NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE, this );
    
    CurrentPlayer.InitializeObservable();
    
    CORE_HELPERS_CALLBACK_1< NETWORK_PLAYER * > callback ( &Wrapper1<NETWORK_SERVER, NETWORK_PLAYER *, &NETWORK_SERVER::ConnectedUpdateClientInfo >, this );
    
    GAMEPLAY_ACTION_COMMAND_CLIENT_CONNECTED::ClientConnectedCallback = callback;
    
    char
        id[32];
    
    sprintf(id, "PLAYER%d", 0);
    
    std::string str( id );
    
    CurrentPlayer.SetUniqueId( CORE_HELPERS_UNIQUE_IDENTIFIER(id) );
    CurrentPlayer.SetName( id );


    
    PlayerTable[0] = &CurrentPlayer;
}

void NETWORK_SERVER::ConnectedUpdateClientInfo( NETWORK_PLAYER * player ) {
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        if ( PlayerTable[i] == NULL && PlayerTable[i]->GetUniqueId() == player->GetUniqueId() ) {
            
            PlayerTable[i]->SetName( player->GetName() );
            PlayerTable[i]->SetUniqueId( player->GetUniqueId() );
        }
    }
    
}

void NETWORK_SERVER::SetAcceptsConnexions(bool accepts) {
    
    if ( accepts ){
        
        LobbyInstance->StartBroadcast();
        LobbyInstance->StartTCPListen();
    }
    else {
        
        if ( LobbyInstance ) {
            
            LobbyInstance->StopBroadcast();
            LobbyInstance->StopTCPListen();
        }
    }
}

void NETWORK_SERVER::DispatchMessageToAllPlayers(SERVICE_NETWORK_COMMAND * command) {
    
    for(int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i ++ ) {
        
        if ( PlayerTable[i] != NULL ) {
            
            PlayerTable[i]->AppendMessage( command );
        }
    }
}

void NETWORK_SERVER::DispatchMessageToPlayer(NETWORK_PLAYER & player, CORE_DATA_STREAM & data_buffer) {
    
    for(int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i ++ ) {
        
        if ( PlayerTable[i] != NULL && player.GetUniqueId() == PlayerTable[i]->GetUniqueId() ) {
            SERVICE_NETWORK_COMMAND * message = new SERVICE_NETWORK_COMMAND();
            
            PlayerTable[i]->AppendMessage( message );
        }
    }
}

void NETWORK_SERVER::DropPlayer( NETWORK_PLAYER * player ) {
    
}

void NETWORK_SERVER::AcceptPlayerFromConnection( SERVICE_NETWORK_CONNECTION * connection ) {
    
    NETWORK_PLAYER
        * player = NULL;
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        if ( PlayerTable[i] == NULL ) {
            
            char
                id[32];
            sprintf(id, "PLAYER%d", i);
            
            std::string str( id );
            
            PlayerTable[i] = new NETWORK_PLAYER(connection, CORE_HELPERS_UNIQUE_IDENTIFIER(id), true, false, str );
            PlayerTable[i]->InitializeObservable();
            player = PlayerTable[i];
            PlayerTable[i]->SetNetworkConnexion( connection );
            
            OnPlayerConnected( player );
            
            break;
        }
    }
    
    if ( player != NULL ) {

        GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED
            accepted_command( player );

        auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand<GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED > ( accepted_command );
        
        player->AppendMessage( network_message );
    }
    
    /*TODO: elswhere :
     ApplicationTimeline.SetOnEventAddedCallback(
     CORE_HELPERS_CALLBACK_1<CORE_TIMELINE_EVENT *>( &Wrapper1< MyTestApp, CORE_TIMELINE_EVENT * , &MyTestApp::OnTimelineEventAdded>, this )
     );*/
}

void NETWORK_SERVER::Update( float time_step ) {

    AccumulatedRemaining += time_step;
    
    if ( LobbyInstance ) {
        LobbyInstance->Update( time_step );
    }
    
    StateMachine.DispatchEvent(UPDATE_EVENT(time_step));
    
    if ( NetworkRefreshRate > 0.0f ) {
    
        if ( NetworkRefreshRate < AccumulatedRemaining ) {
            
            AccumulatedRemaining -=NetworkRefreshRate;
            
            ProcessIncommingMessages();
            ProcessAndSendOutgoingMessages();
        }
    }
    else
    {
        ProcessIncommingMessages();
        ProcessAndSendOutgoingMessages();
    }
}

void NETWORK_SERVER::Finalize() {
    
    SetAcceptsConnexions( false );
    if ( LobbyInstance ) {
        
        LobbyInstance->Finalize();
    }
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        if ( PlayerTable[i] == NULL ) {
            
            CORE_MEMORY_ObjectSafeDeallocation( PlayerTable[i] );
            
            break;
        }
    }
    
    for (int i = 0; i < IncommingMessageQueue.size(); i++ ) {
        
        auto command = IncommingMessageQueue[i];
        
        if ( command != NULL ) {
            
            CORE_MEMORY_ObjectSafeDeallocation( IncommingMessageQueue[i] );
        }
    }
}

/**
 * On new tcp connection
 *      connect the timeline to the network socket
 *      TODO : this is not correct when more than 2 players are in the lobby
 */
void NETWORK_SERVER::OnLobbyTCPNewConnection( SERVICE_NETWORK_CONNECTION * connexion ) {
    
    StateMachine.DispatchEvent(TCP_CONNECTED_EVENT());
}

void NETWORK_SERVER::OnTCPDataReceived( SERVICE_NETWORK_COMMAND * command ) {
    
    //TODO: check race condition
    IncommingMessageQueue[IncommingMessageQueueIterator++] = command;
    
    if ( IncommingMessageQueueIterator == THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE ) {
        IncommingMessageQueueIterator = 0;
    }
}

void NETWORK_SERVER::ProcessIncommingMessages() {
    
    SERVICE_NETWORK_COMMAND * command = NULL;
    CORE_TIMELINE_EVENT * event = NULL;
    
    for (int i = 0; i < IncommingMessageQueue.size(); i++ ) {
        
        command = IncommingMessageQueue[i];
        
        if ( command == NULL ) {
            continue;
        }
        
        GAMEPLAY_ACTION_SYSTEM::GetInstance().DeSerializeNetworkCommand( command, &event );
        
        for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
            
            if ( command && PlayerTable[i] != NULL && PlayerTable[i]->GetNetworkConnexion() != NULL && PlayerTable[i]->GetNetworkConnexion()->UVConnection.TCPType.TCPServer == command->Connection->UVConnection.TCPType.TCPServer ) {
                
                // Assign the command to the player
                
                StateMachine.DispatchEvent(GAME_EVENT(event));
                
                command = NULL;
            }
        }
        
        if ( command != NULL ) {
            
            if ( ((GAMEPLAY_ACTION *) event->GetCommand())->GetCommandType() == (int) GAMEPLAY_ACTION_TYPE_ClientConnected ) {
                
                if ( AcceptsConnections() ) {
                    AcceptPlayerFromConnection( command->Connection );
                }
                else {
                    //TO Test
                    command->Connection->Stop();
                }
            }
        }
        
        CORE_MEMORY_ObjectSafeDeallocation( IncommingMessageQueue[i] );
    }
}

void NETWORK_SERVER::ProcessAndSendOutgoingMessages() {
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        if ( PlayerTable[i] !=  NULL && PlayerTable[i]->GetNetworkConnexion() != NULL ) {
            
            LobbyInstance->SendTcpCommand(
                PlayerTable[i]->PrepareMessage(),
                PlayerTable[i]->GetNetworkConnexion() );
        }
    }
}

void NETWORK_SERVER::RejectPlayer( SERVICE_NETWORK_CONNECTION * connection ) {
    
    GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED
        command;
    CORE_DATA_STREAM
        stream;
    
    auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( command );
    
    stream.Open();
    network_message->Serialize( stream );
    stream.Close();
    
    LobbyInstance->SendTcpCommand(stream, connection);
}

bool NETWORK_SERVER::AcceptsConnections() {
    
    // check if there is still room left, this must be done in critical section
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        if ( PlayerTable[i] ==  NULL ) {
            
            return true;
        }
    }
    
    return false;
}

void NETWORK_SERVER::StartCountDown() {
    
    StateMachine.ChangeState( STARTING_STATESTATE );
}

void NETWORK_SERVER::SendStartingMessage() {
    
    if ( StartingGameCounter < 10 ) {
        
        if ( StartingGameTicTacCounter ) {
            
            StartingGameCounter++;
        }
        
        StartingGameTicTacCounter = !StartingGameTicTacCounter;
    }
    else {
        
        StateMachine.DispatchEvent(COUNTDOWN_FINISHED_EVENT());
    }
}
