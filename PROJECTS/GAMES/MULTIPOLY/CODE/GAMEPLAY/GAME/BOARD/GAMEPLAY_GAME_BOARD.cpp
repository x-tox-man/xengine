//
//  GAMEPLAY_GAME_BOARD.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_GAME_BOARD.h"
#include "GLOBAL_RESOURCES.h"

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
    }
}
