//
//  NETWORK_CLIENT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_CLIENT.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_CONNECTED.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_READY.h"
#include "GAMEPLAY_ACTION_COMMAND_CLIENT_QUIT.h"
#include "GAMEPLAY_ACTION_COMMAND_SERVER_INFO.h"
#include "GAMEPLAY_ACTION_COMMAND_LOAD_GAME.h"
#include "GAMEPLAY_ACTION_COMMAND_CLOCK.h"

//--State EVENT
CORE_FIXED_STATE_DefineStateEnterEvent( NETWORK_CLIENT::INITIAL_STATE )
    GetContext().ClientInstance->StartUDPListen();
CORE_FIXED_STATE_EndOfStateEvent()
//--END

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::INITIAL_STATE, UDP_RECEIVED_EVENT )
        SERVICE_NETWORK_COMMAND const * command = event.GetEventData();

        CORE_DATA_STREAM
            stream( ( char * ) command->Data, command->Size );

        char * txt = NULL;
        int size = 0;

        stream.OutputBytes( &txt, size );
        txt[ size ] = '\0';

        stream.Close();

        SERVICE_LOGGER_Error( "Message : %s\n", txt );

        if ( GetContext().Delegate ) {
            
            GetContext().Delegate->OnServerDiscovered( event.GetEventData() );
        }
    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::INITIAL_STATE, UDP_SERVER_SELECTED_EVENT )

        GetContext().ClientInstance->OnTCPNetworkCommandReceivedCallback = new CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >( &Wrapper1< NETWORK_CLIENT , SERVICE_NETWORK_COMMAND *, &NETWORK_CLIENT::OnTCPDataReceived >, &GetContext() );

        GetContext().ClientInstance->OnTcpConnectedCallback.Connect(Wrapper<NETWORK_CLIENT, &NETWORK_CLIENT::OnTcpConnection>, &GetContext());
        GetContext().ClientInstance->StartTCPConnexion(event.GetEventData());

    CORE_FIXED_STATE_EndOfStateEvent()
    //--END

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::INITIAL_STATE, TCP_CONNECTED_EVENT )
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().TCP_CHALLENGE_STATE);
    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

    //--State EVENT
    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::INITIAL_STATE, QUIT_EVENT )
        //StopUdpListen
        GetContext().ClientInstance->StopUDPListen();
    CORE_FIXED_STATE_EndOfStateEvent()
    //--State EVENT

//--State EVENT
CORE_FIXED_STATE_DefineStateLeaveEvent( NETWORK_CLIENT::INITIAL_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//--State EVENT

CORE_FIXED_STATE_DefineStateEnterEvent( NETWORK_CLIENT::TCP_CHALLENGE_STATE )
    GetContext().SendJoinRequestCommand();
CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::TCP_CHALLENGE_STATE, SERVER_ACCEPTED_CONNECTION_EVENT )

        if ( GetContext().Delegate ) {
            
            GetContext().Delegate->OnServerAccepted( event.GetEventData() );
        }

        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().CONNECTED_STATE);
    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::TCP_CHALLENGE_STATE, SERVER_REJECTED_CONNECTION_EVENT )
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().INITIAL_STATE);
    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::TCP_CHALLENGE_STATE, QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::TCP_CHALLENGE_STATE, GAME_EVENT )
        // Response either SERVER_REJECTED_CONNECTION_EVENT or SERVER_ACCEPTED_CONNECTION_EVENT
        event.GetEventData()->Complete();
    CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( NETWORK_CLIENT::TCP_CHALLENGE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateEnterEvent( NETWORK_CLIENT::CONNECTED_STATE )

CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::CONNECTED_STATE, SELF_QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::CONNECTED_STATE, SERVER_DISCONNECTED_EVENT )
        if ( GetContext().Delegate ) {
            
            GetContext().Delegate->OnServerDisconnected();
        }
    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::CONNECTED_STATE, QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::CONNECTED_STATE, SERVER_KICK_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::CONNECTED_STATE, GAME_EVENT )
        GAMEPLAY_ACTION_SYSTEM::GetInstance().ProcessEvent( event.GetEventData() );
    CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( NETWORK_CLIENT::CONNECTED_STATE )

CORE_FIXED_STATE_EndOfStateEvent()



