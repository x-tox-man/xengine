//
//  NETWORK_SERVER.cpp
//  GAME-ENGINE
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
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_QUIT.h"
#include "GAMEPLAY_ACTION_COMMAND_SERVER_QUIT.h"
#include "GAMEPLAY_ACTION_COMMAND_SERVER_INFO.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_READY.h"
#include "GAMEPLAY_ACTION_COMMAND_GAME_LOADED.h"
#include "GAMEPLAY_ACTION_COMMAND_LOAD_GAME.h"
#include "GAMEPLAY_ACTION_COMMAND_CLOCK.h"

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
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE, UPDATE_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE, QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE, CLIENT_DISCONNECTED_EVENT )

        if ( GetContext().Delegate ) {
            
            GetContext().Delegate->OnClientDisconnected( event.GetEventData() );
            GetContext().ServerChanged();
        }
        #if DEBUG
            else {
                SERVICE_LOGGER_Warning( "Add NETWORK_SERVER_DELEGATE" );
            }
        #endif

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

        GetContext().SetAcceptsConnexions(false);

        for( int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++) {
            
            if ( GetContext().GetPlayerTable()[ i ] != NULL ) {
                
                NETWORK_PLAYER
                    * player_ptr( GetContext().GetPlayerTable()[ i ] );
                
                player_table.push_back( player_ptr );
            }
        }

        GAMEPLAY_ACTION_COMMAND_LOAD_GAME
            command( player_table );

        GetContext().DispatchMessageToAllPlayers( GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand(command, 0));
        SERVICE_LOGGER_Warning( "NETWORK_SERVER Sending Load Game\n" );
    CORE_FIXED_STATE_EndOfStateEvent()

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::STARTING_STATE, CLIENT_DISCONNECTED_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::STARTING_STATE, CLIENT_LOADED_EVENT )

        bool loaded = false;

        for ( int pi = 0; pi < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; pi++ ) {
            
            if ( GetContext().PlayerTable[ pi ] != NULL && GetContext().PlayerTable[ pi ]->IsGameLoaded() ) {
                
                loaded = true;
            }
            else {
                loaded = false;
                break;
            }
        }
    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_SERVER::STARTING_STATE, GAME_EVENT )
        //Do Nothing
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

    GetContext().DispatchMessageToAllPlayers( GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand(command, 0));
    SERVICE_LOGGER_Warning( "NETWORK_SERVER Sending Start Game\n" );
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
    CurrentPlayer(),
    GameStartedCallback(),
    StartingGameCounter( 0 ),
    StartingGameTicTacCounter( true ),
    Delegate( NULL ),
    ServerLock() {
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        PlayerTable[i] = NULL;
    }
     
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE; i++ ) {

        IncommingMessageQueue[i] = NULL;
    }
}

NETWORK_SERVER::~NETWORK_SERVER() {
    
}

void NETWORK_SERVER::Initialize( float network_refresh_rate, const char * discover_message ) {
    
    char
        id[32];
    
    LobbyInstance = new SERVICE_NETWORK_LOBBY();
    NetworkRefreshRate = network_refresh_rate;
    
    LobbyInstance->Initialize(THIS_GAME_MAX_NETWORK_PLAYER_SIZE, discover_message );
    
    LobbyInstance->OnTCPNetworkCommandReceivedCallback = new CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >( &Wrapper1< NETWORK_SERVER , SERVICE_NETWORK_COMMAND *, &NETWORK_SERVER::OnTCPDataReceived >, this );
    
    LobbyInstance->OnTCPNewConnectionCallback = CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_CONNECTION * >( &Wrapper1< NETWORK_SERVER, SERVICE_NETWORK_CONNECTION * , &NETWORK_SERVER::OnLobbyTCPNewConnection>, this );
    
    CORE_FIXED_STATE_InitializeState( StateMachine, NETWORK_SERVER::ACCEPTING_CONNECTIONS_STATE, this );
    
    CurrentPlayer.InitializeObservable();
    
    CORE_HELPERS_CALLBACK_1< NETWORK_PLAYER * > callback ( &Wrapper1<NETWORK_SERVER, NETWORK_PLAYER *, &NETWORK_SERVER::ConnectedUpdateClientInfo >, this );
    
    GAMEPLAY_ACTION_COMMAND_CLIENT_CONNECTED::ClientConnectedCallback = callback;
    
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
            
            PlayerTable[i]->AppendMessage( command->Clone() );
        }
    }
}

