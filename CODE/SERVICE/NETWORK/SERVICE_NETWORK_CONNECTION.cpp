//
//  SERVICE_NETWORK_CONNECTION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "SERVICE_NETWORK_CONNECTION.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "SERVICE_NETWORK_COMMAND.h"
#define MAX_BUFFFER_SIZE 65535

SERVICE_NETWORK_CONNECTION::SERVICE_NETWORK_CONNECTION() :
    Info(),
    UVConnection(),
    BroadcastAddress(),
    SocketConnectionAddress(),
    TcpClientCommunicationThread(),
    TcpCommunicationTask( NULL ),
    SelfLoop( NULL ),
    ListenCallback( NULL ),
    ConnexionLock() {
    
}

SERVICE_NETWORK_CONNECTION::~SERVICE_NETWORK_CONNECTION() {

}

void SERVICE_NETWORK_CONNECTION::UDPReceivePacket(uv_udp_t *req, ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags) {
    
    if ( nread < 0 ) {
        
        fprintf( stderr, "Read error %s\n", uv_err_name( (int)nread ) );
        
        uv_close( ( uv_handle_t * ) req, NULL );
        CORE_MEMORY_ALLOCATOR_Free( buf->base );
        
        return;
    }
    
    SERVICE_NETWORK_COMMAND * command = new SERVICE_NETWORK_COMMAND;
    
    if ( addr != NULL ) {
        
        char sender[17] = { 0 };
        
        uv_ip4_name( (const struct sockaddr_in*) addr, sender, 16);
        
        fprintf(stderr, "Recv from %s\n", sender);
        
        int j = 0;
        int k = 0;
        int l = 0;
        
        for (int i = 0; i < 17; i++ ) {
            
            if ( sender[i] == '.' ) {
                
                sender[i] =  '\0';
                
                if ( j == 0 ) {
                    j = i+1 ;
                }
                else if ( k == 0 ) {
                    k = i+1 ;
                }
                else if ( l == 0 ) {
                    l = i+1 ;
                }
            }
        }
        
        command->Address[0] = atoi( &sender[ 0 ] );
        command->Address[1] = atoi( &sender[ j ] );
        command->Address[2] = atoi( &sender[ k ] );
        command->Address[3] = atoi( &sender[ l ] );
    }
    
    command->Size = (int) nread;
    command->Data = ( void * ) buf->base;
    
    
    if ( *((int*)buf->base) > 0 && *((int*)buf->base) < 409600 ) {
        
        (*SERVICE_NETWORK_SYSTEM::GetInstance().OnUPDDataReceivedCallback)( command );
    }
    
    //uv_close( ( uv_handle_t * ) req, NULL );
}

void SERVICE_NETWORK_CONNECTION::InitializeCommunicationThread() {
    
    ListenCallback = new CORE_HELPERS_CALLBACK( &Wrapper< SERVICE_NETWORK_CONNECTION, &SERVICE_NETWORK_CONNECTION::Listen >, this );
    
    TcpCommunicationTask =  new CORE_PARALLEL_TASK ( ListenCallback );
    
    TcpClientCommunicationThread.Initialize("TCP client thread", *TcpCommunicationTask );
    TcpClientCommunicationThread.Start();
}

void SERVICE_NETWORK_CONNECTION::Listen() {
    
    while ( true ) {
        
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(ConnexionLock)
        if ( SelfLoop ) {
            
            SERVICE_NETWORK_SYSTEM::GetInstance().Update( false, SelfLoop );
        }
        else {
            SERVICE_NETWORK_SYSTEM::GetInstance().Update( false, SERVICE_NETWORK_SYSTEM::GetInstance().Loop );
        }
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    }
}

void SERVICE_NETWORK_CONNECTION::TCPReceivePacket(uv_stream_t *req, ssize_t nread, const uv_buf_t *buf ) {
    
    if ( nread > 0 && buf->len > 0 ) {
        
        CORE_DATA_STREAM
            stream(buf->base, nread );
        
        unsigned int stream_size = 0;
        
        stream >> stream_size;
        
        if ( stream_size == 4 || stream_size > 65536 || strncmp(((char*)stream.GetMemoryBuffer() + stream_size + 8 ), "--END--", 7 ) != 0 ) {
            
            SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION rejected network message\n" );
            
            return;
        }
        
        do {
            
            SERVICE_NETWORK_COMMAND * command = new SERVICE_NETWORK_COMMAND;
            
            command->UnSerialize( "command", stream);
            
            (*SERVICE_NETWORK_SYSTEM::GetInstance().OnTCPDataReceivedCallback)( command, req );
        } while ( strncmp(((char*)stream.GetMemoryBuffer() + stream.GetOffset() + 8 ), "--END--", 7 ) != 0 );
    }
    
    // TODO: Clean memory
}