CORE_FIXED_STATE_DefineStateEnterEvent( NETWORK_CLIENT::NETWORK_RECOVER_STATE )

CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::NETWORK_RECOVER_STATE, SELF_QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::NETWORK_RECOVER_STATE, QUIT_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()

    CORE_FIXED_STATE_DefineStateEvent( NETWORK_CLIENT::NETWORK_RECOVER_STATE, GAME_EVENT )

    CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( NETWORK_CLIENT::NETWORK_RECOVER_STATE )

CORE_FIXED_STATE_EndOfStateEvent()



NETWORK_CLIENT::NETWORK_CLIENT() :
    ClientInstance( NULL ),
    IncommingMessageQueue(),
    IncommingMessageQueueIterator(0),
    CurrentPlayer( 0, true ),
    NetworkRefreshRate(0.1f),
    AccumulatedRemaining( 0.0f ),
    Delegate( NULL ) {
    
}

NETWORK_CLIENT::~NETWORK_CLIENT() {
    
}

void NETWORK_CLIENT::Initialize() {

    ClientInstance = new SERVICE_NETWORK_LOBBY_CLIENT();
    ClientInstance->Initialize();
    
    CORE_FIXED_STATE_InitializeState( StateMachine, NETWORK_CLIENT::INITIAL_STATE, this );
    
    ClientInstance->OnUDPNetworkCommandReceivedCallback = new CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >( &Wrapper1< NETWORK_CLIENT , SERVICE_NETWORK_COMMAND *, &NETWORK_CLIENT::OnUDPDataReceived >, this );
    
    CORE_HELPERS_CALLBACK_1< NETWORK_PLAYER * >
        accepted_callback( &Wrapper1<NETWORK_CLIENT, NETWORK_PLAYER *, &NETWORK_CLIENT::SetClientIsConnected>, this );
    
    GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED::PlayerAcceptedCallback = accepted_callback;
    GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED::ClientFromServerConnectionResponseCallback = accepted_callback;
}

