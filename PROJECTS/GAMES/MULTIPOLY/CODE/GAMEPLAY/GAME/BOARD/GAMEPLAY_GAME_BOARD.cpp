//
//  GAMEPLAY_GAME_BOARD.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_GAME_BOARD.h"
#include "GLOBAL_RESOURCES.h"
#include "GAMEPLAY_RULE_START.h"
#include "GAMEPLAY_RULE_CAISSE.h"
#include "GAMEPLAY_RULE_PROPERTY.h"
#include "GAMEPLAY_RULE_STATION.h"
#include "GAMEPLAY_RULE_PRISON.h"
#include "GAMEPLAY_RULE_CHANCE.h"
#include "GAMEPLAY_RULE_PARK.h"
#include "GAMEPLAY_RULE_PAY_AMOUNT.h"

GAMEPLAY_GAME_BOARD::GAMEPLAY_GAME_BOARD() :
    CellTable() {
    
}

GAMEPLAY_GAME_BOARD::~GAMEPLAY_GAME_BOARD() {
    
}

void GAMEPLAY_GAME_BOARD::Initialize( GAMEPLAY_SCENE * scene ) {

    int
        index = 0;
    std::array< GAMEPLAY_GAME_BOARD_CELL *, 40 >::iterator
        it = CellTable.begin();
    CORE_MATH_VECTOR
        position( 0.0f, 0.0f),
        offset(1.0f, 0.0f),
        offset_position( 0.0f, 0.0f );
    CORE_MATH_QUATERNION
        orientation(0.0f, 0.0f, M_PI_2, 0.0f);
    GRAPHIC_TEXTURE
        * texture = GLOBAL_RESOURCES::CreateTextureFromImagePath( "monopoly-nintendo-plateau" );
    std::array< GAMEPLAY_RULE *, 40 >
        rules_table;
    std::array< GAMEPLAY_RULE *, 40 >::iterator rules_iterator;
    
    CreateRules( rules_table );
    
    rules_iterator = rules_table.begin();
    
    while ( it != CellTable.end() ) {
        
        const float
            half_size = 0.5f;
        bool
            corner = (index % 10 == 0 );
        bool
            is_border_x = index < 10 || ( index >= 20 && index < 30 );
        float
            size_x = half_size * 2.0f,
            size_y = half_size * 2.0f;
        CORE_MATH_VECTOR
            size(size_x, size_y);
        const float
            twice_offset = 0.130859375f,
            single_offset = 0.08203125f;
        
        
        *it = new GAMEPLAY_GAME_BOARD_CELL();
        (*it)->SetRule( *rules_iterator );
        
        auto tb = new GRAPHIC_TEXTURE_BLOCK();
        tb->SetTexture(texture );
        
        if ( corner ) {
            
            tb->SetSize( CORE_MATH_VECTOR( twice_offset, -twice_offset ) );
        }
        else {
            
            if ( is_border_x ) {
                
                tb->SetSize( CORE_MATH_VECTOR( single_offset, -twice_offset ) );
            }
            else {
            
                tb->SetSize( CORE_MATH_VECTOR( twice_offset, -single_offset ) );
            }
        }
        
        if ( index == 0 ) {
            
            offset_position.X( 1.0f - tb->GetSize().X());
            offset_position.Y( -tb->GetSize().Y() );
            
            orientation.Z( -2.0f * M_PI_2 );
        }
        else if( index < 10 ) {
            
            offset_position.X( offset_position.X() - tb->GetSize().X());
        }
        else if( index == 10 ) {
            
            offset_position.X( 0.0f );
            offset_position.Y( -tb->GetSize().Y() );
        }
        else if ( index < 20 ) {
            
            offset_position.Y( offset_position.Y() - tb->GetSize().Y() );
        }
        else if( index == 20 ) {
            
            offset_position.X( 0.0f );
            offset_position.Y( 1.0f );
        }
        else if ( index < 30) {
           
            offset_position.X( offset_position.X() + tb->GetSize().X());
        }
        else if ( index == 30) {
            
            offset_position.X( 1.0f - tb->GetSize().X() );
            offset_position.Y( 1.0f );
        }
        else {
            
            offset_position.Y( offset_position.Y() + tb->GetSize().Y() );
        }
        
        tb->SetOffset( offset_position );
        
        (*it)->Initialize( position, size, orientation, scene, tb, corner );
        
        if ( index < 20 ) {
            
            position.Set(position.X() + ((is_border_x)?size_x : 0.0f), position.Y() + ((is_border_x) ? 0.0f : size_x), position.Z(), position.W());
        }
        else {
            
            position.Set( position.X() - ((is_border_x)?size_x : 0.0f), position.Y() - ((is_border_x) ? 0.0f : size_x), position.Z(), position.W() );
        }
        
        it++;
        index++;
        rules_iterator++;
    }
}