void NETWORK_SERVER::DispatchMessageToPlayer(NETWORK_PLAYER & player, CORE_DATA_STREAM & data_buffer) {
    
    abort();
    
    for(int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i ++ ) {
        
        if ( PlayerTable[i] != NULL && player.GetUniqueId() == PlayerTable[i]->GetUniqueId() ) {
            SERVICE_NETWORK_COMMAND * message = new SERVICE_NETWORK_COMMAND();
            
            PlayerTable[i]->AppendMessage( message );
        }
    }
}

void NETWORK_SERVER::DispatchMessageToPlayer(NETWORK_PLAYER & player, SERVICE_NETWORK_COMMAND * command) {
    
    for(int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i ++ ) {
        
        if ( PlayerTable[i] != NULL && player.GetUniqueId() == PlayerTable[i]->GetUniqueId() ) {
            
            PlayerTable[i]->AppendMessage( command );
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
            
            SERVICE_LOGGER_Warning( "NETWORK_SERVER Sending Accepted\n" );
            
            GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED
                accepted_command( PlayerTable[i] );
            
            auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand<GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED > ( accepted_command, 0 );
            
            PlayerTable[i]->AppendMessage( network_message );
            
            if ( Delegate ) {
                
                Delegate->OnClientConnected( player );
                ServerChanged();
            }
#if DEBUG
            else {
                SERVICE_LOGGER_Warning( "Add NETWORK_SERVER_DELEGATE" );
            }
#endif
            break;
        }
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
    
    for ( size_t i = 0; i < IncommingMessageQueue.size(); i++ ) {
        
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
    
    CORE_PARALLEL_LOCK Lock( ServerLock );
    
    //TODO: check race condition
    IncommingMessageQueue[IncommingMessageQueueIterator++] = command;
    
    assert( command != NULL && command->Data != NULL );
    
    if ( IncommingMessageQueueIterator == THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE ) {
        IncommingMessageQueueIterator = 0;
    }
}

void NETWORK_SERVER::ProcessIncommingMessages() {
    
    SERVICE_NETWORK_COMMAND * command = NULL;
    CORE_TIMELINE_EVENT * event = NULL;
    
    for ( size_t i = 0; i < IncommingMessageQueue.size(); i++ ) {
        
        command = IncommingMessageQueue[i];
        
        if ( command == NULL || command->Data == NULL ) {
            
            continue;
        }
        
        GAMEPLAY_ACTION_SYSTEM::GetInstance().DeSerializeNetworkCommand( command, &event );
        
        int type = ((GAMEPLAY_ACTION*) event->GetCommand())->GetCommandType();
        
        for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
            
            if ( type == (int) GAMEPLAY_ACTION_TYPE_GameLoaded ) {
                
                auto loaded_command = ( ( GAMEPLAY_ACTION_COMMAND_GAME_LOADED::PTR ) event->GetCommand() );
                for ( int pi = 0; pi < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; pi++ ) {
                    
                    if ( PlayerTable[ pi ] != NULL && PlayerTable[ pi ]->GetUniqueId() == loaded_command->Player->GetUniqueId() ) {
                        
                        PlayerTable[ pi ]->SetLoaded( true );
                        
                        StateMachine.DispatchEvent( CLIENT_LOADED_EVENT( PlayerTable[ pi ] ) );
                        
                        break;
                    }
                }
                
                command = NULL;
            }
            else if ( type == (int) GAMEPLAY_ACTION_TYPE_Clock ) {
                auto clock_command = ( ( GAMEPLAY_ACTION_COMMAND_CLOCK::PTR ) event->GetCommand() );
                for ( int pi = 0; pi < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; pi++ ) {
                    
                    if ( PlayerTable[ pi ] != NULL && PlayerTable[ pi ]->GetUniqueId() == clock_command->Player->GetUniqueId() ) {
                        
                        
                        int tick_offset = (GAMEPLAY_ACTION_SYSTEM::GetInstance().GetTimeline().GetTick() + 1) - clock_command->SentTick;
                        PlayerTable[ pi ]->SetPing( tick_offset * ( 1.0f / 30.0f ) );
                        
                        break;
                    }
                }
                
                command = NULL;
            }
            else if ( type == (int) GAMEPLAY_ACTION_TYPE_ClientQuit ) {
                
                SERVICE_LOGGER_Warning( "NETWORK_SERVER Received Client Quit\n" );
                
                for ( int pi = 0; pi < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; pi++ ) {
                    
                    if ( PlayerTable[ pi ] != NULL && PlayerTable[ pi ]->GetUniqueId() == ( ( GAMEPLAY_ACTION_COMMAND_CLIENT_QUIT::PTR ) event->GetCommand() )->GetClientIdentifier() ) {
                        
                        StateMachine.DispatchEvent( CLIENT_DISCONNECTED_EVENT( PlayerTable[ pi ] ) );
                        
                        PlayerTable[ pi ]->Finalize();
                        CORE_MEMORY_ObjectSafeDeallocation( PlayerTable[ pi ] );
                        PlayerTable[ pi ] = NULL;
                        
                        break;
                    }
                }
                
                command = NULL;
            }
            else if ( type >= (int) GAMEPLAY_ACTION_TYPE_Custom_1 && command ) {
                
                SERVICE_LOGGER_Warning( "NETWORK_SERVER Received Custom event\n" );
                // Assign the command to the player
                
                StateMachine.DispatchEvent( GAME_EVENT( event ) );
                
                command = NULL;
            }
        }
        
        if ( command != NULL ) {
            
            if ( type == (int) GAMEPLAY_ACTION_TYPE_ClientConnected ) {
                
                SERVICE_LOGGER_Warning( "NETWORK_SERVER Received Client connected\n" );
                
                if ( AcceptsConnections() ) {
                    
                    AcceptPlayerFromConnection( command->Connection );
                }
                else {
                    //TO Test
                    command->Connection->Stop();
                }
            }
            else if ( type == (int) GAMEPLAY_ACTION_TYPE_ClientReady ) {
                
                SERVICE_LOGGER_Warning( "NETWORK_SERVER Received Client ready\n" );
                
                if ( Delegate ) {
                    auto cmd = ( ( GAMEPLAY_ACTION_COMMAND_CLIENT_READY::PTR ) event->GetCommand() );
                    
                    Delegate->OnClientReady( cmd->Player, cmd->Ready );
                }
            }
            else if ( type == (int) GAMEPLAY_ACTION_TYPE_ServerInfo ||
                     type == (int) GAMEPLAY_ACTION_TYPE_ClientRejected ||
                     type == (int) GAMEPLAY_ACTION_TYPE_ServerQuit ||
                     type == (int) GAMEPLAY_ACTION_TYPE_GameStarting ||
                     type == (int) GAMEPLAY_ACTION_TYPE_LoadGame) {
            }
            else {
                abort();
            }
        }
        
        CORE_MEMORY_ObjectSafeDeallocation( IncommingMessageQueue[i] );
    }
}

void NETWORK_SERVER::ProcessAndSendOutgoingMessages() {
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        if ( PlayerTable[i] != NULL && PlayerTable[i]->GetNetworkConnexion() != NULL ) {
            
            UpdateLagValues();
            
            LobbyInstance->SendTcpCommand(
                                          PlayerTable[i]->PrepareMessage(),
                                          PlayerTable[i]->GetNetworkConnexion() );
        }
        else if ( PlayerTable[i] != NULL && PlayerTable[i]->GetNetworkConnexion() == NULL ) {
            
            std::array< SERVICE_NETWORK_COMMAND *, OUTGOING_MESSAGE_QUEUE_SIZE> & queue = PlayerTable[i]->GetOutGoingMessageQueue();
            
            for (int i = 0; i < OUTGOING_MESSAGE_QUEUE_SIZE; i++ ) {
                if ( queue[ i ] != NULL ) {
                    
                    OnTCPDataReceived( queue[ i ] );
                    queue[ i ] = NULL;
                }
            }
        }
    }
}