void NETWORK_CLIENT::Update( float time_step ) {
    
    AccumulatedRemaining += time_step;
    
    ClientInstance->Update( time_step );
    
    if ( NetworkRefreshRate > 0.0f ) {
        
        if ( AccumulatedRemaining > NetworkRefreshRate ) {
            
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

void NETWORK_CLIENT::Finalize() {
    
    Delegate = NULL;
    
    ClientInstance->Finalize();
    
    StateMachine.FinalizeState();
}

void NETWORK_CLIENT::OnTCPDataReceived( SERVICE_NETWORK_COMMAND * command ) {
    
    //TODO: check race condition
    IncommingMessageQueue[IncommingMessageQueueIterator++] = command;
    
    if ( IncommingMessageQueueIterator == THIS_GAME_MAX_NETWORK_MESSAG_QUEUE_SIZE ) {
        IncommingMessageQueueIterator = 0;
    }
}

void NETWORK_CLIENT::OnUDPDataReceived( SERVICE_NETWORK_COMMAND * command ) {
    
    StateMachine.DispatchEvent(UDP_RECEIVED_EVENT(command));
}

void NETWORK_CLIENT::SetClientIsConnected(NETWORK_PLAYER * player) {
    
    if ( player != NULL ) {
        CurrentPlayer.SetUniqueId( player->GetUniqueId() );
        StateMachine.DispatchEvent(SERVER_ACCEPTED_CONNECTION_EVENT(player));
    }
    else {
        StateMachine.DispatchEvent(SERVER_REJECTED_CONNECTION_EVENT());
    }
}

void NETWORK_CLIENT::DispatchMessageToAllPlayers( SERVICE_NETWORK_COMMAND * command ) {
    
    CurrentPlayer.AppendMessage(command);
}

void NETWORK_CLIENT::DispatchMessageToPlayer(NETWORK_PLAYER & player, CORE_DATA_STREAM & data_buffer) {
    
}

void NETWORK_CLIENT::DispatchMessageToServer( SERVICE_NETWORK_COMMAND * command ) {
    
    CurrentPlayer.AppendMessage( command );
}

void NETWORK_CLIENT::SelectServer(SERVICE_NETWORK_COMMAND * connexion) {
    
    StateMachine.DispatchEvent(UDP_SERVER_SELECTED_EVENT(connexion));
}

void NETWORK_CLIENT::OnTcpConnection() {
    
    StateMachine.DispatchEvent(TCP_CONNECTED_EVENT());
}

void NETWORK_CLIENT::ProcessIncommingMessages() {
    
    SERVICE_NETWORK_COMMAND * command = NULL;
    CORE_TIMELINE_EVENT * event = NULL;
    
    for ( size_t i = 0; i < IncommingMessageQueue.size(); i++ ) {
        
        command = IncommingMessageQueue[i];
        
        if ( command == NULL ) {
            
            continue;
        }
        
        GAMEPLAY_ACTION_SYSTEM::GetInstance().DeSerializeNetworkCommand( command, &event );
        
        int type = ((GAMEPLAY_ACTION*) event->GetCommand())->GetCommandType();
        
        
        if ( type == (int) GAMEPLAY_ACTION_TYPE_LoadGame ) {
            
            auto cmd = ((GAMEPLAY_ACTION_COMMAND_LOAD_GAME*) event->GetCommand());
            Delegate->OnLoadGame( cmd->Players );
        }
        else if ( type == (int) GAMEPLAY_ACTION_TYPE_GameStarting ) {
            
            event->Complete();
        }
        else if ( type == (int) GAMEPLAY_ACTION_TYPE_GameStarting ) {
            
            event->Complete();
        }
        else if ( type == (int) GAMEPLAY_ACTION_TYPE_ServerQuit ) {
            
            SERVICE_LOGGER_Warning( "NETWORK_CLIENT Received Server Quit\n" );
            StateMachine.DispatchEvent( SERVER_DISCONNECTED_EVENT() );
        }
        else if ( type == (int) GAMEPLAY_ACTION_TYPE_ServerInfo ) {
            
            SERVICE_LOGGER_Warning( "NETWORK_CLIENT Received Server Info\n" );
            Delegate->OnServerInfo( ((GAMEPLAY_ACTION_COMMAND_SERVER_INFO*) event->GetCommand()) );
        }
        else if ( type == (int) GAMEPLAY_ACTION_TYPE_Clock ) {
            
            GAMEPLAY_ACTION_COMMAND_CLOCK
                clock_command;
            auto from_command = (GAMEPLAY_ACTION_COMMAND_CLOCK::PTR)((GAMEPLAY_ACTION*) event->GetCommand());
            
            clock_command.Player = from_command->Player;
            clock_command.SentTick = from_command->SentTick;
            
            Delegate->OnPingUpdated( from_command->AveragePing );
            
            auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( clock_command, -1 );
            
            CurrentPlayer.AppendMessage( network_message );
        }
        else {
            
            SERVICE_LOGGER_Warning( "NETWORK_CLIENT Received Game event Local tick : %d - Remote tick : %d\n", GAMEPLAY_ACTION_SYSTEM::GetInstance().GetTimeline().GetTick(), event->GetTick() );
            StateMachine.DispatchEvent(GAME_EVENT(event));
        }
        
        CORE_MEMORY_ObjectSafeDeallocation( IncommingMessageQueue[i] );
    }
}

void NETWORK_CLIENT::ProcessAndSendOutgoingMessages() {
    
    ClientInstance->SendTcpCommand(
        CurrentPlayer.PrepareMessage(),
        CurrentPlayer.GetNetworkConnexion() );
}

void NETWORK_CLIENT::SendJoinRequestCommand() {
    
    GAMEPLAY_ACTION_COMMAND_CLIENT_CONNECTED
        command;
    
    command.SetPlayer( &CurrentPlayer );
    
    auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( command, 0 );
    
    CurrentPlayer.AppendMessage( network_message );
}

void NETWORK_CLIENT::SendDisconnectCommand() {
    
    GAMEPLAY_ACTION_COMMAND_CLIENT_QUIT
        command( CurrentPlayer.GetUniqueId() );
    
    auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( command, 0 );
    
    StateMachine.ChangeState( INITIAL_STATESTATE );
    
    CurrentPlayer.AppendMessage( network_message );
}

void NETWORK_CLIENT::SendReadyCommand( bool ready ) {
    
    GAMEPLAY_ACTION_COMMAND_CLIENT_READY
        command;
    
    command.Player = &CurrentPlayer;
    command.Ready = ready;
    
    auto network_message = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand( command, 0 );
    
    CurrentPlayer.AppendMessage( network_message );
}