void GAMEPLAY_GAME_BOARD::CreateRules( std::array< GAMEPLAY_RULE *, 40 > & rules_table ) {
    
    rules_table[0] = new GAMEPLAY_RULE_START();
    rules_table[1] = new GAMEPLAY_RULE_PROPERTY( 60 );
    rules_table[2] = new GAMEPLAY_RULE_CAISSE();
    rules_table[3] = new GAMEPLAY_RULE_PROPERTY( 60 );
    rules_table[4] = new GAMEPLAY_RULE_PAY_AMOUNT( 200 );
    rules_table[5] = new GAMEPLAY_RULE_STATION( 200 );
    rules_table[6] = new GAMEPLAY_RULE_PROPERTY( 100 );
    rules_table[7] = new GAMEPLAY_RULE_CHANCE();
    rules_table[8] = new GAMEPLAY_RULE_PROPERTY( 100 );
    rules_table[9] = new GAMEPLAY_RULE_PROPERTY( 120 );
    
    rules_table[10] = new GAMEPLAY_RULE_PRISON( false );
    rules_table[11] = new GAMEPLAY_RULE_PROPERTY( 140 );
    rules_table[12] = new GAMEPLAY_RULE_PROPERTY( 150 );
    rules_table[13] = new GAMEPLAY_RULE_PROPERTY( 140 );
    rules_table[14] = new GAMEPLAY_RULE_PROPERTY( 160 );
    rules_table[15] = new GAMEPLAY_RULE_STATION( 200 );
    rules_table[16] = new GAMEPLAY_RULE_PROPERTY( 180 );
    rules_table[17] = new GAMEPLAY_RULE_CAISSE();
    rules_table[18] = new GAMEPLAY_RULE_PROPERTY( 180 );
    rules_table[19] = new GAMEPLAY_RULE_PROPERTY( 200 );
    
    rules_table[20] = new GAMEPLAY_RULE_PARK();
    rules_table[21] = new GAMEPLAY_RULE_PROPERTY( 220 );
    rules_table[22] = new GAMEPLAY_RULE_CHANCE();
    rules_table[23] = new GAMEPLAY_RULE_PROPERTY( 220 );
    rules_table[24] = new GAMEPLAY_RULE_PROPERTY( 240 );
    rules_table[25] = new GAMEPLAY_RULE_STATION( 200 );
    rules_table[26] = new GAMEPLAY_RULE_PROPERTY( 260 );
    rules_table[27] = new GAMEPLAY_RULE_PROPERTY( 260 );
    rules_table[28] = new GAMEPLAY_RULE_PROPERTY( 150 );
    rules_table[29] = new GAMEPLAY_RULE_PROPERTY( 280 );
    
    rules_table[30] = new GAMEPLAY_RULE_PRISON( true );
    rules_table[31] = new GAMEPLAY_RULE_PROPERTY( 300 );
    rules_table[32] = new GAMEPLAY_RULE_PROPERTY( 300 );
    rules_table[33] = new GAMEPLAY_RULE_CAISSE();
    rules_table[34] = new GAMEPLAY_RULE_PROPERTY( 320 );
    rules_table[35] = new GAMEPLAY_RULE_STATION( 200 );
    rules_table[36] = new GAMEPLAY_RULE_CHANCE();
    rules_table[37] = new GAMEPLAY_RULE_PROPERTY( 350 );
    rules_table[38] = new GAMEPLAY_RULE_PAY_AMOUNT( 100 );
    rules_table[39] = new GAMEPLAY_RULE_PROPERTY( 400 );
}