void SERVICE_NETWORK_CONNECTION::UDPSend( uv_udp_send_t* req, int status ) {
    
    SERVICE_LOGGER_Info( "SERVICE_NETWORK_CONNECTION udp send 1.5\n" );

    #if !PLATFORM_WINDOWS
        SERVICE_LOGGER_Info( "SERVICE_NETWORK_CONNECTION udp send %s %d\n", (char*)req->bufsml[0].base , req->bufsml[0].len );
    #endif
}

void SERVICE_NETWORK_CONNECTION::TCPSend( uv_write_t* req, int status ) {
    
    //SERVICE_LOGGER_Info( "SERVICE_NETWORK_CONNECTION tcp send %s %d\n", (char*)req->bufsml[0].base , req->bufsml[0].len );
}

void SERVICE_NETWORK_CONNECTION::AllocateReceiveBuffer( uv_handle_t * handle, size_t suggested_size, uv_buf_t * buf ) {
    
    // TODO: Release memory
    
    buf->base = (char*) CORE_MEMORY_ALLOCATOR_Allocate(suggested_size);
    buf->len = suggested_size;
    
    /*static char Buffer[2048];
    static char * AlternateBuffer;
    static int size = 0;
    
    if ( suggested_size < 2048 ) {
        
        buf->len = suggested_size;
        buf->base = Buffer;
    }
    else {
        
        if ( suggested_size > size ) {
            
            if ( size > 0 ) {
                
                CORE_MEMORY_ALLOCATOR_Free(  AlternateBuffer );
            }
            
            AlternateBuffer = (char *) CORE_MEMORY_ALLOCATOR::Allocate( suggested_size );
            buf->base = AlternateBuffer;
            buf->len = suggested_size;
            size = (int) suggested_size;
        }
        else {
            
            buf->base = AlternateBuffer;
            buf->len = suggested_size;
        }
        
    }*/
}
void SERVICE_NETWORK_CONNECTION::TCPConnectionCallback(uv_connect_t* req, int status) {
    
    OnNewConnexionCallback(req);
}

void SERVICE_NETWORK_CONNECTION::OnTCPAccesNewConnection( uv_stream_t * server, int status ) {
    
    if ( status < 0 ) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    
    SERVICE_LOGGER_Warning( "SERVICE_NETWORK_CONNECTION TCPNewConnection" );
    
    SERVICE_NETWORK_SYSTEM::GetInstance().NewConnection( server );
}

void SERVICE_NETWORK_CONNECTION::TCPClose( uv_handle_t* handle ) {
    
}

void SERVICE_NETWORK_CONNECTION::Start() {
    
    switch ( Info.ConnectionType ) {
            
        case SERVICE_NETWORK_CONNECTION_TYPE_Udp:
            SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION Start\n" );
            if ( Info.ItIsReceiver ) {
                SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION Start\n" );
                UV_CHECK_ERROR( uv_udp_recv_start( &UVConnection.UDPType.UDPSocket, AllocateReceiveBuffer, UDPReceivePacket ); )
            }
            
            break;
            
        case SERVICE_NETWORK_CONNECTION_TYPE_Tcp:
            
            if ( Info.ItIsReceiver ) {
                
                UV_CHECK_ERROR( uv_listen( (uv_stream_t*) &UVConnection.TCPType.TCPSocket, 0, OnTCPAccesNewConnection); )
            }
            break;
            
        default :
            
            SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION Start error" );
            CORE_RUNTIME_Abort();
            break;
    }
}

