//
//  PERIPHERIC_INTERACTION_KEYBOARD.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "PERIPHERIC_INTERACTION_KEYBOARD.h"

PERIPHERIC_INTERACTION_KEYBOARD::PERIPHERIC_INTERACTION_KEYBOARD() :
    KeyTable() {
    
}

PERIPHERIC_INTERACTION_KEYBOARD::~PERIPHERIC_INTERACTION_KEYBOARD() {

}

void PERIPHERIC_INTERACTION_KEYBOARD::Initialize() {
    
    for ( int key = 0; key < KEYBOARD_KEY_Count; key++ ) {
        
        KeyTable[ key ] = KEY_STATE_Up;
    }
}

void PERIPHERIC_INTERACTION_KEYBOARD::Update() {
    
    for ( int key = 0; key < KEYBOARD_KEY_Count; key++ ) {
        
        KeyTable[ key ] = KeyTable[ key ] & ~KEY_STATE_Released;
    }
}

bool PERIPHERIC_INTERACTION_KEYBOARD::IsKeyPressed( const KEYBOARD_KEY key ) {
    
    return KeyTable[ key ] & KEY_STATE_Pressed;
}

bool PERIPHERIC_INTERACTION_KEYBOARD::IsKeyReleased( const KEYBOARD_KEY key ) {
    
    return KeyTable[ key ] & KEY_STATE_Released;
}

void PERIPHERIC_INTERACTION_KEYBOARD::SetKeyPressed( const KEYBOARD_KEY key ) {
    
    KeyTable[ key ] = KeyTable[ key ] | KEY_STATE_Pressed;
    KeyTable[ key ] = KeyTable[ key ] & ~KEY_STATE_Released;
}

void PERIPHERIC_INTERACTION_KEYBOARD::SetKeyReleased( const KEYBOARD_KEY key ) {
    
    KeyTable[ key ] = KeyTable[ key ] | KEY_STATE_Released;
    KeyTable[ key ] = KeyTable[ key ] & ~KEY_STATE_Pressed;
}

KEYBOARD_KEY PERIPHERIC_INTERACTION_KEYBOARD::KeyFromCode( int code ) {

    return (KEYBOARD_KEY) code;
}