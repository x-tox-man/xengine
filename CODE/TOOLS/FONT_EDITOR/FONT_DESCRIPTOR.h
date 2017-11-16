//
//  FONT_DESCRIPTOR.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/01/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef FONT_DESCRIPTOR_h
#define FONT_DESCRIPTOR_h

#include <vector>

struct FONT_DESCRIPTOR {
    
    int Size;
    unsigned char color[ 4 ];
    std::vector< char > CharacterSet;
};

#endif /* FONT_DESCRIPTOR_h */
