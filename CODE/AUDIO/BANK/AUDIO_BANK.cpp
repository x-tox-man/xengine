//
//  AUDIO_SOUND_BANK.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "AUDIO_BANK.h"
#include "AUDIO_LOADER.h"
#include "AUDIO_SYSTEM.h"

AUDIO_SOUND_BANK::AUDIO_SOUND_BANK() :
    SoundTable() {

}

AUDIO_SOUND_BANK::~AUDIO_SOUND_BANK() {
    
}

void AUDIO_SOUND_BANK::RegisterSoundFilePath( const CORE_FILESYSTEM_PATH & sound_path, CORE_HELPERS_IDENTIFIER sound_identifier, const AUDIO_BANK_SOUND_LOAD_OPTION & option, const char * type ) {
    
    
    SoundTable[ sound_identifier ] = new AUDIO_BANK_SOUND( option );
    SoundTable[ sound_identifier ]->SoundPath = sound_path;
    SoundTable[ sound_identifier ]->SoundFileType = type;
}

void AUDIO_SOUND_BANK::PlaySound( const CORE_HELPERS_IDENTIFIER sound_identifier ) {
    
    AUDIO_SOUND * sound = SoundTable[ sound_identifier ]->Sound;
    
    if ( sound->GetSoundChunksTable().size() > 1 ) {
        
        AUDIO_SYSTEM::GetInstance().PlayMusic( sound_identifier );
    }
    else {
        
        AUDIO_SYSTEM::GetInstance().PlaySound( *( sound ) );
    }
}

void AUDIO_SOUND_BANK::Load() {
    
    std::map< CORE_HELPERS_IDENTIFIER, AUDIO_BANK_SOUND *>::iterator it = SoundTable.begin();
    
    while ( it != SoundTable.end() ) {
        
        AUDIO_LOADER_Open( it->second->SoundPath, it->second->SoundFileType, *it->second->Sound, *it->second->Option );
        
        if ( it->second->Option->ItStreams && it->second->Option->ItLoadAtStartup ) {
            
            it->second->Sound->GetSoundChunksTable().resize( 3 );
            
            it->second->Sound->GetSoundChunksTable()[0] = new AUDIO_SOUND_CHUNK;
            it->second->Sound->GetSoundChunksTable()[1] = new AUDIO_SOUND_CHUNK;
            it->second->Sound->GetSoundChunksTable()[2] = new AUDIO_SOUND_CHUNK;
            
            it->second->Sound->GetSoundChunksTable()[0]->Index = 0;
            it->second->Sound->GetSoundChunksTable()[1]->Index = 1;
            it->second->Sound->GetSoundChunksTable()[2]->Index = 2;
            it->second->Sound->SetIsOpen( true );
            
            AUDIO_LOADER_ReadChunk( *it->second->Sound, 0 );
            AUDIO_LOADER_ReadChunk( *it->second->Sound, 1 );
            AUDIO_LOADER_ReadChunk( *it->second->Sound, 2 );
        }
        else if ( it->second->Option->ItLoadAtStartup ) {
            
            it->second->Sound->GetSoundChunksTable().resize( 1 );
            it->second->Sound->GetSoundChunksTable()[0] = new AUDIO_SOUND_CHUNK;
            it->second->Sound->GetSoundChunksTable()[0]->Index = 0;
            
            AUDIO_LOADER_ReadChunk( *it->second->Sound, 0 );
            AUDIO_LOADER_Close( *it->second->Sound );
            it->second->Sound->SetIsOpen( false );
        }
        
        it++;
    }
}

void AUDIO_SOUND_BANK::Unload() {
    
    std::map< CORE_HELPERS_IDENTIFIER, AUDIO_BANK_SOUND *>::iterator it = SoundTable.begin();
    
    while ( it != SoundTable.end() ) {
        
        if ( it->second->Sound->IsOpen() ) {
            
            AUDIO_LOADER_Close( *it->second->Sound );
            
            for ( size_t i = 0; i < it->second->Sound->GetSoundChunksTable().size(); i++ ) {
                
                delete it->second->Sound->GetSoundChunksTable()[i];
            }
            
            delete it->second->Sound;
        }
        
        it++;
    }
}