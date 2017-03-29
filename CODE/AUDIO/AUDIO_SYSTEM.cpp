//
//  AUDIO_SYSTEM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "AUDIO_SYSTEM.h"
#include "AUDIO_LOADER.h"
#include "AUDIO_SOUND_LOADER_MPG123.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( AUDIO_SYSTEM )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD( AUDIO_SYSTEM &, AUDIO_SYSTEM, GetInstance )
    //CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( AUDIO_SYSTEM, PlaySound, CORE_HELPERS_IDENTIFIER )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( AUDIO_SYSTEM, PlaySound, const char * )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( AUDIO_SYSTEM, PlayMusic, const char * )
    //CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( AUDIO_SYSTEM, PlayMusic, CORE_HELPERS_IDENTIFIER )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( AUDIO_SYSTEM )

AUDIO_SYSTEM::~AUDIO_SYSTEM() {

    if ( Interface ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( Interface );
    }
    
    Bank.Unload();
    
    if ( PlayingMusic ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( PlayingMusic );
    }
}

void AUDIO_SYSTEM::Initialize() {
    
    SERVICE_LOGGER_Error( "AUDIO_SYSTEM Initialize 0" );
#if __AUDIO_OPENAL__
    Interface = new AUDIO_OPENAL();
#elif __AUDIO_OPENSL__
    Interface = new AUDIO_OPENSL();
#endif
    SERVICE_LOGGER_Error( "AUDIO_SYSTEM Initialize 1" );
    Interface->Initialize();
    SERVICE_LOGGER_Error( "AUDIO_SYSTEM Initialize 2" );
    #ifdef AUDIO_MPG
        MPG_123_Init();
    #endif
    
    PlayingMusic = NULL;
}

void AUDIO_SYSTEM::PlaySound( AUDIO_SOUND & sound) {
    
    Interface->PlaySound( sound );
}

void AUDIO_SYSTEM::PlaySound( const CORE_HELPERS_IDENTIFIER & sound_identifier ) {
    
    AUDIO_BANK_SOUND & sound = *Bank.GetSound( sound_identifier );
    
    Interface->PlaySound( *sound.Sound );
}

void AUDIO_SYSTEM::PlaySound( const char * sound_identifier ) {
    
    Interface->PlaySound( *Bank.GetSound( CORE_HELPERS_IDENTIFIER( sound_identifier ) )->Sound );
}

void AUDIO_SYSTEM::PlayMusic( const char * sound_identifier ) {
    
    PlayMusic( CORE_HELPERS_IDENTIFIER( sound_identifier ) );
}

void AUDIO_SYSTEM::PlayMusic( const CORE_HELPERS_IDENTIFIER & sound_identifier ) {
    
    AUDIO_BANK_SOUND & sound = *Bank.GetSound( sound_identifier );
    
    if ( PlayingMusic != NULL ) {
        
        Interface->StopSound( *PlayingMusic );
        
        if ( PlayingMusic->IsOpen() ) {
            
            PlayingMusic->SetIsOpen( false );
            PlayingMusic->SetCurrentChunkIndex( 0 );
            
            AUDIO_LOADER_Close( *PlayingMusic );
        }
    }
    
    PlayingMusic = sound.Sound;
    
    if ( !sound.Sound->IsOpen() ) {
        
        AUDIO_LOADER_Open( sound.SoundPath, sound.SoundFileType, *sound.Sound, *sound.Option );
        
        AUDIO_LOADER_ReadChunk( *sound.Sound, 0 );
        AUDIO_LOADER_ReadChunk( *sound.Sound, 1 );
        AUDIO_LOADER_ReadChunk( *sound.Sound, 2 );
    }
    
    Interface->PlaySound( *sound.Sound );
}

void AUDIO_SYSTEM::OnSoundIsRead() {
    
    Interface->OnSoundIsRead();
}

void AUDIO_SYSTEM::Update( const float time_step ) {
    
    Interface->Update( time_step );
}

void AUDIO_SYSTEM::Finalize() {
    
    if ( PlayingMusic ) {
        
        Interface->StopSound( *PlayingMusic );

        PlayingMusic = NULL;
    }
    
    Bank.Unload();
    
    Interface->Finalize();
}

AUDIO_SYSTEM::AUDIO_SYSTEM() :
    Bank() {
        
}