void NETWORK_SERVER::RejectPlayer( SERVICE_NETWORK_CONNECTION * connection ) {
    
    GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED
        command;
    CORE_DATA_STREAM
        stream;
    
    auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( command, 0 );
    
    stream.Open();
    network_message->Serialize( "command", stream );
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

void NETWORK_SERVER::ServerChanged() {
    
    LobbyInstance->UpdateDiscoverMessage( "XS_SERVER_ACCEPTS_CONNECTIONS" );
    SERVICE_LOGGER_Warning( "NETWORK_SERVER Sending Server changed\n" );
    DispatchMessageToAllPlayers( CreateInfo() );
}

void NETWORK_SERVER::SetReady( bool ready ){
    CurrentPlayer.SetIsReady( ready );
    
    ServerChanged();
}

void NETWORK_SERVER::SendStartingMessage() {
    
    //TODO change this
    if ( StartingGameCounter < 60 ) {
        
        if ( StartingGameTicTacCounter ) {
            
            StartingGameCounter++;
        }
        
        StartingGameTicTacCounter = !StartingGameTicTacCounter;
    }
    else {
        
        StateMachine.DispatchEvent(COUNTDOWN_FINISHED_EVENT());
    }
}

SERVICE_NETWORK_COMMAND * NETWORK_SERVER::CreateInfo() {
    
    GAMEPLAY_ACTION_COMMAND_SERVER_INFO
        command;
    CORE_DATA_STREAM
        stream;
    
    command.Info->PlayersCount = 0;
    for(int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i ++ ) {
        
        command.Info->PlayersCount++;
        command.Info->MaxPlayers = THIS_GAME_MAX_NETWORK_PLAYER_SIZE;
        
        if ( PlayerTable[i] != NULL ) {
            
            command.Players.push_back( PlayerTable[i] );
        }
    }
    
    if ( Delegate ) {
        
        Delegate->FillGameInfo( *command.Info );
    }
#if DEBUG
    else {
        SERVICE_LOGGER_Warning( "Add NETWORK_SERVER_DELEGATE" );
    }
#endif
    
    auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( command, 0 );
    
    stream.Open();
    network_message->Serialize( "command", stream );
    stream.Close();
    
    return network_message;
}

void NETWORK_SERVER::DisconnectAll() {
    
    GAMEPLAY_ACTION_COMMAND_SERVER_QUIT
        command;
    CORE_DATA_STREAM
        stream;
    
    auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( command, 0 );
    
    stream.Open();
    network_message->Serialize( "command", stream );
    stream.Close();
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        if ( PlayerTable[ i ] != NULL && PlayerTable[ i ]->GetUniqueId() != CurrentPlayer.GetUniqueId()) {
            
            SERVICE_LOGGER_Warning( "NETWORK_SERVER Sending Disconnect All\n" );
            PlayerTable[i]->AppendMessage( network_message );
        }
    }
}

void NETWORK_SERVER::UpdateLagValues() {
    
    GAMEPLAY_ACTION_COMMAND_CLOCK
        command;
    CORE_DATA_STREAM
        stream;
    
    SERVICE_LOGGER_Warning( "NETWORK_SERVER Sending Clock All\n" );
    
    for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++ ) {
        
        if ( PlayerTable[ i ] != NULL && PlayerTable[ i ]->GetUniqueId() != CurrentPlayer.GetUniqueId()) {
            
            command.Player = PlayerTable[ i ];
            command.SentTick = GAMEPLAY_ACTION_SYSTEM::GetInstance().GetTimeline().GetTick();
            command.AveragePing = PlayerTable[ i ]->GetPing();
            
            auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( command, 0 );
            
            stream.Reset();
            stream.Open();
            network_message->Serialize( "command", stream );
            stream.Close();
            
            PlayerTable[i]->AppendMessage( network_message );
        }
    }
}