void SERVICE_NETWORK_CONNECTION::Stop() {
    
    switch ( Info.ConnectionType ) {
            
        case SERVICE_NETWORK_CONNECTION_TYPE_None: {
            
            break;
        }
            
        case SERVICE_NETWORK_CONNECTION_TYPE_Udp: {
            
            if( Info.ItIsReceiver ) {
                // TODO: Check this
                UV_CHECK_ERROR( uv_udp_recv_stop( &UVConnection.UDPType.UDPSocket ); )
            }
            
            uv_close( (uv_handle_t *) &UVConnection.UDPType.UDPSocket, TCPClose );
            Info.ConnectionType = SERVICE_NETWORK_CONNECTION_TYPE_None;
            
            break;
        }
            
        case SERVICE_NETWORK_CONNECTION_TYPE_Tcp: {
            
            uv_close( (uv_handle_t *) &UVConnection.TCPType.TCPSocket, TCPClose );
            Info.ConnectionType = SERVICE_NETWORK_CONNECTION_TYPE_None;
            
            break;
        }
            
        default : {
            
            break;
        }
    }
}

void SERVICE_NETWORK_CONNECTION::Receive() {
    
    switch ( Info.ConnectionType ) {
            
        case SERVICE_NETWORK_CONNECTION_TYPE_Udp: {
            
            break;
        }
            
        case SERVICE_NETWORK_CONNECTION_TYPE_Tcp: {
            
            break;
        }
            
        default : {
            
            SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION Receive error" );
            CORE_RUNTIME_Abort();
            break;
        }
    }
}

void SERVICE_NETWORK_CONNECTION::Send( const CORE_DATA_STREAM & data_to_send ) {
    
#if DEBUG
    if ( data_to_send.GetSize() <= 0 && data_to_send.GetAllocatedBytes() <= 0 ) {
        
        SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION Send error" );
        
        return;
    }
#endif
    int size = data_to_send.GetSize();
    
    if ( size == 0 ) {
        
        size = data_to_send.GetAllocatedBytes();
    
        if ( size == 0 ){
            return;
        }
    }
    
    switch ( Info.ConnectionType ) {
            
        case SERVICE_NETWORK_CONNECTION_TYPE_Udp: {
            
            UVConnection.UDPType.Buffer = uv_buf_init((char*)data_to_send.GetMemoryBuffer(), (unsigned int) size );
            
            //SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION udp Send 0.2 %x %x %x size %d\n", &UVConnection.UDPType.UDPRequest, &UVConnection.UDPType.UDPSocket, &UVConnection.TCPType.Buffer, size );
            
            //SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION udp Send 1 %x %x %x\n", &UVConnection.UDPType.UDPRequest, UVConnection.UDPType.UDPSocket, &UVConnection.TCPType.Buffer, &SocketConnectionAddress.sin_port );
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(ConnexionLock)
                UV_CHECK_ERROR( uv_udp_send(
                    &UVConnection.UDPType.UDPRequest,
                    &UVConnection.UDPType.UDPSocket,
                    &UVConnection.UDPType.Buffer,
                    1,
                    (const struct sockaddr *) &SocketConnectionAddress,
                    UDPSend ); )
            CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()

            break;
        }
    
        case SERVICE_NETWORK_CONNECTION_TYPE_TcpAccept:
        case SERVICE_NETWORK_CONNECTION_TYPE_Tcp: {
            UVConnection.TCPType.Buffer = uv_buf_init((char*)data_to_send.GetMemoryBuffer(), size );
            
            SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION tcp Send 1" );
            
            if ( SelfLoop ) {
                
                CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(ConnexionLock)
                
                    UV_CHECK_ERROR( uv_write( &UVConnection.TCPType.TCPRequest, (uv_stream_t*) &UVConnection.TCPType.TCPSocket, &UVConnection.TCPType.Buffer, 1, SERVICE_NETWORK_CONNECTION::TCPSend); )
                CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
                
            }
            else {
                CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(ConnexionLock)
                    UV_CHECK_ERROR( uv_write( &UVConnection.TCPType.TCPRequest, (uv_stream_t*) &UVConnection.TCPType.TCPSocket, &UVConnection.TCPType.Buffer, 1, SERVICE_NETWORK_CONNECTION::TCPSend); )
                CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
            }
            
            break;
        }
            
        default : {

            SERVICE_LOGGER_Error( "SERVICE_NETWORK_CONNECTION Send error default" );
            CORE_RUNTIME_Abort();
            break;
        }
    }
}

CORE_HELPERS_CALLBACK_1<uv_connect_t*>
    SERVICE_NETWORK_CONNECTION::OnNewConnexionCallback;
