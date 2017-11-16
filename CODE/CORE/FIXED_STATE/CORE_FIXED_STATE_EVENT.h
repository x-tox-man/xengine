//
//  CORE_FIXED_STATE_EVENT.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_FIXED_STATE_EVENT_h
#define CORE_FIXED_STATE_EVENT_h

template < typename __EVENT_DATA__ >
class CORE_FIXED_STATE_EVENT {
    
public:
    CORE_FIXED_STATE_EVENT( const __EVENT_DATA__ data ): Data(data) {
        
    }

    const __EVENT_DATA__ GetEventData() const { return Data; }
    
private:
    
    const __EVENT_DATA__ Data;
};

template <>
class CORE_FIXED_STATE_EVENT< void > {
    
public:
    
    CORE_FIXED_STATE_EVENT() {

    }
};

#endif /* CORE_FIXED_STATE_EVENT_h */
