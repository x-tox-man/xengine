//
//  GRAPHIC_FONT_MANAGER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 17/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_FONT_MANAGER.h"

GRAPHIC_FONT_MANAGER::GRAPHIC_FONT_MANAGER() {
    
}

GRAPHIC_FONT_MANAGER::~GRAPHIC_FONT_MANAGER() {
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, GRAPHIC_FONT * >::iterator it = FontTable.begin();
    
    while (it != FontTable.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( it->second );
        
        it++;
    }
    
    FontTable.clear();
}

void GRAPHIC_FONT_MANAGER::LoadFont( const CORE_HELPERS_UNIQUE_IDENTIFIER & font_identifier, const CORE_FILESYSTEM_PATH & font_path, const CORE_FILESYSTEM_PATH & texture_path ) {
    
    FontTable[ font_identifier ] = new GRAPHIC_FONT;
    
    FontTable[ font_identifier ]->Load(font_path, texture_path );
    FontTable[ font_identifier ]->Initialize();
}

GRAPHIC_FONT * GRAPHIC_FONT_MANAGER::GetFont( const CORE_HELPERS_UNIQUE_IDENTIFIER & font_identifier ) {
    
    return FontTable[ font_identifier ];
}
